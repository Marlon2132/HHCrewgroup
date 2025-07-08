#include "mainwindow.h"
#include "request.h"
#include "ui_mainwindow.h"
#include "plotter.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_connected(false),
    ui(new Ui::MainWindow),
    m_socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    // Настройка виджетов
    ui->birthDateEdit->setDate(QDate::currentDate());
    ui->calcDateEdit->setDate(QDate::currentDate());

    // Соединения сокета
    connect(m_socket, &QTcpSocket::connected, this, &MainWindow::socketConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::socketReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnected);
    connect(m_socket, &QAbstractSocket::errorOccurred, this, &MainWindow::socketError);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_requestButton_clicked() {
    if (m_connected) {
        m_socket->disconnectFromHost();
    }

    QString ip = ui->ipLineEdit->text();
    quint16 port = static_cast<quint16>(ui->portSpinBox->value());
    m_socket->connectToHost(ip, port);
}

void MainWindow::socketConnected() {
    m_connected = true;
    ui->statusLabel->setText("Подключено к серверу");

    // Формирование запроса
    QString name = ui->nameEdit->text();
    QByteArray nameBytes = name.toUtf8().leftJustified(30, '\0', true);

    QDate birthDate = ui->birthDateEdit->date();
    QDate calcDate = ui->calcDateEdit->date();

    ReqDates rd;
    rd.birthDay = static_cast<quint8>(birthDate.day());
    rd.birthMonth = static_cast<quint8>(birthDate.month());
    rd.birthYear = static_cast<quint16>(birthDate.year());
    rd.calcDay = static_cast<quint8>(calcDate.day());
    rd.calcMonth = static_cast<quint8>(calcDate.month());
    rd.calcYear = static_cast<quint16>(calcDate.year());

    // Отправка запроса
    QByteArray block;
    block.append(nameBytes);
    block.append('\n');
    block.append(reinterpret_cast<const char*>(&rd), sizeof(rd));

    m_socket->write(block);
    ui->statusLabel->setText("Запрос отправлен...");
}

void MainWindow::socketReadyRead() {
    QByteArray response = m_socket->readAll();

    if (response == "ERR") {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные или запись не найдена");
        return;
    }

    if (response.size() != 14) {
        QMessageBox::critical(this, "Ошибка",
                              QString("Некорректный ответ сервера (%1 байт)").arg(response.size()));
        return;
    }

    // Разбор ответа
    quint16 days = *reinterpret_cast<const quint16*>(response.constData());
    const float *values = reinterpret_cast<const float*>(response.constData() + 2);

    ui->plotter->setBaseDays(days);
    ui->plotter->setValues(values[0], values[1], values[2]);
    ui->statusLabel->setText(QString("Данные получены: %1 дней").arg(days));
}

void MainWindow::socketError(QAbstractSocket::SocketError error) {
    Q_UNUSED(error);
    ui->statusLabel->setText("Ошибка: " + m_socket->errorString());
}

void MainWindow::socketDisconnected() {
    m_connected = false;
    ui->statusLabel->setText("Отключено от сервера");
}

