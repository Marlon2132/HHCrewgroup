#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "painter.h"
#include "request.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_requestButton_clicked();
    void socketConnected();
    void socketReadyRead();
    void socketError(QAbstractSocket::SocketError err);
    void socketDisconnected();

private:
    Ui::MainWindow *ui;
    QTcpSocket     *m_socket   = nullptr;
    bool            m_connected = false;
};

#endif // MAINWINDOW_H
