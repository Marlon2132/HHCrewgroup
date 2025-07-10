#include "datetimevalidator.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

DateTimeValidator::DateTimeValidator(QObject *parent) : QObject(parent) {}

bool DateTimeValidator::validateNumericFormat(const QString &input, QDateTime &result)
{
    // Регулярное выражение для формата ДД.ММ.ГГГГ ЧЧ:ММ:СС
    QRegularExpression regex("^(\\d{2})\\.(\\d{2})\\.(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})$");
    QRegularExpressionMatch match = regex.match(input);

    if (!match.hasMatch()) {
        logError("Неверный формат", input);
        return false;
    }

    // Извлечение компонентов даты
    int day = match.captured(1).toInt();
    int month = match.captured(2).toInt();
    int year = match.captured(3).toInt();
    int hour = match.captured(4).toInt();
    int minute = match.captured(5).toInt();
    int second = match.captured(6).toInt();

    // Проверка валидности даты
    QDate date(year, month, day);
    QTime time(hour, minute, second);

    if (!date.isValid() || !time.isValid()) {
        logError("Некорректные значения даты/времени", input);
        return false;
    }

    result = QDateTime(date, time);
    return true;
}

bool DateTimeValidator::validateWordFormat(const QString &input)
{
    // Упрощенная проверка - должен содержать ключевые слова
    return input.contains("года") &&
           (input.contains("часов") || input.contains("час")) &&
           (input.contains("минут") || input.contains("минута")) &&
           (input.contains("секунд") || input.contains("секунда"));
}

void DateTimeValidator::logError(const QString &error, const QString &input)
{
    QFile file("datetime_errors.log");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")
            << " | Ошибка: " << error
            << " | Ввод: '" << input << "'\n";
        file.close();
    }
}
