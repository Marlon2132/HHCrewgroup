#include "datetimeconverter.h"
#include <QStringList>
#include <QRegularExpression>
#include <QMap>
#include <QDateTime>
#include <QDate>
#include <QTime>

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
    QString s = wordFormat.trimmed().toLower();

    // 1) Обратные словари для дней и месяцев
    static QMap<QString,int> dayMap;
    static QMap<QString,int> monthMap;
    if (dayMap.isEmpty()) {
        // генитивные формы из dayToWord()
        for (int d = 1; d <= 31; ++d) {
            dayMap[ dayToWord(d) ] = d;
        }
        // именительные формы для дня (номинатив)
        static QStringList nomDays = {
            "", "первое", "второе", "третье", "четвёртое", "пятое",
            "шестое", "седьмое", "восьмое", "девятое", "десятое",
            "одиннадцатое", "двенадцатое", "тринадцатое", "четырнадцатое", "пятнадцатое",
            "шестнадцатое", "семнадцатое", "восемнадцатое", "девятнадцатое", "двадцатое",
            "двадцать первое", "двадцать второе", "двадцать третье", "двадцать четвёртое",
            "двадцать пятое", "двадцать шестое", "двадцать седьмое", "двадцать восьмое",
            "двадцать девятое", "тридцатое", "тридцать первое"
        };
        for (int d = 1; d <= 31; ++d) {
            dayMap[ nomDays[d] ] = d;
        }
    }
    if (monthMap.isEmpty()) {
        for (int m = 1; m <= 12; ++m)
            monthMap[ monthToWord(m) ] = m;
    }

    // 2) Парсим день, месяц, год
    QRegularExpression dateRe(R"((\D+?)\s+(января|февраля|марта|апреля|мая|июня|июля|августа|сентября|октября|ноября|декабря)\s+(\d{4})\s+года)");
    auto dateMatch = dateRe.match(s);
    if (!dateMatch.hasMatch())
        return QString();

    QString dayWord   = dateMatch.captured(1).trimmed();
    QString monthWord = dateMatch.captured(2);
    int year   = dateMatch.captured(3).toInt();
    int day    = dayMap.value(dayWord, 0);
    int month  = monthMap.value(monthWord, 0);

    // 3) Парсим часы
    QRegularExpression hourRe(R"((\d{1,2})\s+час)");
    auto hMatch = hourRe.match(s, dateMatch.capturedEnd());
    if (!hMatch.hasMatch())
        return QString();
    int hour = hMatch.captured(1).toInt();

    // 4) Минуты (опционально)
    QRegularExpression minRe(R"((\d{1,2})\s+минут)");
    auto mMatch = minRe.match(s, hMatch.capturedEnd());
    int minute = mMatch.hasMatch() ? mMatch.captured(1).toInt() : 0;

    // 5) Секунды (опционально)
    QRegularExpression secRe(R"((\d{1,2})\s+секунд)");
    auto sMatch = secRe.match(s, mMatch.hasMatch() ? mMatch.capturedEnd() : hMatch.capturedEnd());
    int second = sMatch.hasMatch() ? sMatch.captured(1).toInt() : 0;

    // 6) Собираем дату/время
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    if (!date.isValid() || !time.isValid())
        return QString();

    return QDateTime(date, time).toString("dd.MM.yyyy HH:mm:ss");
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
    return (day >= 1 && day <= 31) ? days[day] : QString("?");
}

QString DateTimeConverter::monthToWord(int month)
{
    static QStringList months = {
        "", "января", "февраля", "марта", "апреля", "мая", "июня",
        "июля", "августа", "сентября", "октября", "ноября", "декабря"
    };
    return (month >= 1 && month <= 12) ? months[month] : QString("?");
}

QString DateTimeConverter::yearToWord(int year)
{
    return QString::number(year);
}

QString DateTimeConverter::numberToWord(int number)
{
    static QStringList units = {
        "ноль", "один", "два", "три", "четыре",
        "пять", "шесть", "семь", "восемь", "девять",
        "десять", "одиннадцать", "двенадцать", "тринадцать",
        "четырнадцать", "пятнадцать", "шестнадцать",
        "семнадцать", "восемнадцать", "девятнадцать"
    };
    static QStringList tens = {
        "", "", "двадцать", "тридцать", "сорок",
        "пятьдесят", "шестьдесят"
    };

    if (number < 20)
        return units[number];
    if (number < 60) {
        int t = number / 10;
        int u = number % 10;
        return tens[t] + (u ? " " + units[u] : "");
    }
    return QString("?");
}

QString DateTimeConverter::getHourWord(int hour)
{
    if (hour % 100 >= 11 && hour % 100 <= 14) return "часов";
    switch (hour % 10) {
    case 1:  return "час";
    case 2:
    case 3:
    case 4:  return "часа";
    default: return "часов";
    }
}

QString DateTimeConverter::getMinuteWord(int minute)
{
    if (minute % 100 >= 11 && minute % 100 <= 14) return "минут";
    switch (minute % 10) {
    case 1:  return "минута";
    case 2:
    case 3:
    case 4:  return "минуты";
    default: return "минут";
    }
}

QString DateTimeConverter::getSecondWord(int second)
{
    if (second % 100 >= 11 && second % 100 <= 14) return "секунд";
    switch (second % 10) {
    case 1:  return "секунда";
    case 2:
    case 3:
    case 4:  return "секунды";
    default: return "секунд";
    }
}
