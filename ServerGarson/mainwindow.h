// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLabel>
#include <QRegularExpression>
#include <QPushButton>
#include <QListWidget>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer> // Добавлен таймер

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
    void handlePublicIpReply(QNetworkReply *reply);
    void moveImageRandomly(); // Добавлен слот для перемещения

private:
    void setupUI();
    void updateIpList();
    QString getMainIpAddress();
    void startDancingImage(const QString& surname);
    void fetchPublicIp();
    void stopDancing(); // Добавлена функция остановки

    QTcpServer *server;
    QTextEdit *logText;
    QLabel *imageLabel;
    QListWidget *ipListWidget;
    QLabel *yourIpLabel;
    QNetworkAccessManager *networkManager;
    QString publicIp;
    QTimer *danceTimer; // Таймер для анимации
    QString currentSurname; // Текущая фамилия
};

#endif // MAINWINDOW_H
