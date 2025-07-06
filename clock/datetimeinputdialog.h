#ifndef DATETIMEINPUTDIALOG_H
#define DATETIMEINPUTDIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>

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

private slots:
    void onConvertClicked();
    void onAcceptClicked();
    void updateCurrentTimeDisplay();

private:
    Ui::DateTimeInputDialog *ui;
    InputType inputType;
    QDateTime dateTime;
    QString wordFormat;
    QTimer *timer;
};

#endif // DATETIMEINPUTDIALOG_H
