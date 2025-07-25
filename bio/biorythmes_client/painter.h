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
    void setDates(const Date& todayDate, const Date& calcDate, const Date& birthDate);
    // Новый метод — задаёт проценты
    void setPercents(int physPercent, int psychoPercent, int intelPercent);
    void setDaysLived(quint16 days);
    void setTodayAndCalcDates(const Date& todayDate, const Date& calcDate);
    // координаты курсора, формат и флаги без изменений
    int x;
    int y;
    Date currDate;
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
    Date today;      // Сегодняшняя дата
    Date calc;       // Дата расчета
    Date birth;      // Дата рождения
    int dateDiff;    // Разница между сегодняшней датой и датой расчета
    quint16 m_daysLived = 0;
    int physBiorythmPercent   = 0;
    int psychoBiorythmPercent = 0;
    int intellBiorythmPercent = 0;
};

#endif // PAINTER_H
