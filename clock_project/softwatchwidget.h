// softwatchwidget.h
#ifndef SOFTWATCHWIDGET_H
#define SOFTWATCHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QMap>
#include <QPixmap>
#include <QDateTime>
#include <QPainterPath>

class SoftWatchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SoftWatchWidget(QWidget *parent = nullptr);
    void setDateTime(const QDateTime &dateTime);
    void setBackgroundImage(const QString &resourcePath);


protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateTime();

private:
    void drawSoftHand(QPainter *painter, double angleRadians,
                      double baseLength, double width,
                      const QColor &color, double phase);
    double interpolateRadius(double angleDeg) const;
    void updateBackground();
    void updateOverlay();
    double getDialAngle(double fraction) const;

    QDateTime m_dateTime;
    bool m_manualMode = false;                      // режим ручной установки времени

    QMap<int, double> dialAngles;
    QMap<int, double> dialRadii;
    QPixmap background;
    QPixmap scaledBackground;
    QPixmap overlay;
    QPixmap scaledOverlay;
    QTimer *m_timer;
    QVector<double> dialAnglesForMinutes;
};

#endif // SOFTWATCHWIDGET_H
