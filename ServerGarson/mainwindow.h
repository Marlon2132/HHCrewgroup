#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLabel>
#include <QPropertyAnimation>
#include <QRegularExpression>
#include <QPushButton>
#include <QListWidget>
#include <QNetworkInterface>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startServer();
    void newConnection();
    void readClientData();

private:
    void setupUI();
    void updateIpList();
    QString getMainIpAddress();
    void startDancingImage(const QString& surname);

    QTcpServer *server;
    QTextEdit *logText;
    QLabel *imageLabel;
    QPropertyAnimation *animation;
    QListWidget *ipListWidget;
    QLabel *yourIpLabel;
};

#endif // MAINWINDOW_H
