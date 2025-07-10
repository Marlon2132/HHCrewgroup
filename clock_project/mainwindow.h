#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "softwatchwidget.h"
#include "datetimeinputdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_setTimeAction_triggered();
    void on_helpAction_triggered();

    void on_BGchange1_triggered();
    void on_BGchange2_triggered();
    void on_BGchange3_triggered();
    void on_BGchange4_triggered();
    void on_BGchange5_triggered();

    void updateTime();
    void showInputDialog();

private:
    Ui::MainWindow *ui;
    SoftWatchWidget *softWatch;
    QTimer *timer;
};

#endif // MAINWINDOW_H
