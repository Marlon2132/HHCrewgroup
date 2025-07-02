#ifndef DATE_H
#define DATE_H

#include <QList>
#include <QString>

class Date
{
private:
    int day, month, year;                                             // Поля для записи числа, месяца и года даты
    int format = 1;                                                   // Для определения формата ввода-вывода. 1 - std, 2 - word, 3 - am




    bool isLeapYear(int year) const;                                  // если год в передаваемой дате високосный, возвращает true, иначе false
    int daysInMonth(int m) const;                                     // возвращает количество дней в месяце данной даты

    int toDays() const;                                               // возвращает количество дней от определенной точки (вспомогательная функция для вычисления разницы между датами в днях)

public:
    Date(int d = 1, int m = 1, int y = 1900);                         // конструктор
    void setDate(int d, int m, int y);                                // изменить дату
    bool isLeapYear() const;                                          // если год в данной дате високосный, возвращает true, иначе false
    void changeFormat(int x = 1);                                     // для определения формата ввода-вывода даты
    bool checkDate() const;                        // проверяет правильность даты

    void setCurrentDate();                                            // присваивает объекту Date текущую дату
    Date currentDate() const ;                                        // возвращает текущую дату
    int differenceInDays(const Date& other) const;                    // возвращает разницу между датами в днях
    int daysFromDate() const;                                         // возвращает, сколько дней прошло с передаваемой даты
    void addDays(int delta);                                          // добавляет к дате delta дней
    void inputDate(const QString& inputStr);                          // средство для ввода даты в одном из трех форматов
    QString outputDate() const;                                       // средство для вывода даты в одном из трех форматов
    int toNextBirthday() const;



    Date operator+(int days) const;                                   // перегрузка + для прибавления количества дней к числу
    Date operator-(int days) const;                                   // перегрузка - для отнимания от даты числа дней
    int operator-(Date& date) const;
    int operator+(Date& date) const;

    friend QString operator<<(QString &strOut, const Date date);
    friend QString operator>>(QString strIn, Date &date);
    bool operator>(const Date& _date) const;
    bool operator<(const Date& _date) const;
    bool operator>=(const Date& _date) const;
    bool operator<=(const Date& _date) const;
    bool operator==(const Date& _date) const;
};

#endif // DATE_H
