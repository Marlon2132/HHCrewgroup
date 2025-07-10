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

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawSoftHand(QPainter *painter, double angleRadians,
                      double baseLength, double width,
                      const QColor &color, double phase);
    double interpolateRadius(double angleDeg) const;
    void updateBackground();

    QDateTime m_dateTime;
    QMap<int, double> dialAngles;
    QMap<int, double> dialRadii;
    QPixmap background;
    QPixmap scaledBackground;
};

#endif // SOFTWATCHWIDGET_H
