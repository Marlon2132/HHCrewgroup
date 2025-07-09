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
    static QList<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(year))
        return 29;
    return days[m-1];
}

bool Date::checkDate() const {
    if (year == 0 || month < 1 || month > 12 || day < 1 || day > daysInMonth(month))
        return false;
    return true;
}

int Date::toDays() const {
    int ans = 0;
    if (year > 0) {
        for (int i = 1; i < year; i++) {
            ans += isLeapYear(i) ? 366 : 365;
        }
        for (int i = 1; i < month; i++) {
            ans += daysInMonth(i);
        }
        ans += day - 1;
    }
    else if (year < 0) {
        for (int i = year + 1; i < 0; i++) {
            ans -= isLeapYear(i) ? 366 : 365;
        }
        for (int i = month + 1; i <= 12; i++) {
            ans -= daysInMonth(i);
        }
        ans -= daysInMonth(month) - day + 1;
    }
    return ans;
}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!checkDate()) {
        day = 1;
        month = 1;
        year = 1900;
    }
}

bool Date::isLeapYear() const {
    return isLeapYear(year);
}

void Date::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
    if (!checkDate()) {
        day = 1;
        month = 1;
        year = 1900;
    }
}

void Date::changeFormat(int x) {
    if (x > 0 && x < 4) format = x;
}

void Date::setCurrentDate() {
    QDate current = QDate::currentDate();
    setDate(current.day(), current.month(), current.year());
}

Date Date::currentDate() const {
    QDate current = QDate::currentDate();
    Date date(current.day(), current.month(), current.year());
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
    return abs(other.toDays() - toDays());
}

int Date::daysFromDate() const {
    return differenceInDays(currentDate());
}

void Date::addDays(int delta) {
    if (delta == 0) return;

    if (delta > 0) {
        while (delta > 0) {
            int daysRemaining = daysInMonth(month) - day + 1;
            if (delta < daysRemaining) {
                day += delta;
                delta = 0;
            } else {
                delta -= daysRemaining;
                month++;
                if (month > 12) {
                    month = 1;
                    year++;
                }
                day = 1;
            }
        }
    } else {
        while (delta < 0) {
            if (day > -delta) {
                day += delta;
                delta = 0;
            } else {
                delta += day;
                month--;
                if (month < 1) {
                    month = 12;
                    year--;
                    if (year == 0) year--; // Skip year 0
                }
                day = daysInMonth(month);
            }
        }
    }
}

void Date::inputDate(const QString& inputStr) {
    int oldDay = day;
    int oldMonth = month;
    int oldYear = year;

    if (format == 1) {
        QStringList parts = inputStr.split('.');
        if (parts.count() == 1) {
            day = parts[0].toInt();
        } else if (parts.count() == 2) {
            day = parts[0].toInt();
            month = parts[1].toInt();
        } else if (parts.count() == 3) {
            day = parts[0].toInt();
            month = parts[1].toInt();
            year = parts[2].toInt();
        }
    }
    else if (format == 2) {
        QString lowerStr = inputStr.toLower();
        QStringList tokens = lowerStr.split(QChar(' '), Qt::SkipEmptyParts);

        if (tokens.size() < 3) {
            return;
        }

        static QMap<QString, int> dayMap = {
            {"первое", 1}, {"второе", 2}, {"третье", 3}, /* ... остальные дни ... */
            {"тридцать", 30}, {"тридцать первое", 31}
        };

        static QMap<QString, int> monthMap = {
            {"января", 1}, {"февраля", 2}, /* ... остальные месяцы ... */
            {"декабря", 12}
        };

        // Парсинг дня (может состоять из 1 или 2 слов)
        QString dayStr;
        int currentIndex = 0;
        if (currentIndex < tokens.size()) {
            QString first = tokens[currentIndex];
            if (dayMap.contains(first)) {
                dayStr = first;
                currentIndex++;
            } else if (currentIndex + 1 < tokens.size()) {
                QString combined = first + " " + tokens[currentIndex + 1];
                if (dayMap.contains(combined)) {
                    dayStr = combined;
                    currentIndex += 2;
                } else {
                    return;
                }
            } else {
                return;
            }
        }

        // Парсинг месяца
        QString monthStr;
        if (currentIndex < tokens.size()) {
            monthStr = tokens[currentIndex];
            currentIndex++;
        } else {
            return;
        }

        // Парсинг года
        QString yearStr;
        if (currentIndex < tokens.size()) {
            yearStr = tokens[currentIndex];
            currentIndex++;
        } else {
            return;
        }

        bool ok;
        int parsedYear = yearStr.toInt(&ok);
        if (!ok) return;

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

        // Получаем числовые значения
        day = dayMap.value(dayStr, -1);
        month = monthMap.value(monthStr, -1);
        year = parsedYear;
    }
    else if (format == 3) {
        QStringList parts = inputStr.split('.');
        if (parts.count() == 1) {
            year = parts[0].toInt();
        } else if (parts.count() == 2) {
            year = parts[0].toInt();
            month = parts[1].toInt();
        } else if (parts.count() == 3) {
            year = parts[0].toInt();
            month = parts[1].toInt();
            day = parts[2].toInt();
        }
    }

    /*if (!checkDate()) {
        day = oldDay;
        month = oldMonth;
        year = oldYear;
    }*/
}

QString Date::outputDate() const {
    static QStringList days = {
        "первое", "второе", "третье", /* ... остальные дни ... */
        "тридцатое", "тридцать первое"
    };

    static QStringList months = {
        "января", "февраля", "марта", /* ... остальные месяцы ... */
        "декабря"
    };

    if (!checkDate()) {
        return "Некорректная дата";
    }

    if (format == 1) {
        return QString("%1.%2.%3")
        .arg(day, 2, 10, QChar('0'))
            .arg(month, 2, 10, QChar('0'))
            .arg(year);
    }
    else if (format == 2) {
        QString ret = days[day - 1] + " " + months[month - 1] + " ";
        if (year < 0) {
            ret += QString::number(-year) + " года до нашей эры";
        } else {
            ret += QString::number(year) + " года";
        }
        return ret;
    }
    else if (format == 3) {
        return QString("%1.%2.%3")
        .arg(year)
            .arg(month, 2, 10, QChar('0'))
            .arg(day, 2, 10, QChar('0'));
    }
    return "Неизвестный формат";
}

QString operator<<(QString &strOut, const Date date) {
    strOut = date.outputDate();
    return strOut;
}

QString operator>>(QString strIn, Date &date) {
    date.inputDate(strIn);
    return strIn;
}

bool Date::operator<(const Date& _date) const {
    return toDays() < _date.toDays();
}

bool Date::operator>(const Date& _date) const {
    return toDays() > _date.toDays();
}

bool Date::operator<=(const Date& _date) const {
    return toDays() <= _date.toDays();
}

bool Date::operator>=(const Date& _date) const {
    return toDays() >= _date.toDays();
}

int Date::operator-(Date& date) const {
    return toDays() - date.toDays();
}

int Date::operator+(Date& date) const {
    return toDays() + date.toDays();
}

bool Date::operator==(const Date& _date) const {
    return toDays() == _date.toDays();
}

int Date::toNextBirthday() const {
    Date today = currentDate();
    Date nextBirthday(day, month, today.year);

    if (nextBirthday < today) {
        nextBirthday.year++;
    }

    return today.differenceInDays(nextBirthday);
}
