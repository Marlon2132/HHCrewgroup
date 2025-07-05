#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>

class QLineEdit;
class QPushButton;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void connectToServer();
    void sendMessage();
    void readServerResponse();
    void displayError(QAbstractSocket::SocketError socketError);
    void onConnected();

private:
    void setupUI();
    void showGardenImage();

    QTcpSocket *tcpSocket;
    QLineEdit *ipEdit;
    QLineEdit *messageEdit;
    QPushButton *connectButton;
    QPushButton *sendButton;
    QTextEdit *logText;
    QLabel *imageLabel;
};

#endif // MAINWINDOW_H
