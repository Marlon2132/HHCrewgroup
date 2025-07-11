// softwatchwidget.cpp
#include "softwatchwidget.h"
#include <cmath>
#include <algorithm>
#include <QResizeEvent>
#include <QtMath>
#include <QPainterPath>
#include <QTimer>

SoftWatchWidget::SoftWatchWidget(QWidget *parent) : QWidget(parent)
{
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

    dialAnglesForMinutes << dialAngles[12]
                         << dialAngles[1]
                         << dialAngles[2]
                         << dialAngles[3]
                         << dialAngles[4]
                         << dialAngles[5]
                         << dialAngles[6]
                         << dialAngles[7]
                         << dialAngles[8]
                         << dialAngles[9]
                         << dialAngles[10]
                         << dialAngles[11];

    if (!background.load(":/images/background.jpg")) {
        background = QPixmap(size());
        background.fill(Qt::darkGray);
    }
    if (!overlay.load(":/images/clocks.png")) {
        // можно заглушку
    }

    m_dateTime = QDateTime::currentDateTime();
    m_manualMode = false;
    setWindowTitle("Постоянство памяти");

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SoftWatchWidget::updateTime);
    m_timer->start(50);
}

void SoftWatchWidget::updateTime()
{
    if (!m_manualMode)
        m_dateTime = QDateTime::currentDateTime();
    update();
}

void SoftWatchWidget::setDateTime(const QDateTime &dateTime)
{
    m_manualMode = true;
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
    scaledBackground = background.scaled(size(),
                                         Qt::KeepAspectRatioByExpanding,
                                         Qt::SmoothTransformation);
}

void SoftWatchWidget::updateOverlay()
{
    if (overlay.isNull()) return;
    scaledOverlay = overlay.scaled(size(),
                                   Qt::KeepAspectRatioByExpanding,
                                   Qt::SmoothTransformation);
}

double SoftWatchWidget::getDialAngle(double fraction) const
{
    fraction = fmod(fraction, 12.0);
    if (fraction < 0) fraction += 12.0;

    int index = static_cast<int>(fraction);
    double frac = fraction - index;
    double angle1 = dialAnglesForMinutes[index];
    double angle2 = dialAnglesForMinutes[(index + 1) % 12];
    double diff = angle2 - angle1;

    if (diff > 180.0)  diff -= 360.0;
    else if (diff < -180.0) diff += 360.0;

    double angle = angle1 + frac * diff;
    if (angle < 0)      angle += 360.0;
    else if (angle >= 360.0) angle -= 360.0;
    return angle;
}

double SoftWatchWidget::interpolateRadius(double angleDeg) const
{
    angleDeg = fmod(angleDeg, 360.0);
    if (angleDeg < 0) angleDeg += 360.0;

    QVector<QPair<double, double>> points;
    for (int h = 1; h <= 12; ++h) {
        points.append(qMakePair(dialAngles[h], dialRadii[h]));
        points.append(qMakePair(dialAngles[h] + 360.0, dialRadii[h]));
        points.append(qMakePair(dialAngles[h] - 360.0, dialRadii[h]));
    }
    std::sort(points.begin(), points.end(),
              [](auto &a, auto &b){ return a.first < b.first; });

    double prevA = points.first().first;
    double prevR = points.first().second;
    double nextA = points.last().first;
    double nextR = points.last().second;

    for (int i = 0; i < points.size() - 1; ++i) {
        if (points[i].first <= angleDeg && angleDeg <= points[i+1].first) {
            prevA = points[i].first;
            prevR = points[i].second;
            nextA = points[i+1].first;
            nextR = points[i+1].second;
            break;
        }
    }
    double span = nextA - prevA;
    if (span > 0) {
        double t = (angleDeg - prevA) / span;
        return prevR + t * (nextR - prevR);
    }
    return prevR;
}

void SoftWatchWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    if (!scaledBackground.isNull())
        painter.drawPixmap(0, 0, scaledBackground);
    if (!scaledOverlay.isNull())
        painter.drawPixmap(0, 0, scaledOverlay);

    int side = qMin(width(), height());
    painter.translate(width() / 3.92, height() * 0.619);
    painter.scale(side / 400.0, side / 400.0);

    QTime tm = m_dateTime.time();
    double secs   = tm.second() + tm.msec() / 1000.0;
    double mins   = tm.minute() + secs / 60.0;
    double hours  = tm.hour() % 12 + mins / 60.0;

    double hAng = qDegreesToRadians(getDialAngle(hours));
    double mAng = qDegreesToRadians(getDialAngle(mins / 5.0));
    double sAng = qDegreesToRadians(getDialAngle(secs  / 5.0));
    double phase = QDateTime::currentMSecsSinceEpoch() / 1000.0;

    drawSoftHand(&painter, hAng, 70 * 0.5, 6, QColor(70,80,160), phase * 0.3);
    drawSoftHand(&painter, mAng,100 * 0.5, 4, QColor(80,140,200), phase * 0.7);
    drawSoftHand(&painter, sAng,120 * 0.5, 3, QColor(220,60,60), phase * 1.5);

    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPointF(0,0), 3, 3);
}

void SoftWatchWidget::drawSoftHand(QPainter *painter, double angleRad,
                                   double baseLen, double width,
                                   const QColor &color, double phase)
{
    double angleDeg = qRadiansToDegrees(angleRad);
    double radiusF = interpolateRadius(angleDeg);
    double length  = baseLen * radiusF;
    QPointF endP(length * cos(angleRad), -length * sin(angleRad));

    QPointF cp1 = endP * 0.3;
    QPointF cp2 = endP * 0.7;

    QPointF perp(endP.y(), -endP.x());
    double norm = std::hypot(perp.x(), perp.y());
    if (norm>0) perp /= norm;

    double angMod   = fmod(angleRad, M_PI*2);
    double curv     = 4.0
                  + 2.0 * sin(phase * 0.5)
                  + 1.5 * sin(angMod * 3.0 - phase * 2.0)
                  + 1.0 * sin(angMod * 8.0 + phase);
    double offs1    = 0.5 + 0.2 * sin(phase * 1.2);
    double offs2    = 1.3 + 0.3 * cos(phase * 0.7);

    cp1 += perp * curv * offs1;
    cp2 += perp * curv * offs2;

    QPainterPath path;
    path.moveTo(0,0);
    path.cubicTo(cp1, cp2, endP);

    // тени
    painter->save();
    auto drawShadow = [&](double dx, double dy, QColor col, double w){
        QPainterPath pp = path;
        pp.translate(dx, dy);
        QPen pen(col, w);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter->setPen(pen);
        painter->drawPath(pp);
    };
    drawShadow(1,1, QColor(0,0,0,80),  width+0.5);
    drawShadow(0.5,0.5, QColor(0,0,0,40), width+1);
    painter->restore();

    // сама стрелка
    QLinearGradient grad(0,0,endP.x(), endP.y());
    grad.setColorAt(0, color.lighter(140));
    grad.setColorAt(1, color.darker(140));
    QPen pen(grad, width);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawPath(path);
}

void SoftWatchWidget::setBackgroundImage(const QString &resourcePath)
{
    QPixmap pix(resourcePath);
    if (pix.isNull()) return;
    background = pix;
    updateBackground();
    update();
}
