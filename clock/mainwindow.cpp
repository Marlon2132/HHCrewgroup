#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "datetimeinputdialog.h"
#include "datetimeconverter.h"
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем и настраиваем таймер для обновления часов
    clockTimer = new QTimer(this);
    clockTimer->setInterval(1000); // Обновление каждую секунду
    connect(clockTimer, &QTimer::timeout, this, &MainWindow::updateClockDisplay);
    clockTimer->start();
    updateClockDisplay(); // Первоначальное обновление

    // Подключаем пункты меню к слотам
    connect(ui->manually_action, &QAction::triggered, this, &MainWindow::onManualInputTriggered);
    connect(ui->wordly_action, &QAction::triggered, this, &MainWindow::onWordInputTriggered);
    connect(ui->from_timer_action, &QAction::triggered, this, &MainWindow::onTimerInputTriggered);

    // Ручное соединение для помощи
    connect(ui->open_help_action, &QAction::triggered,
            this, &MainWindow::on_open_help_action_triggered);
}

void MainWindow::updateClockDisplay()
{
    QDateTime current = QDateTime::currentDateTime();
    QString words = DateTimeConverter::convertToWords(current);
    ui->clockLabel->setText("Текущее время: " + current.toString("dd.MM.yyyy HH:mm:ss") +
                            "\n" + words);
}

void MainWindow::onManualInputTriggered()
{
    DateTimeInputDialog dialog(DateTimeInputDialog::Numeric, this);
    if (dialog.exec() == QDialog::Accepted) {
        QDateTime dt = dialog.getDateTime();
        // Здесь можно установить время в часах
        updateClockDisplay(); // Обновляем отображение
    }
}

void MainWindow::onWordInputTriggered()
{
    DateTimeInputDialog dialog(DateTimeInputDialog::Word, this);
    if (dialog.exec() == QDialog::Accepted) {
        QDateTime dt = dialog.getDateTime();
        // Здесь можно установить время в часах
        updateClockDisplay(); // Обновляем отображение
    }
}

void MainWindow::onTimerInputTriggered()
{
    // Просто обновляем отображение текущим временем
    updateClockDisplay();
}

void MainWindow::on_open_help_action_triggered()
{
    QMessageBox::information(this, "Помощь",
                             "Часы Дали\n\nФункции программы:\n"
                             "- Отображение текущего времени с автоматическим обновлением\n"
                             "- Ввод времени в числовом формате (ДД.ММ.ГГГГ ЧЧ:ММ:СС)\n"
                             "- Ввод времени в словесном формате\n"
                             "- Примеры ввода на основе реального времени\n"
                             "- Преобразование между форматами в реальном времени");
}

MainWindow::~MainWindow()
{
    delete ui;
}
