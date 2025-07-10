#include "painter.h"
#include "date.h"
#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QFont>
#include <QtMath>
#include <QMouseEvent>
#include <QCursor>
#include <QDate>

Painter::Painter(QWidget *parent) :
    QWidget{parent}
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(true);
}

void Painter::setPercents(int physPercent, int psychoPercent, int intelPercent)
{
    physBiorythmPercent   = physPercent;
    psychoBiorythmPercent = psychoPercent;
    intellBiorythmPercent = intelPercent;
    update();
}

void Painter::setDaysLived(quint16 days)
{
    m_daysLived = days;
}

void Painter::setTodayAndCalcDates(const Date& todayDate, const Date& calcDate)
{
    today = todayDate;
    // Вычисляем разницу между сегодняшней датой и датой расчета
    dateDiff = today - calcDate;
}

void Painter::setDates(const Date& todayDate, const Date& calcDate, const Date& birthDate)
{
    today = todayDate;
    calc = calcDate;
    birth = birthDate;
    dateDiff = today - calc;  // Теперь оператор вычитания определен
    update();
}

void Painter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter pntr(this);
    if (antialiasing) pntr.setRenderHint(QPainter::Antialiasing, true);
    QFont _font("font", 7);
    pntr.setFont(_font);
    double width = this->width();
    double height = this->height();
    double centerW = width/2;
    double centerH = height/2;

    // 0y & 0x
    pntr.drawLine(centerW, 15, centerW, height-15);
    pntr.drawLine(15, centerH, width - 15, centerH);

    //arrow 0y
    pntr.drawLine(centerW, 15, centerW - 3, 20);
    pntr.drawLine(centerW, 15, centerW + 3, 20);
    // end of 0y - centerW, 15

    //arrow 0x
    pntr.drawLine(width - 20, centerH - 3, width-15, centerH);
    pntr.drawLine(width - 20, centerH + 3, width-15, centerH);
    //end of 0x - this->width()-15, centerH

    //names of the axes
    pntr.drawText(centerW-40, 10, "Уровень активности");
    pntr.drawText(width-20, centerH-5, "Дата");

    //null of coordinates
    pntr.setPen(QPen(Qt::white, 3));
    pntr.drawEllipse(centerW-1, centerH-1, 2, 2);

    pntr.setPen(QPen(Qt::white, 1));

    // надписи max & min
    pntr.drawText(centerW+5, 32, "max");
    pntr.drawText(centerW+5, height-27, "min");

    //черточки на осях
    pntr.drawLine(centerW - 3, 30, centerW + 3, 30);
    pntr.drawLine(centerW - 3, height-30, centerW + 3, this->height()-30);
    pntr.drawLine(centerW - 3, (height-60)/4+30, centerW + 3, (height-60)/4+30);
    pntr.drawLine(centerW - 3, ((height-60)/4)*3+30, centerW + 3, ((height-60)/4)*3+30);

    // Новые позиции для 30-дневного диапазона
    pntr.drawLine(width*1/6, centerH-3, width*1/6, centerH+3);
    pntr.drawLine(width*2/6, centerH-3, width*2/6, centerH+3);
    pntr.drawLine(centerW, centerH-3, centerW, centerH+3);
    pntr.drawLine(width*4/6, centerH-3, width*4/6, centerH+3);
    pntr.drawLine(width*5/6, centerH-3, width*5/6, centerH+3);

    //draw dates - используем сегодняшнюю дату как центральную
    if (format == 2)
    {
        today.changeFormat(1);
        birth.changeFormat(1);
    }
    pntr.drawText(centerW+2, centerH+10, today.outputDate());
    pntr.drawText(width*4/6, centerH+10, (today+10).outputDate());
    pntr.drawText(width*5/6, centerH+10, (today+20).outputDate());
    pntr.drawText(width*1/6, centerH+10, (today-20).outputDate());
    pntr.drawText(width*2/6, centerH+10, (today-10).outputDate());
    if (format == 2)
    {
        today.changeFormat(2);
        birth.changeFormat(2);
    }

    //============================================================================================================================
    if (firstLaunch)
    {
        const int RANGE_DAYS = 30;
        const double DAYS_SPAN = RANGE_DAYS * 2;
        const double step = (width - 30) / DAYS_SPAN;

        double pi = 3.14159265359;
        double dort1, dort2, diff, dortCheck1, dortCheck2;
        diff = 0.5;

        // физ био
        if (physShow)
        {
            for (double i = -RANGE_DAYS; i <= RANGE_DAYS; i += diff) {
                double x_pos = centerW + step * i;

                // Расчет дней от рождения: дни до расчета + разница до сегодня + смещение
                double daysFromBirth = m_daysLived + dateDiff + i;
                dort1 = qSin(2*pi*daysFromBirth/23);
                dort2 = qSin(2*pi*(daysFromBirth + diff)/23);

                //критичнские дни
                //макс - линия на ось
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                {
                    pntr.setPen(QPen(Qt::red, 1));
                    pntr.drawLine(x_pos, centerH - (height-60)/2, x_pos, centerH);
                }
                //макс - крестик
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                {
                    pntr.setPen(QPen(Qt::red, 2));
                    pntr.drawLine(x_pos+5, 15, x_pos-5, 25);
                    pntr.drawLine(x_pos-5, 15, x_pos+5, 25);
                }
                //мин - крестик
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                {
                    pntr.setPen(QPen(Qt::red, 2));
                    pntr.drawLine(x_pos+5, height-5, x_pos-5, height-15);
                    pntr.drawLine(x_pos-5, height-5, x_pos+5, height-15);
                }
                //мин - линия на ось
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                {
                    pntr.setPen(QPen(Qt::red, 1));
                    pntr.drawLine(x_pos, centerH + (height-60)/2, x_pos, centerH);
                }
                //неуст - окружность
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                {
                    pntr.setPen(QPen(Qt::red, 2));
                    pntr.drawEllipse(x_pos-5, centerH-5, 10, 10);
                }

                //очень критические дни
                dortCheck1 = qSin(2*pi*daysFromBirth/28);
                dortCheck2 = qSin(2*pi*daysFromBirth/33);
                if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                           || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                           || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawLine(x_pos, centerH - (height-60)/2, x_pos, centerH);
                    pntr.drawLine(x_pos+5, 15, x_pos-5, 25);
                    pntr.drawLine(x_pos-5, 15, x_pos+5, 25);
                }
                else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawLine(x_pos, centerH + (height-60)/2, x_pos, centerH);
                    pntr.drawLine(x_pos+5, height-5, x_pos-5, height-15);
                    pntr.drawLine(x_pos-5, height-5, x_pos+5, height-15);
                }
                else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                 || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                 || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawEllipse(x_pos-5, centerH-5, 10, 10);
                }
                if (bold) pntr.setPen(QPen(Qt::red, 2));
                else pntr.setPen(QPen(Qt::red, 1));
                pntr.drawLine(x_pos, centerH - ((height-60)/2)*dort1,
                              centerW + step*(i+diff), centerH - ((height-60)/2)*dort2);
            }
        }

        //псих био
        if (psychoShow)
        {
            for (double i = -RANGE_DAYS; i <= RANGE_DAYS; i += diff) {
                double x_pos = centerW + step * i;

                // Расчет дней от рождения: дни до расчета + разница до сегодня + смещение
                double daysFromBirth = m_daysLived + dateDiff + i;
                dort1 = qSin(2*pi*daysFromBirth/28);
                dort2 = qSin(2*pi*(daysFromBirth + diff)/28);

                //критичнские дни
                //макс - линия на ось
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                {
                    pntr.setPen(QPen(Qt::blue, 1));
                    pntr.drawLine(x_pos, centerH - (height-60)/2, x_pos, centerH);
                }
                //макс - крестик
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                {
                    pntr.setPen(QPen(Qt::blue, 2));
                    pntr.drawLine(x_pos+5, 15, x_pos-5, 25);
                    pntr.drawLine(x_pos-5, 15, x_pos+5, 25);
                }
                //мин - крестик
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                {
                    pntr.setPen(QPen(Qt::blue, 2));
                    pntr.drawLine(x_pos+5, height-5, x_pos-5, height-15);
                    pntr.drawLine(x_pos-5, height-5, x_pos+5, height-15);
                }
                //мин - линия на ось
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                {
                    pntr.setPen(QPen(Qt::blue, 1));
                    pntr.drawLine(x_pos, centerH + (height-60)/2, x_pos, centerH);
                }
                //неуст - окружность
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                {
                    pntr.setPen(QPen(Qt::blue, 2));
                    pntr.drawEllipse(x_pos-5, centerH-5, 10, 10);
                }
                //очень критические дни
                dortCheck1 = qSin(2*pi*daysFromBirth/23);
                dortCheck2 = qSin(2*pi*daysFromBirth/33);
                if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                           || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                           || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawLine(x_pos, centerH - (height-60)/2, x_pos, centerH);
                    pntr.drawLine(x_pos+5, 15, x_pos-5, 25);
                    pntr.drawLine(x_pos-5, 15, x_pos+5, 25);
                }
                else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawLine(x_pos, centerH + (height-60)/2, x_pos, centerH);
                    pntr.drawLine(x_pos+5, height-5, x_pos-5, height-15);
                    pntr.drawLine(x_pos-5, height-5, x_pos+5, height-15);
                }
                else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                 || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                 || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawEllipse(x_pos-5, centerH-5, 10, 10);
                }
                if (bold) pntr.setPen(QPen(Qt::blue, 2));
                else pntr.setPen(QPen(Qt::blue, 1));
                pntr.drawLine(x_pos, centerH - ((height-60)/2)*dort1,
                              centerW + step*(i+diff), centerH - ((height-60)/2)*dort2);
            }
        }

        //инт био
        if (intellShow)
        {
            for (double i = -RANGE_DAYS; i <= RANGE_DAYS; i += diff) {
                double x_pos = centerW + step * i;

                // Расчет дней от рождения: дни до расчета + разница до сегодня + смещение
                double daysFromBirth = m_daysLived + dateDiff + i;
                dort1 = qSin(2*pi*daysFromBirth/33);
                dort2 = qSin(2*pi*(daysFromBirth + diff)/33);

                //критичнские дни
                //макс - линия на ось
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                {
                    pntr.setPen(QPen(Qt::green, 1));
                    pntr.drawLine(x_pos, centerH - (height-60)/2, x_pos, centerH);
                }
                //макс - крестик
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                {
                    pntr.setPen(QPen(Qt::green, 2));
                    pntr.drawLine(x_pos+5, 15, x_pos-5, 25);
                    pntr.drawLine(x_pos-5, 15, x_pos+5, 25);
                }
                //мин - крестик
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                {
                    pntr.setPen(QPen(Qt::green, 2));
                    pntr.drawLine(x_pos+5, height-5, x_pos-5, height-15);
                    pntr.drawLine(x_pos-5, height-5, x_pos+5, height-15);
                }
                //мин - линия на ось
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                {
                    pntr.setPen(QPen(Qt::green, 1));
                    pntr.drawLine(x_pos, centerH + (height-60)/2, x_pos, centerH);
                }
                //неуст - окружность
                if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                {
                    pntr.setPen(QPen(Qt::green, 2));
                    pntr.drawEllipse(x_pos-5, centerH-5, 10, 10);
                }
                //очень критические дни
                dortCheck1 = qSin(2*pi*daysFromBirth/28);
                dortCheck2 = qSin(2*pi*daysFromBirth/23);
                if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                           || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                           || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawLine(x_pos, centerH - (height-60)/2, x_pos, centerH);
                    pntr.drawLine(x_pos+5, 15, x_pos-5, 25);
                    pntr.drawLine(x_pos-5, 15, x_pos+5, 25);
                }
                else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawLine(x_pos, centerH + (height-60)/2, x_pos, centerH);
                    pntr.drawLine(x_pos+5, height-5, x_pos-5, height-15);
                    pntr.drawLine(x_pos-5, height-5, x_pos+5, height-15);
                }
                else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                 || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                 || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                {
                    pntr.setPen(QPen(Qt::yellow, 3));
                    pntr.drawEllipse(x_pos-5, centerH-5, 10, 10);
                }
                if (bold) pntr.setPen(QPen(Qt::green, 2));
                else pntr.setPen(QPen(Qt::green, 1));
                pntr.drawLine(x_pos, centerH - ((height-60)/2)*dort1,
                              centerW + step*(i+diff), centerH - ((height-60)/2)*dort2);
            }
        }

        if (birthdaySwitch)
        {
            int diffDays = birth - today;
            if (diffDays >= -RANGE_DAYS && diffDays <= RANGE_DAYS)
            {
                double x_pos = centerW + step * diffDays;

                pntr.setPen(QPen(Qt::white, 2));
                pntr.drawLine(x_pos, (height-60)/9 + 30, x_pos, (height-60)/9*2 + 30);
                pntr.drawLine(x_pos, (height-60)/9*3 + 30, x_pos, (height-60)/9*4 + 30);
                pntr.drawLine(x_pos, (height-60)/9*5 + 30, x_pos, (height-60)/9*6 + 30);
                pntr.drawLine(x_pos, (height-60)/9*7 + 30, x_pos, (height-60)/9*8 + 30);
                pntr.drawLine(x_pos-10, 15, x_pos, 25);
                pntr.drawLine(x_pos+10, 15, x_pos, 25);
                pntr.drawLine(x_pos-10, height-15, x_pos, height-25);
                pntr.drawLine(x_pos+10, height-15, x_pos, height-25);

                pntr.setPen(QPen(Qt::white, 3));
                pntr.drawEllipse(x_pos-5, centerH-5, 10, 10);

                QFont _font("font", 10);
                pntr.setFont(_font);
                pntr.drawText(x_pos-43, height-3, "Дата рождения");
            }
        }
    }

    if (cursorTracking)
    {
        const int RANGE_DAYS = 30;
        const double DAYS_SPAN = RANGE_DAYS * 2;
        const double step = (width - 30) / DAYS_SPAN;

        QFont _font("font", 7);
        pntr.setFont(_font);
        pntr.setPen(QPen(Qt::gray, 1));
        pntr.drawLine(x, y, x, centerH);

        // Рассчитываем дату под курсором относительно сегодняшней даты
        int dayOffset = qRound((x - 15) / step) - RANGE_DAYS;
        cursorDate = today + dayOffset;

        pntr.drawText(x, y, cursorDate.outputDate());
    }
}

void Painter::getDates(Date _currDate, Date _birth)
{
    currDate.inputDate(_currDate.outputDate());
    birth.inputDate(_birth.outputDate());
}

void Painter::changeFormat(int x)
{
    if (x > 0 && x < 4) {
        currDate.changeFormat(x);
        birth.changeFormat(x);
        today.changeFormat(x);
        format = x;
    }
}

void Painter::mouseMoveEvent(QMouseEvent* event)
{
    x = event->pos().x();
    y = event->pos().y();
    update();
}

void Painter::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    currDate = cursorDate;
    update();
    emit updateInfoSignal();
}
