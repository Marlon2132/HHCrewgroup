#include "mainwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QDateTime>
#include <cmath>
#include <algorithm>
#include <QDebug>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    timer->start(16);
    elapsedTimer.start();

    dialAngles[12] = 160.0;   dialRadii[12] = 1.000;
    dialAngles[1]  = 145.0;   dialRadii[1]  = 0.763;
    dialAngles[2]  = 123.0;   dialRadii[2]  = 0.502;
    dialAngles[3]  = 76.0;    dialRadii[3]  = 0.351;
    dialAngles[4]  = 342.0;   dialRadii[4]  = 0.223;
    dialAngles[5]  = 294.0;   dialRadii[5]  = 0.649;
    dialAngles[6]  = 275.0;   dialRadii[6]  = 1.289;
    dialAngles[7]  = 269.0;   dialRadii[7]  = 0.716;
    dialAngles[8]  = 260.0;   dialRadii[8]  = 0.314;
    dialAngles[9]  = 241.0;   dialRadii[9]  = 0.115;
    dialAngles[10] = 210.0;   dialRadii[10] = 0.400;
    dialAngles[11] = 195.0;   dialRadii[11] = 0.600;

    if (!background.load(":/photo/Orig.jpg")) {
        qDebug() << "Failed to load background image!";
        background = QPixmap(size());
        background.fill(Qt::darkGray);
    }

    setWindowTitle("Постоянство памяти");

}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updateBackground();
}

void MainWindow::updateBackground() {
    if (background.isNull()) return;
    scaledBackground = background.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
}

double MainWindow::interpolateRadius(double angleDeg) const {
    angleDeg = fmod(angleDeg, 360.0);
    if (angleDeg < 0) angleDeg += 360.0;

    QVector<QPair<double, double>> points;
    for (int hour = 1; hour <= 12; hour++) {
        points.append(qMakePair(dialAngles[hour], dialRadii[hour]));
    }

    for (int hour = 1; hour <= 12; hour++) {
        points.append(qMakePair(dialAngles[hour] + 360.0, dialRadii[hour]));
        points.append(qMakePair(dialAngles[hour] - 360.0, dialRadii[hour]));
    }

    std::sort(points.begin(), points.end(), [](const QPair<double, double>& a, const QPair<double, double>& b) {
        return a.first < b.first;
    });

    double prevAngle = points.first().first;
    double prevRadius = points.first().second;
    double nextAngle = points.last().first;
    double nextRadius = points.last().second;
    double minDist = 360.0;

    for (const auto& point : points) {
        double dist = fabs(point.first - angleDeg);
        if (dist < minDist) {
            minDist = dist;
        }
    }

    for (int i = 0; i < points.size() - 1; i++) {
        if (points[i].first <= angleDeg && angleDeg <= points[i+1].first) {
            prevAngle = points[i].first;
            prevRadius = points[i].second;
            nextAngle = points[i+1].first;
            nextRadius = points[i+1].second;
            break;
        }
    }

    if (nextAngle - prevAngle > 0) {
        double t = (angleDeg - prevAngle) / (nextAngle - prevAngle);
        return prevRadius + t * (nextRadius - prevRadius);
    }
    return prevRadius;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    if (!scaledBackground.isNull()) {
        painter.drawPixmap(0, 0, scaledBackground);
    }

    int side = qMin(width(), height());

    // Позиция часов
    painter.translate(width() / 3.85, height() * 0.615);

    // Масштабирование (теперь влияет на размер стрелок)
    double scaleFactor = side / 400.0;
    painter.scale(scaleFactor, scaleFactor);

    double totalMs = elapsedTimer.elapsed();
    QTime time = QTime::currentTime();
    double seconds = time.second() + time.msec() / 1000.0;
    double minutes = time.minute() + seconds / 60.0;
    double hours = time.hour() % 12 + minutes / 60.0;

    const double twelveOclockAngle = 160.0;
    double hourAngle = qDegreesToRadians(twelveOclockAngle - hours * 30.0 - minutes * 0.5);
    double minuteAngle = qDegreesToRadians(twelveOclockAngle - minutes * 6.0);
    double secondAngle = qDegreesToRadians(twelveOclockAngle - seconds * 6.0);

    double globalPhase = totalMs / 1000.0;

    // Увеличиваем базовые длины для компенсации масштабирования
    const double baseHourLength = 70.0 * 0.5;
    const double baseMinuteLength = 100.0 * 0.5;
    const double baseSecondLength = 120.0 * 0.5;

    drawSoftHand(&painter, hourAngle, baseHourLength, 8, QColor(70, 80, 160), globalPhase * 0.3);
    drawSoftHand(&painter, minuteAngle, baseMinuteLength, 6, QColor(80, 140, 200), globalPhase * 0.7);
    drawSoftHand(&painter, secondAngle, baseSecondLength, 3, QColor(220, 60, 60), globalPhase * 1.5);

    // Центральная точка - меньшего размера и черного цвета
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPointF(0, 0), 3, 3); // Уменьшенный размер
}

