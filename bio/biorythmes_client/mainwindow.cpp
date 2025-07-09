#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QMessageBox>
#include <QtEndian>
#include "date.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    ui->birthDateEdit->setDate(QDate::currentDate());
    ui->calcDateEdit ->setDate(QDate::currentDate());

    connect(m_socket, &QTcpSocket::connected,    this, &MainWindow::socketConnected);
    connect(m_socket, &QTcpSocket::readyRead,    this, &MainWindow::socketReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnected);
    connect(m_socket, &QAbstractSocket::errorOccurred,
            this, &MainWindow::socketError);

    connect(ui->requestButton, &QPushButton::clicked,
            this, &MainWindow::on_requestButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_requestButton_clicked() {
    if (m_connected) {
        m_socket->disconnectFromHost();
        return;
    }

    QString ip   = ui->ipLineEdit->text();
    quint16 port = ui->portSpinBox->value();

    ui->statusTEdit->append(
        QString("Connecting to %1:%2…").arg(ip).arg(port));
    m_socket->connectToHost(ip, port);
}

void MainWindow::socketConnected() {
    m_connected = true;
    ui->statusTEdit->append("Connected to server");

    // Собираем данные запроса
    QString name = ui->nameEdit->text();
    QDate   qb   = ui->birthDateEdit->date();
    QDate   qc   = ui->calcDateEdit->date();

    ReqDates rd;
    // Копируем имя в фиксированный буфер
    memset(rd.fullname, '\0', sizeof rd.fullname);
    QByteArray nameBytes = name.toUtf8();
    memcpy(rd.fullname,
           nameBytes.constData(),
           qMin<int>(nameBytes.size(), sizeof rd.fullname));
    rd.birthDay   = quint8(qb.day());
    rd.birthMonth = quint8(qb.month());
    rd.birthYear  = quint16(qb.year());
    rd.calcDay    = quint8(qc.day());
    rd.calcMonth  = quint8(qc.month());
    rd.calcYear   = quint16(qc.year());

    // Переводим в сетевой порядок байт
   // rd.birthYear = qToBigEndian<quint16>(rd.birthYear);
   // rd.calcYear  = qToBigEndian<quint16>(rd.calcYear);

    // Отправляем только бинарную структуру
    QByteArray packet(reinterpret_cast<const char*>(&rd), sizeof rd);
    m_socket->write(packet);

    ui->statusTEdit->append("Request sent");
}

void MainWindow::socketReadyRead() {
    auto response = m_socket->readAll();

    if (response == "ERR") {
        ui->statusTEdit->append("Server error: invalid data");
        return;
    }
    if (response.size() != 14) {
        ui->statusTEdit->append(QString::fromUtf8(response));
        return;
    }

    RecievedData Answer;
    Answer.DaysLived = *reinterpret_cast<quint16*>(response.data());
    Answer.values[0] = *reinterpret_cast<float*>(response.data()+2);
    Answer.values[1]   = *reinterpret_cast<float*>(response.data()+6);
    Answer.values[2]   = *reinterpret_cast<float*>(response.data()+10);

    ui->statusTEdit->append(
        QString("Answer received: %1 days\nPhysical %2%\nPsycho %3%\nIntellectual %4%").arg(Answer.DaysLived).arg(Answer.values[0]*100).arg(Answer.values[1]*100).arg(Answer.values[2]*100));

    // Конвертим QDate → Date
    Date birth, calc;
    birth.inputDate(ui->birthDateEdit->date().toString("dd.MM.yyyy"));
    calc .inputDate(ui->calcDateEdit ->date().toString("dd.MM.yyyy"));

    // Передаём в painter
    ui->painter->getDates(calc, birth);
    ui->painter->setPercents(int(Answer.values[0]*100), int(Answer.values[1]*100), int(Answer.values[2]*100));
    ui->painter->firstLaunch = true;
    ui->painter->update();
}

void MainWindow::socketError(QAbstractSocket::SocketError) {
    ui->statusTEdit->append(
        "Socket error: " + m_socket->errorString());
}

void MainWindow::socketDisconnected() {
    m_connected = false;
    ui->statusTEdit->append("Disconnected");
}
