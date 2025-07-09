#ifndef RECORDS_H
#define RECORDS_H

#include <QtGlobal>    // для quint8, quint16

// Гарантируем упаковку без выравнивания
#pragma pack(push, 1)

/// Структура запроса от клиента
struct Request {
    char fullName[30]; // ФИО 30 байт
    quint8 birthDay;       // день рождения (1 байт)
    quint8 birthMonth;     // месяц рождения (1 байт)
    quint16 birthYear;      // год рождения (2 байта)
    quint8 calcDay;        // день расчёта (1 байт)
    quint8 calcMonth;      // месяц расчёта (1 байт)
    quint16 calcYear;       // год расчёта (2 байта)
};

/// Запись в базе данных
struct PersonRecord {
    char fullName[30];   // ФИО ровно 30 байт
    quint8 birthDay;       // 1 байт
    quint8 birthMonth;     // 1 байт
    quint16 birthYear;      // 2 байта
    quint8 calcDay;        // 1 байт
    quint8 calcMonth;      // 1 байт
    quint16 calcYear;       // 2 байта
    quint16 daysLived;      // число прожитых дней (2 байта)
    float values[3];      // три float-значения
};

#pragma pack(pop)

#endif // RECORDS_H
