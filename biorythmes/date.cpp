#include "date.h"

#include <QDate>
#include <QChar>
#include <QString>
#include <QStringList>
#include <QMap>

bool Date::isLeapYear(int y) const {
    if (y % 4 != 0) return false;
    if (y % 100 != 0) return true;
    return (y % 400 == 0);
}

int Date::daysInMonth(int m) const {
    static QList<int> days = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeapYear()) return 29;
    return days[m-1];
}

bool Date::checkDate(int d, int m, int y) const {
    if (y == 0) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > daysInMonth(m)) return 0;
    return 1;
}

int Date::toDays() const {
    int ans = 0;
    if (year > 0)
    {
        for (int i = 1; i < year; i++)
        {
            if (isLeapYear(i))
            {
                ans += 366;
            }
            else
            {
                ans += 365;
            }
        }
        for (int i = 1; i < month; i++)
        {
            ans += daysInMonth(i);
        }
        ans += day;
        ans -= 1;
    }
    else if (year < 0)
    {
        for (int i = year+1; i < 0; i++)
        {
            if (isLeapYear(i))
            {
                ans -= 366;
            }
            else
            {
                ans -= 365;
            }
        }
        for (int i = month+1; i <= 12; i++)
        {
            ans -= daysInMonth(i);
        }
        ans -= daysInMonth(month);
        ans += day;
        ans += 1;
    }
    return ans;
}

Date::Date(int d, int m, int y) : format(1) {
    if (checkDate(d, m, y)) {
        day = d;
        month = m;
        year = y;
    }
}

bool Date::isLeapYear() const {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    return (year % 400 == 0);
}

void Date::setDate(int d, int m, int y) {
    if (checkDate(d, m, y)) {
        day = d;
        month = m;
        year = y;
    }
}

void Date::changeFormat(int x) {
    if (x > 0 && x < 4) format = x;
}

void Date::setCurrentDate() {
    QDate current = QDate::currentDate();
    day = current.day();
    month = current.month();
    year = current.year();
}

Date Date::currentDate() const {
    Date date(QDate::currentDate().day(), QDate::currentDate().month(), QDate::currentDate().year());
    date.changeFormat(format);
    return date;
}

Date Date::operator+(int days) const {
    Date temp(*this);
    temp.addDays(days);
    return temp;
}

Date Date::operator-(int days) const {
    Date temp(*this);
    temp.addDays(-days);
    return temp;
}

int Date::differenceInDays(const Date& other) const {
    if (other.toDays() >= toDays()) return other.toDays() - toDays();
    else return toDays() - other.toDays();
}

int Date::daysFromDate() const {
    return differenceInDays(currentDate());
}

void Date::addDays(int delta) {

    if (delta == 0) return;
    if (delta > 0)
    {
        while (delta != 0)
        {
            int toTheEndOfMonth = daysInMonth(month) - day;
            if (delta <= toTheEndOfMonth)
            {
                day += delta;
                delta = 0;
            }
            else {
                delta -= toTheEndOfMonth;
                delta -= 1;
                month++;
                day = 1;
                if (month > 12)
                {
                    month = 1;
                    year++;
                }
            }
        }
    }
    else
    {
        while (delta != 0)
        {
            if (-delta < day)
            {
                day += delta;
                delta = 0;
            }
            else
            {
                delta += day;
                month--;
                if (month < 1)
                {
                    month = 12;
                    if (year == 1)
                    {
                        year -= 2;
                    }
                    else
                    {
                        year--;
                    }
                }
                day = daysInMonth(month);
            }
        }
    }
}



