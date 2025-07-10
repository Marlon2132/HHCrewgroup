#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QMap>
#include <QPixmap>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawSoftHand(QPainter *painter, double angleRadians,
                      double baseLength, double width,
                      const QColor &color, double phase);

    double interpolateRadius(double angleDeg) const;
    void updateBackground();

    QTimer *timer;
    QElapsedTimer elapsedTimer;
    QMap<int, double> dialAngles;
    QMap<int, double> dialRadii;
    QPixmap background;
    QPixmap scaledBackground;
};

#endif // MAINWINDOW_H
