#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

class QLineEdit;
class QTextEdit;
class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectToServer();
    void sendMessage();
    void readServerResponse();
    void displayError(QAbstractSocket::SocketError socketError);
    void onConnected();

private:
    void setupUI();
    void showGardenImage();
    QString extractSurname(const QString &message);

    QTcpSocket *tcpSocket;
    QLineEdit *ipEdit;
    QLineEdit *messageEdit;
    QTextEdit *logText;
    QLabel *imageLabel;
    QPushButton *connectButton;
    QPushButton *sendButton;
    QString surnameForImage;
};

#endif // MAINWINDOW_H
