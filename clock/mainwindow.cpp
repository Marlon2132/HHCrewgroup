#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_help_action_triggered(){
    QMessageBox *about = new QMessageBox;
    about->setIcon(QMessageBox::Information);
    about->setWindowTitle("Помощь");
    about->setText("Часы\n\nТут будет добавляться описание программы.");
    about->exec();
}