void Date::inputDate(const QString& inputStr) {

    int resDay = day, resMonth = month, resYear = year;

    if (format == 1) {
        QStringList parts = inputStr.split('.');
        if(parts.count() == 1 && checkDate(parts[0].toInt(), month, year)) {
            day = parts[0].toInt();
        }
        else if(parts.count() == 2 && checkDate(parts[0].toInt(), parts[1].toInt(), year)) {
            day = parts[0].toInt();
            month = parts[1].toInt();
        }
        else if(parts.count() == 3 && checkDate(parts[0].toInt(), parts[1].toInt(), parts[2].toInt())) {
            day = parts[0].toInt();
            month = parts[1].toInt();
            year = parts[2].toInt();
        }
    }
    else if(format == 2) {

        QString lowerStr = inputStr.toLower();
        QStringList tokens = lowerStr.split(QChar(' '), Qt::SkipEmptyParts);

        if (tokens.size() < 3) {
            return; // Недостаточно токенов для разбора
        }

        QMap<QString, int> dayMap;
        dayMap["первое"] = 1;
        dayMap["второе"] = 2;
        dayMap["третье"] = 3;
        dayMap["четвертое"] = 4;
        dayMap["пятое"] = 5;
        dayMap["шестое"] = 6;
        dayMap["седьмое"] = 7;
        dayMap["восьмое"] = 8;
        dayMap["девятое"] = 9;
        dayMap["десятое"] = 10;
        dayMap["одиннадцатое"] = 11;
        dayMap["двенадцатое"] = 12;
        dayMap["тринадцатое"] = 13;
        dayMap["четырнадцатое"] = 14;
        dayMap["пятнадцатое"] = 15;
        dayMap["шестнадцатое"] = 16;
        dayMap["семнадцатое"] = 17;
        dayMap["восемнадцатое"] = 18;
        dayMap["девятнадцатое"] = 19;
        dayMap["двадцатое"] = 20;
        dayMap["двадцать первое"] = 21;
        dayMap["двадцать второе"] = 22;
        dayMap["двадцать третье"] = 23;
        dayMap["двадцать четвертое"] = 24;
        dayMap["двадцать пятое"] = 25;
        dayMap["двадцать шестое"] = 26;
        dayMap["двадцать седьмое"] = 27;
        dayMap["двадцать восьмое"] = 28;
        dayMap["двадцать девятое"] = 29;
        dayMap["тридцатое"] = 30;
        dayMap["тридцать первое"] = 31;
        QMap<QString, int> monthMap;
        monthMap["января"] = 1;
        monthMap["февраля"] = 2;
        monthMap["марта"] = 3;
        monthMap["апреля"] = 4;
        monthMap["мая"] = 5;
        monthMap["июня"] = 6;
        monthMap["июля"] = 7;
        monthMap["августа"] = 8;
        monthMap["сентября"] = 9;
        monthMap["октября"] = 10;
        monthMap["ноября"] = 11;
        monthMap["декабря"] = 12;

        int currentIndex = 0;
        QString dayStr;

        // Обработка дня (может состоять из одного или двух слов)
        if (currentIndex < tokens.size()) {
            QString first = tokens[currentIndex];
            if (dayMap.contains(first)) {
                dayStr = first;
                currentIndex++;
            } else {
                if (currentIndex + 1 < tokens.size()) {
                    QString combined = first + " " + tokens[currentIndex + 1];
                    if (dayMap.contains(combined)) {
                        dayStr = combined;
                        currentIndex += 2;
                    } else {
                        return; // Не удалось распознать день
                    }
                } else {
                    return; // Недостаточно токенов для дня
                }
            }
        } else {
            return;
        }

        // Обработка месяца
        QString monthStr;
        if (currentIndex < tokens.size()) {
            monthStr = tokens[currentIndex];
            currentIndex++;
        } else {
            return;
        }

        // Обработка года
        QString yearStr;
        if (currentIndex < tokens.size()) {
            yearStr = tokens[currentIndex];
            currentIndex++;
        } else {
            return;
        }

        bool ok;
        int parsedYear = yearStr.toInt(&ok);
        if (!ok) {
            return; // Год не является числом
        }

        // Проверка на "до н.э."
        bool isBC = false;
        for (int i = currentIndex; i < tokens.size(); ++i) {
            if (tokens[i] == "до") {
                isBC = true;
                break;
            }
        }

        if (isBC) {
            parsedYear = -parsedYear;
        }

        // Получаем числовые значения дня и месяца
        int parsedDay = dayMap.value(dayStr, -1);
        int parsedMonth = monthMap.value(monthStr, -1);

        // Записываем результаты
        day = parsedDay;
        month = parsedMonth;
        year = parsedYear;
    }
    else if(format == 3) {
        QStringList parts = inputStr.split('.');
        if(parts.count() == 1 && checkDate(day, month, parts[0].toInt())) {
            year = parts[0].toInt();
        }
        else if(parts.count() == 2 && checkDate(day, parts[1].toInt(), parts[0].toInt())) {
            year = parts[0].toInt();
            month = parts[1].toInt();
        }
        else if(parts.count() == 3 && checkDate(parts[2].toInt(), parts[1].toInt(), parts[0].toInt())) {
            year = parts[0].toInt();
            month = parts[1].toInt();
            day = parts[2].toInt();
        }
    }


    if (!checkDate(day, month, year)) {
        day = resDay;
        month = resMonth;
        year = resYear;
    }

}

