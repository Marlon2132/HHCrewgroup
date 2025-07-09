#ifndef REQUEST_H
#define REQUEST_H

#include <QtGlobal>
#include <QString>

#pragma pack(push, 1)

struct ReqDates {
    char fullname[30];
    quint8  birthDay;
    quint8  birthMonth;
    quint16 birthYear;
    quint8  calcDay;
    quint8  calcMonth;
    quint16 calcYear;
};

#pragma pack(pop)

#endif // REQUEST_H
