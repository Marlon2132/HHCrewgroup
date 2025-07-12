// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCalendarWidget>
#include <QTimeEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QAction>
#include "datetimeinputdialog.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    softWatch = new SoftWatchWidget;
    setCentralWidget(softWatch);

    // --- создаём лейбл над виджетом часов
    dateLabel = new QLabel(softWatch);
    dateLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setStyleSheet(
            "color: white;"
            "background: rgba(0, 0, 0, 120);"
            "font-size: 14px;"
            "padding: 4px;"
        );
    // изначально на всю ширину, высота 30px, в левом верхнем углу
        dateLabel->setGeometry(0, 0, softWatch->width(), 30);
    dateLabel->setText(QDate::currentDate().toString("dd.MM.yyyy"));

    loadSettings();

    m_dateTime = QDateTime::currentDateTime();
    timer = new QTimer(this);
    timer->start(50);
    connect(timer, &QTimer::timeout, this, [this](){
        updateTime();
        // каждый тик обновляем положение и текст лейбла
            dateLabel->setText(m_dateTime.date().toString("dd.MM.yyyy"));
        dateLabel->setGeometry(0, 0, softWatch->width(), 30);});

    updateTime();

    connect(ui->helpAction, &QAction::triggered,
            this, &MainWindow::on_helpAction_triggered);
    connect(ui->BGchange1, &QAction::triggered,
            this, &MainWindow::on_BGchange1_triggered);
    connect(ui->BGchange2, &QAction::triggered,
            this, &MainWindow::on_BGchange2_triggered);
    connect(ui->BGchange3, &QAction::triggered,
            this, &MainWindow::on_BGchange3_triggered);
    connect(ui->BGchange4, &QAction::triggered,
            this, &MainWindow::on_BGchange4_triggered);
    connect(ui->BGchange5, &QAction::triggered,
            this, &MainWindow::on_BGchange5_triggered);
    connect(ui->changeDateTimeAction, &QAction::triggered,
            this, &MainWindow::on_changeDateTimeAction_triggered);
}

void MainWindow::updateTime()
{
    m_dateTime = QDateTime::currentDateTime();
    softWatch->setDateTime(m_dateTime);
}



void MainWindow::on_helpAction_triggered()
{
    QMessageBox::information(this, "О программе",
                             "Часы Дали\n\n"
                             "- Мягкие деформирующиеся стрелки\n"
                             "- Отдельный ввод даты и времени через меню\n"
                             "- Поддержка смены фона\n");
}

void MainWindow::on_BGchange1_triggered() { softWatch->setBackgroundImage(":/images/background.jpg"); }
void MainWindow::on_BGchange2_triggered() { softWatch->setBackgroundImage(":/images/bg2.jpg"); }
void MainWindow::on_BGchange3_triggered() { softWatch->setBackgroundImage(":/images/bg3.jpg"); }
void MainWindow::on_BGchange4_triggered() { softWatch->setBackgroundImage(":/images/bg4.jpg"); }
void MainWindow::on_BGchange5_triggered() { softWatch->setBackgroundImage(":/images/bg5.jpg"); }

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::on_changeDateTimeAction_triggered()
{
    // Открываем диалог в заданном режиме (Numeric или Word)
    DateTimeInputDialog dlg(DateTimeInputDialog::Numeric, this);
    if (dlg.exec() == QDialog::Accepted) {
        // Получаем выбранную дату/время и передаём в виджет
        m_dateTime = dlg.getDateTime();
        softWatch->setDateTime(m_dateTime);

        // обновляем надпись с датой/временем
        dateLabel->setText(m_dateTime.toString("dd.MM.yyyy"));
        // Останавливаем системный таймер, если ещё не остановлен
        if (!timerStopped) {
            timer->stop();
            timerStopped = true;
        }
    }
}

void MainWindow::loadSettings()
{
    QSettings s("MyCompany", "SoftClock");
    restoreGeometry(s.value("geometry").toByteArray());
    QByteArray bg = s.value("background").toByteArray();
    if (!bg.isEmpty())
        softWatch->setBackgroundImage(bg);

    bool manual = s.value("manualMode", false).toBool();
    if (manual) {
        QDateTime dt = s.value("manualTime", QDateTime::currentDateTime()).toDateTime();
        softWatch->setDateTime(dt);
    }
}

void MainWindow::saveSettings()
{
    QSettings s("MyCompany", "SoftClock");
    s.setValue("geometry", saveGeometry());
    // какой фон выбран — можно хранить путь последней установки
    // допустим, храним ресурс
    // s.setValue("background", QByteArray(":/images/bg2.jpg"));
    // Аналогично:
    s.setValue("manualMode", softWatch->isManualMode());
    s.setValue("manualTime", softWatch->currentDateTime());
}