void MainWindow::drawSoftHand(QPainter *painter, double angleRadians,
                              double baseLength, double width,
                              const QColor &color, double phase) {
    double angleDeg = qRadiansToDegrees(angleRadians);
    double radiusFactor = interpolateRadius(angleDeg);
    double actualLength = baseLength * radiusFactor;

    QPointF endPoint(actualLength * std::cos(angleRadians),
                     -actualLength * std::sin(angleRadians));

    QPointF cp1(0.3 * endPoint.x(), 0.3 * endPoint.y());
    QPointF cp2(0.7 * endPoint.x(), 0.7 * endPoint.y());

    QPointF perp(endPoint.y(), -endPoint.x());
    double norm = std::hypot(perp.x(), perp.y());
    if (norm > 0) perp /= norm;

    double angleMod = fmod(angleRadians, M_PI * 2);
    double curvature = 4.0 +
                       2.0 * sin(phase * 0.5) +
                       1.5 * sin(angleMod * 8.0 + phase) +
                       1.0 * sin(angleMod * 3.0 - phase * 2.0);

    double offset1 = 0.5 + 0.2 * sin(phase * 1.2);
    double offset2 = 1.3 + 0.3 * cos(phase * 0.7);

    cp1 += perp * curvature * offset1;
    cp2 += perp * curvature * offset2;

    QPainterPath path;
    path.moveTo(0, 0);
    path.cubicTo(cp1, cp2, endPoint);

    // Сохраняем состояние painter
    painter->save();

    // Первая тень (основная)
    QPainterPath shadowPath1 = path;
    shadowPath1.translate(2, 2);
    QPen shadowPen1(QColor(0, 0, 0, 80));
    shadowPen1.setWidth(width + 1);
    shadowPen1.setCapStyle(Qt::RoundCap);
    shadowPen1.setJoinStyle(Qt::RoundJoin);
    painter->setPen(shadowPen1);
    painter->drawPath(shadowPath1);

    // Вторая тень (для размытия)
    QPainterPath shadowPath2 = path;
    shadowPath2.translate(1, 1);
    QPen shadowPen2(QColor(0, 0, 0, 40));
    shadowPen2.setWidth(width + 2);
    shadowPen2.setCapStyle(Qt::RoundCap);
    shadowPen2.setJoinStyle(Qt::RoundJoin);
    painter->setPen(shadowPen2);
    painter->drawPath(shadowPath2);

    // Восстанавливаем состояние painter
    painter->restore();

    // Рисуем основную стрелку
    QLinearGradient arrowGrad(0, 0, endPoint.x(), endPoint.y());
    arrowGrad.setColorAt(0, color.lighter(140));
    arrowGrad.setColorAt(1, color.darker(140));

    painter->save();
    QPen pen(arrowGrad, width);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawPath(path);
    painter->restore();
}
