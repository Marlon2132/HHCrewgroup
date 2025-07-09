#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include "date.h"
#include <QMouseEvent>

class Painter : public QWidget
{
    Q_OBJECT

signals:
    void updateInfoSignal();

public:
    explicit Painter(QWidget *parent = nullptr);

    // Передать даты — без изменения
    void getDates(Date _currDate, Date _birth);
    void changeFormat(int x);

    // Новый метод — задаёт проценты
    void setPercents(int physPercent, int psychoPercent, int intelPercent);

    // координаты курсора, формат и флаги без изменений
    int x;
    int y;
    Date currDate;
    Date birth;
    Date cursorDate;

    bool cursorTracking = false;
    bool maxLine    = false;
    bool minLine    = false;
    bool nullCircle = false;
    bool maxCross   = false;
    bool minCross   = false;
    bool critMax    = false;
    bool critMin    = false;
    bool critNull   = false;
    bool birthdaySwitch = true;
    bool bold       = false;
    bool antialiasing  = true;
    bool physShow     = true;
    bool psychoShow   = true;
    bool intellShow   = true;
    bool firstLaunch  = false;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    int format = 1;

    // полям присвоим начальные значения
    int physBiorythmPercent   = 0;
    int psychoBiorythmPercent = 0;
    int intellBiorythmPercent = 0;
};

#endif // PAINTER_H
