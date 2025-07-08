#ifndef REQUEST_H
#define REQUEST_H

#include <QtGlobal>

#pragma pack(push, 1)

struct ReqDates {
    quint8  birthDay;
    quint8  birthMonth;
    quint16 birthYear;
    quint8  calcDay;
    quint8  calcMonth;
    quint16 calcYear;
};

#pragma pack(pop)

#endif // REQUEST_H
