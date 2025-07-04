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
#include <QNetworkAccessManager>
#include <QNetworkReply>

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
 void updateAnimation();
private:
    void setupUI();
    void updateIpList();
    QString getMainIpAddress();
    void startDancingImage(const QString& surname);
    void fetchPublicIp();
    QTimer *animationTimer; // Таймер для анимации
    QPointF currentPosition; // Текущая позиция
    QPointF velocity;
    QTcpServer *server;
    QTextEdit *logText;
    QLabel *imageLabel;
    QPropertyAnimation *animation;
    QListWidget *ipListWidget;
    QLabel *yourIpLabel;
    QNetworkAccessManager *networkManager;
    QString publicIp;
};

#endif // MAINWINDOW_H
