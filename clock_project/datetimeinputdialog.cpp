// datetimeinputdialog.cpp
#include "datetimeinputdialog.h"
#include "ui_datetimeinputdialog.h"
#include "datetimevalidator.h"
#include "datetimeconverter.h"
#include <QMessageBox>
#include <QDateTime>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QTimeEdit>

DateTimeInputDialog::DateTimeInputDialog(InputType type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DateTimeInputDialog)
    , inputType(type)
{
    ui->setupUi(this);

    QDateTime current = QDateTime::currentDateTime();
    QString exampleWords = DateTimeConverter::convertToWords(current);

    // Настройка существующих виджетов из .ui
    ui->dateEdit->setDate(current.date());
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDisplayFormat("dd.MM.yyyy");

    ui->timeEdit->setTime(current.time());
    ui->timeEdit->setDisplayFormat("HH:mm:ss");

    if (inputType == Numeric) {
        setWindowTitle("Числовой ввод даты/времени");
        ui->wordInput->hide();
        ui->wordLabel->hide();
        ui->numericOutput->hide();
        ui->numericLabel->hide();
        ui->convertButton->setText("Преобразовать в слова");

        connect(ui->convertButton, &QPushButton::clicked,
                this, &DateTimeInputDialog::onConvertClicked);
        connect(ui->dateEdit, &QDateEdit::dateChanged,
                this, [this](const QDate &d){
                    dateTime.setDate(d);
                    emit dateTimeChanged(dateTime);
                    onConvertClicked();
                });
        connect(ui->timeEdit, &QTimeEdit::timeChanged,
                this, [this](const QTime &t){
                    dateTime.setTime(t);
                    emit dateTimeChanged(dateTime);
                    onConvertClicked();
                });
    }
    else {
        setWindowTitle("Словесный ввод даты/времени");
        ui->numericOutput->hide();
        ui->numericLabel->hide();
        ui->wordsOutput->hide();
        ui->wordsLabel->hide();
        ui->wordInput->setPlaceholderText("Пример: " + exampleWords);
        ui->wordInput->setPlainText(exampleWords);
        ui->convertButton->setText("Преобразовать в дату/время");
        connect(ui->convertButton, &QPushButton::clicked,
                this, &DateTimeInputDialog::onConvertClicked);
        ui->dateEdit->hide();
        ui->timeEdit->hide();
    }

    connect(ui->acceptButton, &QPushButton::clicked,
            this, &DateTimeInputDialog::onAcceptClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &QDialog::reject);
}

DateTimeInputDialog::~DateTimeInputDialog()
{
    delete ui;
}

void DateTimeInputDialog::onConvertClicked()
{
    if (inputType == Numeric) {
        QString words = DateTimeConverter::convertToWords(dateTime);
        ui->wordsOutput->setText(words);
    } else {
        if (DateTimeValidator::validateWordFormat(ui->wordInput->toPlainText())) {
            QDateTime dt = QDateTime::currentDateTime(); // заглушка
            ui->numericOutput->setText(dt.toString("dd.MM.yyyy HH:mm:ss"));
            emit dateTimeChanged(dt);
        } else {
            ui->numericOutput->setText("Неверный формат!");
        }
    }
}
void DateTimeInputDialog::onAcceptClicked()
{
    if (inputType == Numeric && !dateTime.isValid()) {
        QMessageBox::warning(this,
                             tr("Ошибка"),
                             tr("Введите корректные дату и время"));
        return;
    }
    accept();
}
