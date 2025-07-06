#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTimer>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>
#include <QTcpSocket>  // Добавлено

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    QString getMainIpAddress();
    void updateIpList();
    void startServer();
    void newConnection();
    void readClientData();
    void startDancingImage(const QString& surname);
    void moveImageRandomly();

    QTcpServer *server;
    QTimer *danceTimer;
    QLabel *yourIpLabel;
    QListWidget *ipListWidget;
    QTextEdit *logText;
    QLabel *imageLabel;
};

#endif // MAINWINDOW_H
