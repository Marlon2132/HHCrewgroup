#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QRandomGenerator>
#include <QPixmap>
#include <QDir>
#include <QHostAddress>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QScrollBar>
#include <QNetworkAddressEntry>
#include <QNetworkRequest>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    publicIp(""),
    danceTimer(new QTimer(this))
{
    setupUI();
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &MainWindow::newConnection);
    networkManager = new QNetworkAccessManager(this);

    // Настройка таймера для плавной анимации
    danceTimer->setInterval(40); // Обновление каждые 200 мс
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

    // Кнопка запуска сервера
    QPushButton *startButton = new QPushButton("Start Server", this);
    startButton->setMinimumHeight(30);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startServer);

    // Метка для отображения IP
    yourIpLabel = new QLabel(this);
    yourIpLabel->setAlignment(Qt::AlignCenter);
    yourIpLabel->setText("Your IP: Calculating...");

    // Список IP-адресов
    ipListWidget = new QListWidget(this);
    ipListWidget->setMaximumHeight(80);

    // Лог-поле
    logText = new QTextEdit(this);
    logText->setReadOnly(true);

    // Метка для изображения
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->hide();
    imageLabel->setMinimumSize(150, 150);
    imageLabel->setFrameShape(QFrame::Box);
    imageLabel->setStyleSheet("background: transparent; border: 1px solid #ccc;");

    // Добавляем элементы
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

    // Обновляем список IP
    updateIpList();
}

QString MainWindow::getMainIpAddress()
{
    // Получаем все сетевые интерфейсы
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    // Приоритет: Ethernet -> WiFi -> Другие
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

    // Если не нашли - возвращаем первый доступный
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

    // Обновляем метку с вашим IP
    yourIpLabel->setText("Local IP: " + mainIp + ":12345");

    // Добавляем localhost
    ipListWidget->addItem("127.0.0.1 (localhost)");

    // Получаем все IPv4 адреса
    QList<QHostAddress> ipAddresses = QNetworkInterface::allAddresses();

    for (const QHostAddress &address : ipAddresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
            address != QHostAddress::LocalHost) {

            QString ip = address.toString();
            ipListWidget->addItem(ip);
        }
    }

    // Добавляем публичный IP, если он доступен
    if (!publicIp.isEmpty()) {
        ipListWidget->addItem("Public IP: " + publicIp);
        ipListWidget->addItem("Note: For external networks, configure port forwarding on your router");
    }

    // Выделяем основной IP в списке
    for (int i = 0; i < ipListWidget->count(); ++i) {
        if (ipListWidget->item(i)->text().contains(mainIp)) {
            ipListWidget->item(i)->setText(ipListWidget->item(i)->text() + " [MAIN]");
            break;
        }
    }
}

void MainWindow::fetchPublicIp()
{
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl("http://api.ipify.org")));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handlePublicIpReply(reply);
    });
}

void MainWindow::handlePublicIpReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        publicIp = QString::fromUtf8(reply->readAll()).trimmed();
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Public IP: " + publicIp);
        logText->append("[" + QDateTime::currentDateTime().toString() + "] For external access, configure port forwarding on your router");
        updateIpList();
    } else {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Failed to get public IP: " + reply->errorString());
    }
    reply->deleteLater();
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

        // Обновляем список IP
        updateIpList();

        // Получаем публичный IP
        fetchPublicIp();

        // Прокручиваем лог вниз
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

    // Прокручиваем лог вниз
    QScrollBar *sb = logText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::readClientData()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QString message = QString::fromUtf8(clientSocket->readAll()).trimmed();
    logText->append("[" + QDateTime::currentDateTime().toString() + "] Received: " + message);

    // Проверка формата сообщения
    QRegularExpression pattern("^Hello, Garson, I'm (.+)!$");
    QRegularExpressionMatch match = pattern.match(message);

    if (match.hasMatch()) {
        QString surname = match.captured(1).trimmed();
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Correct message from: " + surname);

        // Отправка ответа
        QString response = "I'm not Garson, I'm Server! Go To Sleep To the Garden!";
        clientSocket->write(response.toUtf8());

        // Запуск анимации
        startDancingImage(surname);
    } else {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Incorrect message format");

        // Отправка ошибки
        QString error = "Error: Invalid message format! Expected: \"Hello, Garson, I'm [Surname]!\"";
        clientSocket->write(error.toUtf8());
    }

    // Прокручиваем лог вниз
    QScrollBar *sb = logText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::startDancingImage(const QString& surname)
{
    // Остановка предыдущей анимации
    danceTimer->stop();
    imageLabel->hide();

    // Загрузка изображения/текста
    QString imagePath = ":photos/" + surname + ".jpg";
    QPixmap studentImage(imagePath);

    if (!studentImage.isNull()) {
        imageLabel->setPixmap(studentImage.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imageLabel->setStyleSheet("background: transparent; border: none;");
    } else {
        imageLabel->setText("Student: " + surname);
        imageLabel->setStyleSheet("background: transparent; border: none; color: black; font-weight: bold;");
    }

    imageLabel->adjustSize();

    // Начальная позиция - центр окна
    QRect geo = this->geometry();
    int x = (geo.width() - imageLabel->width()) / 2;
    int y = (geo.height() - imageLabel->height()) / 2;
    imageLabel->move(x, y);

    imageLabel->show();

    // Запускаем анимацию
    danceTimer->start();
}

void MainWindow::moveImageRandomly()
{
    if (!imageLabel->isVisible()) return;

    // Текущая позиция метки
    QPoint currentPos = imageLabel->pos();

    // Генерация случайного смещения (в радиусе 5-10 пикселей)
    int offsetX = QRandomGenerator::global()->bounded(-5, 5);
    int offsetY = QRandomGenerator::global()->bounded(-5, 5);

    // Вычисляем новую позицию
    QPoint newPos = currentPos + QPoint(offsetX, offsetY);

    // Гарантируем, что метка останется в пределах окна
    QRect geo = this->geometry();
    newPos.setX(qBound(0, newPos.x(), geo.width() - imageLabel->width()));
    newPos.setY(qBound(0, newPos.y(), geo.height() - imageLabel->height()));

    // Плавное перемещение
    imageLabel->move(newPos);
}
