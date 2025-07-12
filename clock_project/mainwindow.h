// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include "softwatchwidget.h"
#include <QSettings>
#include <QLabel>

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
    void on_changeDateTimeAction_triggered();
    void on_helpAction_triggered();
    void on_BGchange1_triggered();
    void on_BGchange2_triggered();
    void on_BGchange3_triggered();
    void on_BGchange4_triggered();
    void on_BGchange5_triggered();
    void updateTime();

private:
    void loadSettings();
    void saveSettings();
    Ui::MainWindow *ui;
    SoftWatchWidget *softWatch;
    QTimer *timer;
    bool timerStopped = false;
    QDateTime m_dateTime;
    QLabel *dateLabel;
};

#endif // MAINWINDOW_H
