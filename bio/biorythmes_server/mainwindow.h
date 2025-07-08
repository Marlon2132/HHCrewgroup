#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "date.h"
#include "painter.h"
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateInfoF();

public slots:

    void updateInfo();

    void on_btnStart_clicked();
    void appendLog(const QString &msg);



private slots:
    void on_buildGraphic_clicked();

    void on_standartFormat_triggered();

    void on_textFormat_triggered();

    void on_reverseFormat_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_physShowSwitch_triggered();

    void on_psychoShowSwitcch_triggered();

    void on_intellShowSwitch_triggered();

    void on_setCurrDate_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_action_triggered();

    void on_action_5_triggered();

    void on_maxLineSwitch_triggered();

    void on_maxCrossSwitch_triggered();

    void on_minLineSwitch_triggered();

    void on_minCrossSwitch_triggered();

    void on_nullSwitch_triggered();

    void on_critMinSwitch_triggered();

    void on_critMaxSwitch_triggered();

    void on_critNullSwitch_triggered();

    void on_action_8_triggered();

    void on_cursorTrackingSwitch_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    Date currDate;
    Date birth;
    painter *paintel = new painter();
    int physBiorythmPercent;
    int psychoBiorythmPercent;
    int intellBiorythmPercent;

    Server *server;
    void displayLocalIp();

};
#endif // MAINWINDOW_H
