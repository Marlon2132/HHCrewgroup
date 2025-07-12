// datetimeinputdialog.cpp
#include "datetimeinputdialog.h"
#include "ui_datetimeinputdialog.h"
#include "datetimevalidator.h"
#include "datetimeconverter.h"
#include <QMessageBox>

DateTimeInputDialog::DateTimeInputDialog(InputType type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DateTimeInputDialog)
    , inputType(type)
{
    ui->setupUi(this);

    // Подписи и состояния кнопок
    ui->errorLabel->hide();
    ui->acceptButton->setEnabled(false);
    ui->modeTab->setCurrentIndex(inputType == Numeric ? 0 : 1);

    // Подставляем текущее время
    QDateTime now = QDateTime::currentDateTime();
    ui->currentTimeLabel->setText("Текущее время: " + now.toString("dd.MM.yyyy HH:mm:ss"));

    // Numeric-вкладка
    connect(ui->currentTimeButton, &QPushButton::clicked, this, [=](){
        QDateTime c = QDateTime::currentDateTime();
        ui->dateEdit->setDate(c.date());
        ui->timeEdit->setTime(c.time());
    });
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &DateTimeInputDialog::onConvertClicked);
    connect(ui->timeEdit, &QTimeEdit::timeChanged, this, &DateTimeInputDialog::onConvertClicked);

    // Word-вкладка
    connect(ui->wordInput, &QTextEdit::textChanged, this, &DateTimeInputDialog::onConvertClicked);

    // Общие кнопки
    connect(ui->convertButton, &QPushButton::clicked, this, &DateTimeInputDialog::onConvertClicked);
    connect(ui->acceptButton, &QPushButton::clicked, this, &DateTimeInputDialog::onAcceptClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    // Первый прогон валидации
    onConvertClicked();
}

DateTimeInputDialog::~DateTimeInputDialog()
{
    delete ui;
}

void DateTimeInputDialog::onConvertClicked()
{
    ui->errorLabel->hide();
    bool ok = false;

    if (ui->modeTab->currentIndex() == 0) { // Numeric-вкладка
        QDate d = ui->dateEdit->date();
        QTime t = ui->timeEdit->time();
        QDateTime dt(d, t);
        dateTime = dt;
        QString words = DateTimeConverter::convertToWords(dt);
        ui->numericOutput->setText(words);
        ok = dt.isValid();
    }
    else { // Word-вкладка
        QString txt = ui->wordInput->toPlainText();
        if (DateTimeValidator::validateWordFormat(txt)) {
            // здесь можно заменить на полноценный парсинг
            QDateTime dt = QDateTime::fromString(
                DateTimeConverter::convertToNumeric(txt),
                "dd.MM.yyyy HH:mm:ss");
            dateTime = dt;
            ui->wordsOutput->setText(dt.toString("dd.MM.yyyy HH:mm:ss"));
            ok = dt.isValid();
        } else {
            ui->errorLabel->setText("Неверный словесный формат");
            ui->errorLabel->show();
        }
    }

    ui->acceptButton->setEnabled(ok);
}

void DateTimeInputDialog::onAcceptClicked()
{
    if (!dateTime.isValid()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введите корректное время"));
        return;
    }
    accept();
}


void DateTimeInputDialog::setupValidators() {
    connect(ui->wordInput, &QTextEdit::textChanged,
            this, &DateTimeInputDialog::validateAll);
    connect(ui->dateEdit, &QDateEdit::dateChanged,
            this, &DateTimeInputDialog::validateAll);
    connect(ui->timeEdit, &QTimeEdit::timeChanged,
            this, &DateTimeInputDialog::validateAll);
}

void DateTimeInputDialog::validateAll() {
    bool ok = true;
    if (inputType == Numeric) {
        QDateTime dt;
        ok = DateTimeValidator::validateNumericFormat(
            ui->numericOutput->text(), dt);
    } else {
        ok = DateTimeValidator::validateWordFormat(
            ui->wordInput->toPlainText());
    }
    ui->acceptButton->setEnabled(ok);
    ui->errorLabel->setVisible(!ok);
    if (!ok) ui->errorLabel->setText("Неверный формат");
}

