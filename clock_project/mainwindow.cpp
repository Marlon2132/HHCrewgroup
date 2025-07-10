#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStatusBar>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include "datetimeconverter.h"
#include <QPainterPath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем виджет с мягкими часами
    softWatch = new SoftWatchWidget;
    setCentralWidget(softWatch);

    // Таймер для обновления времени
    timer = new QTimer(this);
    timer->start(1000); // Обновление каждую секунду
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    updateTime();

    // Настраиваем меню
    QMenu *timeMenu = menuBar()->addMenu("Время");
    QAction *setTimeAction = timeMenu->addAction("Установить время");
    connect(setTimeAction, &QAction::triggered, this, &MainWindow::showInputDialog);

    QMenu *helpMenu = menuBar()->addMenu("Помощь");
    QAction *helpAction = helpMenu->addAction("О программе");
    connect(helpAction, &QAction::triggered, this, &MainWindow::onHelpTriggered);
}

void MainWindow::updateTime()
{
    QDateTime now = QDateTime::currentDateTime();
    softWatch->setDateTime(now);
}

void MainWindow::showInputDialog()
{
    DateTimeInputDialog dialog(DateTimeInputDialog::Numeric, this);
    if (dialog.exec() == QDialog::Accepted) {
        QDateTime dt = dialog.getDateTime();
        softWatch->setDateTime(dt);
        statusBar()->showMessage(DateTimeConverter::convertToWords(dt));
    }
}

void MainWindow::onHelpTriggered()
{
    QMessageBox::information(this, "О программе",
                             "Часы Дали\n\n"
                             "Особенности программы:\n"
                             "- Реализация часов в стиле Сальвадора Дали\n"
                             "- Мягкие деформирующиеся стрелки\n"
                             "- Поддержка числового и словесного ввода времени\n"
                             "- Автоматическое обновление времени\n\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}
