// datetimeinputdialog.h
#ifndef DATETIMEINPUTDIALOG_H
#define DATETIMEINPUTDIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>

// Добавляем предварительные объявления
class QDateEdit;
class QTimeEdit;

namespace Ui {
class DateTimeInputDialog;
}

class DateTimeInputDialog : public QDialog
{
    Q_OBJECT

public:
    enum InputType { Numeric, Word };

    explicit DateTimeInputDialog(InputType type, QWidget *parent = nullptr);
    ~DateTimeInputDialog();

    QDateTime getDateTime() const { return dateTime; }
    QString getWordFormat() const { return wordFormat; }

signals:
    void dateTimeChanged(const QDateTime &dt); // Добавляем сигнал

private slots:
    void onConvertClicked();
    void onAcceptClicked();
    void setupValidators();
    void validateAll();

private:
    Ui::DateTimeInputDialog *ui;
    InputType inputType;
    QDateTime dateTime;
    QString wordFormat;
    QTimer *timer;
};

#endif // DATETIMEINPUTDIALOG_H
