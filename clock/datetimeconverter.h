#ifndef DATETIMECONVERTER_H
#define DATETIMECONVERTER_H

#include <QString>
#include <QDateTime>

class DateTimeConverter
{
public:
    // Числовой -> Словесный
    static QString convertToWords(const QDateTime &dt);

    // Словесный -> Числовой (упрощенная реализация)
    static QString convertToNumeric(const QString &wordFormat);

private:
    // Вспомогательные функции преобразования чисел в слова
    static QString dayToWord(int day);
    static QString monthToWord(int month);
    static QString yearToWord(int year);
    static QString numberToWord(int number);
    static QString getHourWord(int hour);
    static QString getMinuteWord(int minute);
    static QString getSecondWord(int second);
};

#endif // DATETIMECONVERTER_H
