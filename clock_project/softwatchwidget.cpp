#include "softwatchwidget.h"
#include <cmath>
#include <algorithm>
#include <QDebug>
#include <QResizeEvent>
#include <QtMath>
#include <QPainterPath>

SoftWatchWidget::SoftWatchWidget(QWidget *parent) : QWidget(parent)
{
    // Углы и радиусы для циферблата в стиле Дали
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

    // Загрузка фонового изображения
    if (!background.load(":/images/background.jpg")) {
        qDebug() << "Failed to load background image! Using default color.";
        background = QPixmap(size());
        background.fill(Qt::darkGray);
    }

    if (!overlay.load(":/images/clocks.png")) {
        qWarning() << "Failed to load overlay";
    }

    m_dateTime = QDateTime::currentDateTime();
    setWindowTitle("Постоянство памяти");
}

void SoftWatchWidget::setBackgroundImage(const QString &resourcePath)
{
    // 1) Пытаемся загрузить
    QPixmap pix(resourcePath);
    if (pix.isNull()) {
        qDebug() << "SoftWatchWidget: failed to load" << resourcePath;
        return;
    }

    // 2) Сохраняем, масштабируем и перерисовываем
    background = pix;
    updateBackground();
    //updateOverlay();
    update();   // вызовет paintEvent()
}

void SoftWatchWidget::setDateTime(const QDateTime &dateTime)
{
    m_dateTime = dateTime;
    update();
}

void SoftWatchWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateBackground();
    updateOverlay();
}

void SoftWatchWidget::updateBackground()
{
    if (background.isNull()) return;
    scaledBackground = background.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
}

void SoftWatchWidget::updateOverlay()
{
    if (overlay.isNull()) return;
    scaledOverlay = overlay.scaled(
        size(),
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
        );
}

double SoftWatchWidget::interpolateRadius(double angleDeg) const
{
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

void SoftWatchWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // Рисуем фон
    if (!scaledBackground.isNull()) {
        painter.drawPixmap(0, 0, scaledBackground);
    }

    if (!scaledOverlay.isNull()){
        painter.drawPixmap(0, 0, scaledOverlay);
    }

    int side = qMin(width(), height());
    painter.translate(width() / 3.85, height() * 0.615);
    double scaleFactor = side / 400.0;
    painter.scale(scaleFactor, scaleFactor);

    QTime time = m_dateTime.time();
    double seconds = time.second() + time.msec() / 1000.0;
    double minutes = time.minute() + seconds / 60.0;
    double hours = time.hour() % 12 + minutes / 60.0;

    const double twelveOclockAngle = 160.0;
    double hourAngle = qDegreesToRadians(twelveOclockAngle - hours * 30.0 - minutes * 0.5);
    double minuteAngle = qDegreesToRadians(twelveOclockAngle - minutes * 6.0);
    double secondAngle = qDegreesToRadians(twelveOclockAngle - seconds * 6.0);

    double globalPhase = QDateTime::currentMSecsSinceEpoch() / 1000.0;

    // Рисуем стрелки
    drawSoftHand(&painter, hourAngle, 70 * 0.5, 8, QColor(70, 80, 160), globalPhase * 0.3);
    drawSoftHand(&painter, minuteAngle, 100 * 0.5, 6, QColor(80, 140, 200), globalPhase * 0.7);
    drawSoftHand(&painter, secondAngle, 120 * 0.5, 3, QColor(220, 60, 60), globalPhase * 1.5);

    // Центральная точка
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPointF(0, 0), 3, 3);
}

void SoftWatchWidget::drawSoftHand(QPainter *painter, double angleRadians,
                                   double baseLength, double width,
                                   const QColor &color, double phase)
{
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

    // Тени для создания 3D-эффекта
    painter->save();
    QPainterPath shadowPath1 = path;
    shadowPath1.translate(2, 2);
    QPen shadowPen1(QColor(0, 0, 0, 80));
    shadowPen1.setWidth(width + 1);
    shadowPen1.setCapStyle(Qt::RoundCap);
    shadowPen1.setJoinStyle(Qt::RoundJoin);
    painter->setPen(shadowPen1);
    painter->drawPath(shadowPath1);

    QPainterPath shadowPath2 = path;
    shadowPath2.translate(1, 1);
    QPen shadowPen2(QColor(0, 0, 0, 40));
    shadowPen2.setWidth(width + 2);
    shadowPen2.setCapStyle(Qt::RoundCap);
    shadowPen2.setJoinStyle(Qt::RoundJoin);
    painter->setPen(shadowPen2);
    painter->drawPath(shadowPath2);
    painter->restore();

    // Основная стрелка с градиентом
    painter->save();
    QLinearGradient arrowGrad(0, 0, endPoint.x(), endPoint.y());
    arrowGrad.setColorAt(0, color.lighter(140));
    arrowGrad.setColorAt(1, color.darker(140));

    QPen pen(arrowGrad, width);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawPath(path);
    painter->restore();
}
