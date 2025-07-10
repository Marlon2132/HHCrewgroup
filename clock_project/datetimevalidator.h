#ifndef DATETIMEVALIDATOR_H
#define DATETIMEVALIDATOR_H

#include <QObject>
#include <QDateTime>

class DateTimeValidator : public QObject
{
    Q_OBJECT
public:
    explicit DateTimeValidator(QObject *parent = nullptr);

    // Проверка числового формата
    static bool validateNumericFormat(const QString &input, QDateTime &result);

    // Проверка словесного формата (упрощенная)
    static bool validateWordFormat(const QString &input);

    // Логирование ошибок
    static void logError(const QString &error, const QString &input);
};

#endif // DATETIMEVALIDATOR_H
