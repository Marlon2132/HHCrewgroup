#include "painter.h"
#include "date.h"
#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QFont>
#include <QtMath>
#include <QMouseEvent>
#include <QCursor>

painter::painter(QWidget *parent) :
    QWidget{parent}
{

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(1);
}

void painter::paintEvent(QPaintEvent *event)
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
    //pntr.drawText(this->width()/2-7, this->height()/2+9, "0");
    pntr.drawText(centerW+5, 32, "max");
    pntr.drawText(centerW+5, height-27, "min");

    //черточки на осях
    pntr.drawLine(centerW - 3, 30, centerW + 3, 30);
    pntr.drawLine(centerW - 3, height-30, centerW + 3, this->height()-30);
    pntr.drawLine(centerW - 3, (height-60)/4+30, centerW + 3, (height-60)/4+30);
    pntr.drawLine(centerW - 3, ((height-60)/4)*3+30, centerW + 3, ((height-60)/4)*3+30);

    pntr.drawLine(centerW/4, centerH-3, centerW/4, centerH+3);
    pntr.drawLine((centerW/4)*2, centerH-3, (centerW/4)*2, centerH+3);
    pntr.drawLine((centerW/4)*3, centerH-3, (centerW/4)*3, centerH+3);
    pntr.drawLine((centerW/4)*5, centerH-3, (centerW/4)*5, centerH+3);
    pntr.drawLine((centerW/4)*6, centerH-3, (centerW/4)*6, centerH+3);
    pntr.drawLine((centerW/4)*7, centerH-3, (centerW/4)*7, centerH+3);

    //draw dates
    if (format == 2)
    {
        currDate.changeFormat(1);
        birth.changeFormat(1);
    }
    pntr.drawText(centerW+2, centerH+10, currDate.outputDate());
    pntr.drawText((centerW/4)*5, centerH+10, (currDate+10).outputDate());
    pntr.drawText((centerW/4)*6, centerH+10, (currDate+20).outputDate());
    pntr.drawText((centerW/4)*7, centerH+10, (currDate+30).outputDate());
    pntr.drawText((centerW/4), centerH+10, (currDate-30).outputDate());
    pntr.drawText((centerW/4)*2, centerH+10, (currDate-20).outputDate());
    pntr.drawText((centerW/4)*3, centerH+10, (currDate-10).outputDate());
    if (format == 2)
    {
        currDate.changeFormat(2);
        birth.changeFormat(2);
    }

    //============================================================================================================================
    if (firstLaunch)
    {
        double pi = 3.14159265359;
        double dort1, dort2, diff, dortCheck1, dortCheck2;
        diff = 0.5;

        // физ био
        if (physShow)
        {


            for (double i = -40; i < 40; i += diff) {

                if (currDate >= birth)
                {
                    if (currDate + qRound(i) >= birth) //
                    {
                        dort1 = qSin(2*pi*((currDate-birth)+i)/23);
                        dort2 = qSin(2*pi*((currDate-birth)+i+diff)/23);


                        //критичнские дни
                        //макс - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                        {
                            pntr.setPen(QPen(Qt::red, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //макс - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                        {
                            pntr.setPen(QPen(Qt::red, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        //мин - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                        {
                            pntr.setPen(QPen(Qt::red, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        //мин - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                        {
                            pntr.setPen(QPen(Qt::red, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //неуст - окружность
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                        {
                            pntr.setPen(QPen(Qt::red, 2));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }

                        //очень критические дни//----------------------------------------------
                        dortCheck1 = qSin(2*pi*((currDate-birth)+i)/28);
                        dortCheck2 = qSin(2*pi*((currDate-birth)+i)/33);
                        if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                                   || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                                   || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                        || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                        || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                         || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                         || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        if (bold) pntr.setPen(QPen(Qt::red, 2));
                        else pntr.setPen(QPen(Qt::red, 1));
                        pntr.drawLine(centerW+((width-30)/80)*(i), centerH - ((height-60)/2)*dort1, centerW+((width-30)/80)*(i+diff), centerH - ((height-60)/2)*dort2);
                    }
                }
                else
                {
                    if (currDate + i >= birth) //
                    {
                        dort1 = qSin(2*pi*((currDate-birth)+i)/23);
                        dort2 = qSin(2*pi*((currDate-birth)+i+diff)/23);
                        //критичнские дни
                        //макс - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                        {
                            pntr.setPen(QPen(Qt::red, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //макс - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                        {
                            pntr.setPen(QPen(Qt::red, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        //мин - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                        {
                            pntr.setPen(QPen(Qt::red, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        //мин - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                        {
                            pntr.setPen(QPen(Qt::red, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //неуст - окружность
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                        {
                            pntr.setPen(QPen(Qt::red, 2));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        //очень критические дни//----------------------------------------------
                        dortCheck1 = qSin(2*pi*((currDate-birth)+i)/28);
                        dortCheck2 = qSin(2*pi*((currDate-birth)+i)/33);
                        if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                                   || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                                   || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                        || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                        || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                         || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                         || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        if (bold) pntr.setPen(QPen(Qt::red, 2));
                        else pntr.setPen(QPen(Qt::red, 1));
                        pntr.drawLine(centerW+((width-30)/80)*(i), centerH - ((height-60)/2)*dort1, centerW+((width-30)/80)*(i+diff), centerH - ((height-60)/2)*dort2);
                    }
                }


            }
        }



        //псих био
        if (psychoShow)
        {

            for (double i = -40; i < 40; i += diff) {

                if (currDate >= birth)
                {
                    if (currDate + qRound(i) >= birth)
                    {
                        dort1 = qSin(2*pi*((currDate-birth)+i)/28);
                        dort2 = qSin(2*pi*((currDate-birth)+i+diff)/28);
                        //критичнские дни
                        //макс - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                        {
                            pntr.setPen(QPen(Qt::blue, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //макс - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                        {
                            pntr.setPen(QPen(Qt::blue, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        //мин - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                        {
                            pntr.setPen(QPen(Qt::blue, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        //мин - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                        {
                            pntr.setPen(QPen(Qt::blue, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //неуст - окружность
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                        {
                            pntr.setPen(QPen(Qt::blue, 2));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        //очень критические дни//----------------------------------------------
                        dortCheck1 = qSin(2*pi*((currDate-birth)+i)/23);
                        dortCheck2 = qSin(2*pi*((currDate-birth)+i)/33);
                        if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                                   || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                                   || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                        || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                        || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                         || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                         || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        if (bold) pntr.setPen(QPen(Qt::blue, 2));
                        else pntr.setPen(QPen(Qt::blue, 1));
                        pntr.drawLine(centerW+((width-30)/80)*(i), centerH - ((height-60)/2)*dort1, centerW+((width-30)/80)*(i+diff), centerH - ((height-60)/2)*dort2);
                    }
                }
                else
                {
                    if (currDate + i >= birth)
                    {
                        dort1 = qSin(2*pi*((currDate-birth)+i)/28);
                        dort2 = qSin(2*pi*((currDate-birth)+i+diff)/28);
                        //критичнские дни
                        //макс - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                        {
                            pntr.setPen(QPen(Qt::blue, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //макс - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                        {
                            pntr.setPen(QPen(Qt::blue, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        //мин - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                        {
                            pntr.setPen(QPen(Qt::blue, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        //мин - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                        {
                            pntr.setPen(QPen(Qt::blue, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //неуст - окружность
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                        {
                            pntr.setPen(QPen(Qt::blue, 2));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        //очень критические дни//----------------------------------------------
                        dortCheck1 = qSin(2*pi*((currDate-birth)+i)/23);
                        dortCheck2 = qSin(2*pi*((currDate-birth)+i)/33);
                        if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                                   || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                                   || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                        || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                        || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                         || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                         || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        if (bold) pntr.setPen(QPen(Qt::blue, 2));
                        else pntr.setPen(QPen(Qt::blue, 1));
                        pntr.drawLine(centerW+((width-30)/80)*(i), centerH - ((height-60)/2)*dort1, centerW+((width-30)/80)*(i+diff), centerH - ((height-60)/2)*dort2);
                    }
                }
            }
        }

        //инт био
        if (intellShow)
        {

            for (double i = -40; i < 40; i += diff) {

                if (currDate >= birth)
                {
                    if (currDate + qRound(i) >= birth)
                    {
                        dort1 = qSin(2*pi*((currDate-birth)+i)/33);
                        dort2 = qSin(2*pi*((currDate-birth)+i+diff)/33);
                        //критичнские дни
                        //макс - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                        {
                            pntr.setPen(QPen(Qt::green, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //макс - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                        {
                            pntr.setPen(QPen(Qt::green, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        //мин - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                        {
                            pntr.setPen(QPen(Qt::green, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        //мин - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                        {
                            pntr.setPen(QPen(Qt::green, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //неуст - окружность
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                        {
                            pntr.setPen(QPen(Qt::green, 2));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        //очень критические дни//----------------------------------------------
                        dortCheck1 = qSin(2*pi*((currDate-birth)+i)/28);
                        dortCheck2 = qSin(2*pi*((currDate-birth)+i)/23);
                        if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                                   || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                                   || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                        || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                        || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                         || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                         || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        if (bold) pntr.setPen(QPen(Qt::green, 2));
                        else pntr.setPen(QPen(Qt::green, 1));
                        pntr.drawLine(centerW+((width-30)/80)*(i), centerH - ((height-60)/2)*dort1, centerW+((width-30)/80)*(i+diff), centerH - ((height-60)/2)*dort2);
                    }
                }
                else
                {
                    if (currDate + i >= birth)
                    {
                        dort1 = qSin(2*pi*((currDate-birth)+i)/33);
                        dort2 = qSin(2*pi*((currDate-birth)+i+diff)/33);
                        //критичнские дни
                        //макс - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxLine)
                        {
                            pntr.setPen(QPen(Qt::green, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //макс - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 100 && maxCross)
                        {
                            pntr.setPen(QPen(Qt::green, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        //мин - крестик
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minCross)
                        {
                            pntr.setPen(QPen(Qt::green, 2));
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        //мин - линия на ось
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == -100 && minLine)
                        {
                            pntr.setPen(QPen(Qt::green, 1));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                        }
                        //неуст - окружность
                        if ((int(i*10))%10 == 0 && qRound(dort1*100) == 0 && nullCircle)
                        {
                            pntr.setPen(QPen(Qt::green, 2));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        //очень критические дни//----------------------------------------------
                        dortCheck1 = qSin(2*pi*((currDate-birth)+i)/28);
                        dortCheck2 = qSin(2*pi*((currDate-birth)+i)/23);
                        if (critMax && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 100 && qRound(dortCheck1*100) == 100)
                                                                   || (qRound(dortCheck1*100) == 100 && qRound(dortCheck2*100) == 100)
                                                                   || (qRound(dort1*100) == 100 && qRound(dortCheck2*100) == 100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH - (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, 15, centerW+((width-30)/80)*i-5, 25);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, 15, centerW+((width-30)/80)*i+5, 25);
                        }
                        else if (critMin && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == -100 && qRound(dortCheck1*100) == -100)
                                                                        || (qRound(dortCheck1*100) == -100 && qRound(dortCheck2*100) == -100)
                                                                        || (qRound(dort1*100) == -100 && qRound(dortCheck2*100) == -100)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawLine(centerW+((width-30)/80)*i, centerH + (height-60)/2, centerW+((width-30)/80)*i, centerH);
                            pntr.drawLine(centerW+((width-30)/80)*i+5, height-5, centerW+((width-30)/80)*i-5, height-15);
                            pntr.drawLine(centerW+((width-30)/80)*i-5, height-5, centerW+((width-30)/80)*i+5, height-15);
                        }
                        else if (critNull && (int(i*10))%10 == 0 && ( (qRound(dort1*100) == 0 && qRound(dortCheck1*100) == 0)
                                                                         || (qRound(dortCheck1*100) == 0 && qRound(dortCheck2*100) == 0)
                                                                         || (qRound(dort1*100) == 0 && qRound(dortCheck2*100) == 0)) )
                        {
                            pntr.setPen(QPen(Qt::yellow, 3));
                            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
                        }
                        if (bold) pntr.setPen(QPen(Qt::green, 2));
                        else pntr.setPen(QPen(Qt::green, 1));
                        pntr.drawLine(centerW+((width-30)/80)*(i), centerH - ((height-60)/2)*dort1, centerW+((width-30)/80)*(i+diff), centerH - ((height-60)/2)*dort2);
                    }
                }
            }
        }
        //============================================================================================


        if (birthdaySwitch)
        {
            int i = birth - currDate;

            pntr.setPen(QPen(Qt::white, 2));

            pntr.drawLine(centerW+((width-30)/80)*(i), (height-60)/9 + 30, centerW+((width-30)/80)*(i), (height-60)/9*2 + 30);
            pntr.drawLine(centerW+((width-30)/80)*(i), (height-60)/9*3 + 30, centerW+((width-30)/80)*(i), (height-60)/9*4 + 30);
            pntr.drawLine(centerW+((width-30)/80)*(i), (height-60)/9*5 + 30, centerW+((width-30)/80)*(i), (height-60)/9*6 + 30);
            pntr.drawLine(centerW+((width-30)/80)*(i), (height-60)/9*7 + 30, centerW+((width-30)/80)*(i), (height-60)/9*8 + 30);
            pntr.drawLine(centerW+((width-30)/80)*(i)-10, 15, centerW+((width-30)/80)*(i), 25);
            pntr.drawLine(centerW+((width-30)/80)*(i)+10, 15, centerW+((width-30)/80)*(i), 25);
            pntr.drawLine(centerW+((width-30)/80)*(i)-10, height-15, centerW+((width-30)/80)*(i), height-25);
            pntr.drawLine(centerW+((width-30)/80)*(i)+10, height-15, centerW+((width-30)/80)*(i), height-25);
            pntr.setPen(QPen(Qt::white, 3));
            pntr.drawEllipse(centerW+((width-30)/80)*i-5, centerH-5, 10, 10);
            QFont _font("font", 10);
            pntr.setFont(_font);
            pntr.drawText(centerW+((width-30)/80)*(i)-43, height-3, "Дата рождения");
        }


    }

    if (cursorTracking)
    {
        QFont _font("font", 7);
        pntr.setFont(_font);
        pntr.setPen(QPen(Qt::gray, 1));
        pntr.drawLine(x, y, x, centerH);
        QString cursorDateOut;
        for (int i = 1; i < 81; i++)
        {
            if (x > (width/80)*(i-1) && x < (width/80)*i)
            {
                cursorDate.inputDate((currDate - 40 + i).outputDate());
                cursorDateOut = cursorDate.outputDate();
            }
        }
        pntr.drawText(x, y, cursorDateOut);
    }
}

void painter::getDates(Date _currDate, Date _birth)
{
    currDate.inputDate(_currDate.outputDate());
    birth.inputDate(_birth.outputDate());
}

void painter::changeFormat(int x) {
    if (x > 0 && x < 4)
    {
        currDate.changeFormat(x);
        birth.changeFormat(x);
        format = x;
    }
}


void painter::mouseMoveEvent(QMouseEvent* event)
{

    x = event->pos().x();
    y = event->pos().y();
    update();
}

void painter::mouseDoubleClickEvent(QMouseEvent* event)
{

    currDate = cursorDate;
    update();
    emit updateInfoSignal();
}
