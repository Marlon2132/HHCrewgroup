#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

class Plotter; // Добавьте предварительное объявление

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
    void on_requestButton_clicked();
    void socketConnected();
    void socketReadyRead();
    void socketError(QAbstractSocket::SocketError error);
    void socketDisconnected();

private:
    bool m_connected;
    Ui::MainWindow *ui;
    QTcpSocket *m_socket;
};
#endif // MAINWINDOW_H
