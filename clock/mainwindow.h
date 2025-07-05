#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_help_action_triggered();
    void onManualInputTriggered();
    void onWordInputTriggered();
    void onTimerInputTriggered();
    void updateClockDisplay();

private:
    Ui::MainWindow *ui;
    QTimer *clockTimer;
};

#endif // MAINWINDOW_H