QString Date::outputDate() const {
    QStringList days = {"первое", "второе", "третье", "четвертое", "пятое", "шестое", "седьмое", "восьмое",
                        "девятое", "десятое", "одиннадцатое", "двенадцатое", "тринадцатое", "четырнадцатое",
                        "пятнадцатое","шестнадцатое","семнадцатое", "восемнадцатое", "девятнадцатое", "двадцатое",
                        "двадцать первое", "двадцать второе", "двадцать третье","двадцать четвертое", "двадцать пятое",
                        "двадцать шестое", "двадцать седьмое", "двадцать восьмое","двадцать девятое", "тридцатое",
                        "тридцать первое"};
    QStringList months = {"января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября",
                          "октября", "ноября", "декабря"};




    if (format == 1) {
        QString ret;
        if (day > 0 && day < 10) ret += '0';
        ret += QString::number(day);
        ret += '.';
        if (month > 0 && month < 10) ret += '0';
        ret += QString::number(month);
        ret += '.';
        ret += QString::number(year);
        return ret;
    }
    else if (format == 2) {
        QString ret;
        ret += days[day - 1];
        ret += ' ';
        ret += months[month - 1];
        ret += ' ';
        if (year < 0) {
            int year1 = year;
            year1 *= -1;
            ret += QString::number(year1);
        }
        else {
            ret += QString::number(year);
        }
        ret += " года";
        if (year < 0) {
            ret += " до нашей эры";
        }
        return ret;
    }
    else if (format == 3) {
        QString ret;
        ret += QString::number(year);
        ret += '.';
        if (month > 0 && month < 10) ret += '0';
        ret += QString::number(month);
        ret += '.';
        if (day > 0 && day < 10) ret += '0';
        ret += QString::number(day);
        return ret;
    }
    else return QString("Never used branch is used?!");
}

QString operator<<(QString &strOut, const Date date) {
    strOut = date.outputDate();
    return strOut;
}

QString operator>>(QString strIn, Date &date) {
    date.inputDate(strIn);
    return strIn;
}

bool Date::operator<(const Date& _date) const
{
    return toDays() < _date.toDays();
}

bool Date::operator>(const Date& _date) const
{
    return toDays() > _date.toDays();
}

bool Date::operator<=(const Date& _date) const
{
    return toDays() <= _date.toDays();
}

bool Date::operator>=(const Date& _date) const
{
    return toDays() >= _date.toDays();
}

int Date::operator-(Date& date) const
{
    return toDays()-date.toDays();
}

int Date::operator+(Date& date) const
{
    return toDays() + date.toDays();
}

bool Date::operator==(const Date& _date) const
{
    if (toDays() == _date.toDays()) return 1;
    return 0;
}

int Date::toNextBirthday() const
{
    Date dateB1(day, month, year + 1);
    Date dateB2(day, month, year);
    return dateB1 - dateB2;
}
