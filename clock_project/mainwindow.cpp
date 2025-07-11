// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCalendarWidget>
#include <QTimeEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    softWatch = new SoftWatchWidget;
    setCentralWidget(softWatch);

    m_dateTime = QDateTime::currentDateTime();
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    updateTime();

    connect(ui->setDateAction, &QAction::triggered,
            this, &MainWindow::on_setDateAction_triggered);
    connect(ui->setTimeAction, &QAction::triggered,
            this, &MainWindow::on_setTimeAction_triggered);
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
}

void MainWindow::updateTime()
{
    m_dateTime = QDateTime::currentDateTime();
    softWatch->setDateTime(m_dateTime);
}

void MainWindow::on_setDateAction_triggered()
{
    QDialog dlg(this);
    dlg.setWindowTitle("Выберите дату");
    QVBoxLayout *lay = new QVBoxLayout(&dlg);
    QCalendarWidget *cal = new QCalendarWidget(&dlg);
    cal->setSelectedDate(m_dateTime.date());
    lay->addWidget(cal);
    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,
                                                 Qt::Horizontal, &dlg);
    lay->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    if (dlg.exec() == QDialog::Accepted) {
        m_dateTime.setDate(cal->selectedDate());
        softWatch->setDateTime(m_dateTime);
    }

    if (!timerStopped) {
        timer->stop();
       timerStopped = true;
    }
}

void MainWindow::on_setTimeAction_triggered()
{
    QDialog dlg(this);
    dlg.setWindowTitle("Выберите время");
    QVBoxLayout *lay = new QVBoxLayout(&dlg);
    QTimeEdit *te = new QTimeEdit(m_dateTime.time(), &dlg);
    te->setDisplayFormat("HH:mm:ss");
    lay->addWidget(te);
    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,
                                                 Qt::Horizontal, &dlg);
    lay->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    if (dlg.exec() == QDialog::Accepted) {
        m_dateTime.setTime(te->time());
        softWatch->setDateTime(m_dateTime);
    }
    if (!timerStopped) {
        timer->stop();
        timerStopped = true;
    }
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
    delete ui;
}
