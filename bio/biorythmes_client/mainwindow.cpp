#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include "date.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализируем поля
    ui->birthDateEdit->setDate(QDate::currentDate());
    ui->calcDateEdit ->setDate(QDate::currentDate());

    // Кнопка «Запросить» теперь «Построить»
    connect(ui->requestButton, &QPushButton::clicked,
            this, &MainWindow::on_requestButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_requestButton_clicked() {
    // Считаем пользовательские даты
    QDate qBirth = ui->birthDateEdit->date();
    QDate qCalc  = ui->calcDateEdit->date();

    // Переводим в ваш Date
    Date birth, calc;
    birth.inputDate(qBirth.toString("dd.MM.yyyy"));
    calc .inputDate(qCalc .toString("dd.MM.yyyy"));

    // Передаём в painter
    ui->painter->getDates(calc, birth);
    ui->painter->firstLaunch = true;
    ui->painter->update();

    ui->statusLabel->setText("График обновлён");
}
