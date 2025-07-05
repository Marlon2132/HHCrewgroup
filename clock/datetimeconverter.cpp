#include "datetimeconverter.h"
#include <QStringList>

QString DateTimeConverter::convertToWords(const QDateTime &dt)
{
    return dayToWord(dt.date().day()) + " " +
           monthToWord(dt.date().month()) + " " +
           yearToWord(dt.date().year()) + " года " +
           numberToWord(dt.time().hour()) + " " + getHourWord(dt.time().hour()) + " " +
           numberToWord(dt.time().minute()) + " " + getMinuteWord(dt.time().minute()) + " " +
           numberToWord(dt.time().second()) + " " + getSecondWord(dt.time().second());
}

QString DateTimeConverter::convertToNumeric(const QString &wordFormat)
{
    // Упрощенная реализация - в реальном проекте потребуется сложный парсинг
    // Здесь просто возвращаем текущую дату для примера
    return QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");
}

QString DateTimeConverter::dayToWord(int day)
{
    static QStringList days = {
        "", "первого", "второго", "третьего", "четвертого", "пятого",
        "шестого", "седьмого", "восьмого", "девятого", "десятого",
        "одиннадцатого", "двенадцатого", "тринадцатого", "четырнадцатого", "пятнадцатого",
        "шестнадцатого", "семнадцатого", "восемнадцатого", "девятнадцатого", "двадцатого",
        "двадцать первого", "двадцать второго", "двадцать третьего", "двадцать четвертого",
        "двадцать пятого", "двадцать шестого", "двадцать седьмого", "двадцать восьмого",
        "двадцать девятого", "тридцатого", "тридцать первого"
    };
    return (day >= 1 && day <= 31) ? days[day] : "?";
}

QString DateTimeConverter::monthToWord(int month)
{
    static QStringList months = {
        "", "января", "февраля", "марта", "апреля", "мая", "июня",
        "июля", "августа", "сентября", "октября", "ноября", "декабря"
    };
    return (month >= 1 && month <= 12) ? months[month] : "?";
}

QString DateTimeConverter::yearToWord(int year)
{
    // Упрощенная реализация
    return QString::number(year);
}

QString DateTimeConverter::numberToWord(int number)
{
    static QStringList units = {
        "ноль", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять",
        "десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать",
        "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"
    };

    static QStringList tens = {
        "", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят"
    };

    if (number < 20) return units[number];
    if (number < 60) return tens[number / 10] + ((number % 10) ? " " + units[number % 10] : "");
    return "?";
}

QString DateTimeConverter::getHourWord(int hour)
{
    if (hour % 100 >= 11 && hour % 100 <= 14) return "часов";
    switch (hour % 10) {
    case 1: return "час";
    case 2:
    case 3:
    case 4: return "часа";
    default: return "часов";
    }
}

QString DateTimeConverter::getMinuteWord(int minute)
{
    if (minute % 100 >= 11 && minute % 100 <= 14) return "минут";
    switch (minute % 10) {
    case 1: return "минута";
    case 2:
    case 3:
    case 4: return "минуты";
    default: return "минут";
    }
}

QString DateTimeConverter::getSecondWord(int second)
{
    if (second % 100 >= 11 && second % 100 <= 14) return "секунд";
    switch (second % 10) {
    case 1: return "секунда";
    case 2:
    case 3:
    case 4: return "секунды";
    default: return "секунд";
    }
}
