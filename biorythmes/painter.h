#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include "date.h"
#include <QMouseEvent>

class painter : public QWidget
{
    Q_OBJECT

signals:
    void updateInfoSignal();

public:
    explicit painter(QWidget *parent = nullptr);
    void getDates(Date _currDate, Date _birth);
    void changeFormat(int x);

    int x;
    int y;
    Date currDate;
    Date birth;
    Date cursorDate;

    bool cursorTracking = false;

    bool maxLine = false;
    bool minLine = false;
    bool nullCircle = false;
    bool maxCross = false;
    bool minCross = false;
    bool critMax = false;
    bool critMin = false;
    bool critNull = false;
    bool birthdaySwitch = true;
    bool bold = false;
    bool antialiasing = true;
    bool physShow = true;
    bool psychoShow = true;
    bool intellShow = true;
    bool firstLaunch = false;

    //private slots:
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;


private:


    int format = 1;
    int physBiorythmPercent;
    int psychoBiorythmPercent;
    int intellBiorythmPercent;



};

#endif // PAINTER_H
