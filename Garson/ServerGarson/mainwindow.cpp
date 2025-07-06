#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QRandomGenerator>
#include <QPixmap>
#include <QHostAddress>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QScrollBar>
#include <QTimer>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QRegularExpression>
#include <QTextEdit>
#include <QListWidget>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    danceTimer(new QTimer(this))
{
    setupUI();
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &MainWindow::newConnection);

    danceTimer->setInterval(100);
    connect(danceTimer, &QTimer::timeout, this, &MainWindow::moveImageRandomly);
}

MainWindow::~MainWindow()
{
    server->close();
    danceTimer->stop();
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(5);

    QPushButton *startButton = new QPushButton("Start Server", this);
    startButton->setMinimumHeight(30);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startServer);

    yourIpLabel = new QLabel(this);
    yourIpLabel->setAlignment(Qt::AlignCenter);
    yourIpLabel->setText("Your IP: Calculating...");

    ipListWidget = new QListWidget(this);
    ipListWidget->setMaximumHeight(80);

    logText = new QTextEdit(this);
    logText->setReadOnly(true);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->hide();
    imageLabel->setMinimumSize(150, 150);
    imageLabel->setFrameShape(QFrame::Box);
    imageLabel->setStyleSheet("border: 1px solid #ccc;");

    layout->addWidget(startButton);
    layout->addWidget(yourIpLabel);
    layout->addWidget(new QLabel("All available IP addresses:"));
    layout->addWidget(ipListWidget);
    layout->addWidget(new QLabel("Log:"));
    layout->addWidget(logText);
    layout->addWidget(new QLabel("Active student:"));
    layout->addWidget(imageLabel);

    setCentralWidget(centralWidget);
    setWindowTitle("Garson Server");
    resize(600, 500);

    updateIpList();
}

QString MainWindow::getMainIpAddress()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    for (const QNetworkInterface &interface : interfaces) {
        if (!(interface.flags() & QNetworkInterface::IsUp) ||
            !(interface.flags() & QNetworkInterface::IsRunning)) {
            continue;
        }

        if (interface.flags() & QNetworkInterface::IsLoopBack ||
            interface.humanReadableName().contains("virtual", Qt::CaseInsensitive)) {
            continue;
        }

        QList<QNetworkAddressEntry> entries = interface.addressEntries();
        for (const QNetworkAddressEntry &entry : entries) {
            QHostAddress ip = entry.ip();
            if (ip.protocol() == QAbstractSocket::IPv4Protocol &&
                !ip.isLoopback() &&
                !ip.isLinkLocal()) {
                return ip.toString();
            }
        }
    }

    QList<QHostAddress> ipAddresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : ipAddresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
            !address.isLoopback() &&
            !address.isLinkLocal()) {
            return address.toString();
        }
    }

    return "127.0.0.1";
}

void MainWindow::updateIpList()
{
    ipListWidget->clear();
    QString mainIp = getMainIpAddress();

    yourIpLabel->setText("Local IP: " + mainIp + ":12345");
    ipListWidget->addItem("127.0.0.1 (localhost)");

    QList<QHostAddress> ipAddresses = QNetworkInterface::allAddresses();

    for (const QHostAddress &address : ipAddresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
            address != QHostAddress::LocalHost) {

            QString ip = address.toString();
            ipListWidget->addItem(ip);
        }
    }

    for (int i = 0; i < ipListWidget->count(); ++i) {
        if (ipListWidget->item(i)->text().contains(mainIp)) {
            ipListWidget->item(i)->setText(ipListWidget->item(i)->text() + " [MAIN]");
            break;
        }
    }
}

void MainWindow::startServer()
{
    if (server->isListening()) {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Server already running!");
        return;
    }

    if (server->listen(QHostAddress::Any, 12345)) {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Server started on port 12345");
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Waiting for connections...");
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Local IP: " + getMainIpAddress());

        updateIpList();

        QScrollBar *sb = logText->verticalScrollBar();
        sb->setValue(sb->maximum());
    } else {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Error: " + server->errorString());
        QMessageBox::critical(this, "Server Error", "Failed to start server:\n" + server->errorString());
    }
}

void MainWindow::newConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MainWindow::readClientData);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

    QString clientInfo = clientSocket->peerAddress().toString() + ":" + QString::number(clientSocket->peerPort());
    logText->append("[" + QDateTime::currentDateTime().toString() + "] New client: " + clientInfo);

    QScrollBar *sb = logText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::readClientData()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QString message = QString::fromUtf8(clientSocket->readAll()).trimmed();
    logText->append("[" + QDateTime::currentDateTime().toString() + "] Received: " + message);

    QRegularExpression pattern("^Hello, Garson, I'm (.+)!$");
    QRegularExpressionMatch match = pattern.match(message);

    if (match.hasMatch()) {
        QString surname = match.captured(1).trimmed();
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Correct message from: " + surname);

        QString response = "I'm not Garson, I'm Server! Go To Sleep To the Garden!";
        clientSocket->write(response.toUtf8());

        startDancingImage(surname);
    } else {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Incorrect message format");

        QString error = "Error: Invalid message format! Expected: \"Hello, Garson, I'm [Surname]!\"";
        clientSocket->write(error.toUtf8());
    }

    QScrollBar *sb = logText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::startDancingImage(const QString& surname)
{
    danceTimer->stop();
    imageLabel->hide();

    QString imagePath = ":/photos/" + surname + ".jpg";
    QPixmap studentImage(imagePath);

    if (!studentImage.isNull()) {
        imageLabel->setPixmap(studentImage.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imageLabel->setStyleSheet("background: transparent; border: none;");
    } else {
        imageLabel->setText("Student: " + surname);
        imageLabel->setStyleSheet("background: transparent; border: none; color: black; font-weight: bold;");
    }

    imageLabel->adjustSize();

    QRect geo = this->geometry();
    int x = (geo.width() - imageLabel->width()) / 2;
    int y = (geo.height() - imageLabel->height()) / 2;
    imageLabel->move(x, y);

    imageLabel->show();
    danceTimer->start();
}

void MainWindow::moveImageRandomly()
{
    if (!imageLabel->isVisible()) return;

    QPoint currentPos = imageLabel->pos();
    int offsetX = QRandomGenerator::global()->bounded(-7, 7);
    int offsetY = QRandomGenerator::global()->bounded(-7, 7);
    QPoint newPos = currentPos + QPoint(offsetX, offsetY);

    QRect geo = this->geometry();
    newPos.setX(qBound(0, newPos.x(), geo.width() - imageLabel->width()));
    newPos.setY(qBound(0, newPos.y(), geo.height() - imageLabel->height()));

    imageLabel->move(newPos);
}
