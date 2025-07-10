#include "datetimeinputdialog.h"
#include "ui_datetimeinputdialog.h"
#include "datetimevalidator.h"
#include "datetimeconverter.h"
#include <QMessageBox>
#include <QDateTime>
#include <QPainterPath>

DateTimeInputDialog::DateTimeInputDialog(InputType type, QWidget *parent)
    : QDialog(parent), ui(new Ui::DateTimeInputDialog), inputType(type)
{
    ui->setupUi(this);

    // Создаем и настраиваем таймер для обновления времени
    timer = new QTimer(this);
    timer->setInterval(1000); // Обновление каждую секунду
    connect(timer, &QTimer::timeout, this, &DateTimeInputDialog::updateCurrentTimeDisplay);
    timer->start();
    updateCurrentTimeDisplay(); // Первоначальное обновление

    // Получаем текущую дату и время
    QDateTime current = QDateTime::currentDateTime();
    QString exampleNumeric = current.toString("dd.MM.yyyy HH:mm:ss");
    QString exampleWords = DateTimeConverter::convertToWords(current);

    if (inputType == Numeric) {
        setWindowTitle("Числовой ввод даты/времени");

        // Настройка интерфейса для числового ввода
        ui->wordInput->hide();
        ui->wordLabel->hide();
        ui->numericOutput->hide();
        ui->numericLabel->hide();

        // Установка примера ввода
        ui->numericInput->setPlaceholderText("Пример: " + exampleNumeric);
        ui->numericInput->setText(exampleNumeric); // Автозаполнение примером

        ui->convertButton->setText("Преобразовать в слова");
        connect(ui->convertButton, &QPushButton::clicked, this, &DateTimeInputDialog::onConvertClicked);
    } else {
        setWindowTitle("Словесный ввод даты/времени");

        // Настройка интерфейса для словесного ввода
        ui->numericInput->hide();
        ui->numericLabel->hide();
        ui->wordsOutput->hide();
        ui->wordsLabel->hide();

        // Установка примера ввода
        ui->wordInput->setPlaceholderText("Пример: " + exampleWords);
        ui->wordInput->setPlainText(exampleWords); // Автозаполнение примером

        ui->convertButton->setText("Преобразовать в дату/время");
        connect(ui->convertButton, &QPushButton::clicked, this, &DateTimeInputDialog::onConvertClicked);
    }

    // Добавляем кнопку для вставки текущего времени (только для числового ввода)
    ui->currentTimeBtn->setVisible(inputType == Numeric);
    connect(ui->currentTimeBtn, &QPushButton::clicked, this, [=](){
        ui->numericInput->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"));
        onConvertClicked(); // Автоматическое преобразование
    });

    connect(ui->acceptButton, &QPushButton::clicked, this, &DateTimeInputDialog::onAcceptClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

DateTimeInputDialog::~DateTimeInputDialog()
{
    delete ui;
}

void DateTimeInputDialog::updateCurrentTimeDisplay()
{
    QDateTime now = QDateTime::currentDateTime();
    QString currentTime = now.toString("dd.MM.yyyy HH:mm:ss");
    QString currentWords = DateTimeConverter::convertToWords(now);

    ui->currentTimeLabel->setText("Текущее время: " + currentTime +
                                  "\n" + currentWords);
}

void DateTimeInputDialog::onConvertClicked()
{
    if (inputType == Numeric) {
        if (DateTimeValidator::validateNumericFormat(ui->numericInput->text(), dateTime)) {
            wordFormat = DateTimeConverter::convertToWords(dateTime);
            ui->wordsOutput->setText(wordFormat);
        } else {
            ui->wordsOutput->setText("Ошибка в формате или значениях!");
        }
    } else {
        if (DateTimeValidator::validateWordFormat(ui->wordInput->toPlainText())) {
            // В реальной реализации здесь должен быть парсинг словесного формата
            dateTime = QDateTime::currentDateTime(); // Заглушка
            ui->numericOutput->setText(dateTime.toString("dd.MM.yyyy HH:mm:ss"));
        } else {
            ui->numericOutput->setText("Неверный словесный формат!");
        }
    }
}

void DateTimeInputDialog::onAcceptClicked()
{
    if (inputType == Numeric && !dateTime.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные дату и время");
        return;
    }

    accept();
}
