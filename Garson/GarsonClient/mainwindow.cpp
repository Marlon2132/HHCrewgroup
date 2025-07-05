#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include <QDateTime>
#include <QPixmap>
#include <QDir>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::readServerResponse);
    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &MainWindow::displayError);
    connect(tcpSocket, &QTcpSocket::connected, this, &MainWindow::onConnected);
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Поля ввода
    ipEdit = new QLineEdit("217.21.43.190", this);
    messageEdit = new QLineEdit(this);
    messageEdit->setPlaceholderText("Enter your surname for the message");

    // Кнопки
    connectButton = new QPushButton("Connect to Server", this);
    sendButton = new QPushButton("Send Message", this);
    sendButton->setEnabled(false);

    // Лог
    logText = new QTextEdit(this);
    logText->setReadOnly(true);

    // Изображение
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->hide();
    imageLabel->setMinimumSize(300, 200);
    imageLabel->setStyleSheet("border: 1px solid gray;");

    // Расположение элементов
    QHBoxLayout *ipLayout = new QHBoxLayout();
    ipLayout->addWidget(new QLabel("Server IP:", this));
    ipLayout->addWidget(ipEdit);
    ipLayout->addWidget(connectButton);

    QHBoxLayout *messageLayout = new QHBoxLayout();
    messageLayout->addWidget(new QLabel("Message:", this));
    messageLayout->addWidget(messageEdit);
    messageLayout->addWidget(sendButton);

    mainLayout->addLayout(ipLayout);
    mainLayout->addLayout(messageLayout);
    mainLayout->addWidget(logText);
    mainLayout->addWidget(imageLabel);

    setCentralWidget(centralWidget);
    setWindowTitle("Garson Client");
    resize(600, 500);

    // Соединение кнопок
    connect(connectButton, &QPushButton::clicked, this, &MainWindow::connectToServer);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);
}

void MainWindow::connectToServer()
{
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Already connected.");
        return;
    }

    QString ip = ipEdit->text().trimmed();
    quint16 port = 12345;

    tcpSocket->connectToHost(ip, port);
    logText->append("[" + QDateTime::currentDateTime().toString() + "] Connecting to " + ip + "...");
}

void MainWindow::onConnected()
{
    logText->append("[" + QDateTime::currentDateTime().toString() + "] Connected to server.");
    sendButton->setEnabled(true);
}

void MainWindow::sendMessage()
{
    if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Not connected to server.");
        return;
    }

    QString surname = messageEdit->text().trimmed();
    if (surname.isEmpty()) {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Surname is empty!");
        return;
    }

    // Формируем сообщение
    QString message = "Hello, Garson, I'm " + surname + "!";
    tcpSocket->write(message.toUtf8());
    logText->append("[" + QDateTime::currentDateTime().toString() + "] Sent: " + message);
}

void MainWindow::readServerResponse()
{
    QString response = QString::fromUtf8(tcpSocket->readAll()).trimmed();
    logText->append("[" + QDateTime::currentDateTime().toString() + "] Server response: " + response);

    // Если ответ сервера содержит команду для сна
    if (response.contains("Go To Sleep To the Garden!")) {
        showGardenImage();
    } else {
        imageLabel->hide();
    }
}
void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    logText->append("[" + QDateTime::currentDateTime().toString() + "] Error: " + tcpSocket->errorString());
    sendButton->setEnabled(false);
}

void MainWindow::showGardenImage()
{
    // Пробуем загрузить изображение
    QString imagePath = QDir::currentPath() + "/garden.jpg";
    QPixmap gardenImage(imagePath);

    if (gardenImage.isNull()) {
        // Создаем изображение программно, если файла нет
        gardenImage = QPixmap(400, 300);
        gardenImage.fill(Qt::darkGreen);

        QPainter painter(&gardenImage);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 20));
        painter.drawText(gardenImage.rect(), Qt::AlignCenter, "Sleeping in the Garden");

        painter.setBrush(Qt::blue);
        painter.drawEllipse(100, 100, 50, 50); // луна
    }

    imageLabel->setPixmap(gardenImage.scaled(imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio));
    imageLabel->show();
}
