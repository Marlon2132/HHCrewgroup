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
#include <QFont>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::readServerResponse);
    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &MainWindow::displayError);
    connect(tcpSocket, &QTcpSocket::connected, this, &MainWindow::onConnected);
}

MainWindow::~MainWindow()
{
}

QString MainWindow::extractSurname(const QString &message)
{
    // Регулярное выражение для поиска фамилии после "I'm" или "I am"
    QRegularExpression re("I('m|\\s+am)\\s+([^!,.]+)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = re.match(message);

    if (match.hasMatch()) {
        return match.captured(2).trimmed();
    }

    // Если шаблон не найден, берем последнее слово
    QStringList parts = message.split(' ', Qt::SkipEmptyParts);
    if (!parts.isEmpty()) {
        QString lastWord = parts.last();
        // Удаляем возможные знаки препинания
        if (lastWord.endsWith('!') || lastWord.endsWith(',') || lastWord.endsWith('.')) {
            lastWord.chop(1);
        }
        return lastWord;
    }

    return "Unknown";
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Поля ввода
    ipEdit = new QLineEdit("127.0.0.1", this);
    messageEdit = new QLineEdit(this);
    messageEdit->setPlaceholderText("Enter your full message (e.g. Hello, Garson, I'm Ivanov!)");

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

    QString message = messageEdit->text().trimmed();
    if (message.isEmpty()) {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Message is empty!");
        return;
    }

    // Извлекаем фамилию для возможного отображения изображения
    surnameForImage = extractSurname(message);

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
    }
    else {
        // Просто скрываем изображение для всех других ответов
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
    if (surnameForImage.isEmpty()) {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Cannot show image: surname is unknown.");
        return;
    }

    // Используем путь :/photos/ для изображений студентов
    QString studentImagePath = ":/photos/" + surnameForImage+ ".jpg";

    // Загружаем изображение студента из ресурсов
    QPixmap studentImage(studentImagePath);

    // Создаем изображение сада
    QPixmap gardenImage(400, 300);
    if (QPixmap("garden.jpg").isNull()) {
        gardenImage.fill(Qt::darkGreen);
        QPainter painter(&gardenImage);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 20));
        painter.drawText(gardenImage.rect(), Qt::AlignCenter, "Sleeping in the Garden");
        painter.setBrush(Qt::blue);
        painter.drawEllipse(100, 100, 50, 50); // луна
    } else {
        gardenImage = QPixmap("garden.jpg");
    }

    // Создаем композитное изображение
    QPixmap compositeImage(gardenImage.size());
    compositeImage.fill(Qt::transparent);

    QPainter painter(&compositeImage);
    painter.drawPixmap(0, 0, gardenImage);

    // Если изображение студента загружено, накладываем его
    if (!studentImage.isNull()) {
        // Увеличиваем размер изображения студента
        int studentWidth = gardenImage.width() * 0.8; // 90% ширины сада
        int studentHeight = gardenImage.height() * 0.8; // 90% высоты сада

        studentImage = studentImage.scaled(
            studentWidth,
            studentHeight,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );

        // Позиционируем по центру
        painter.drawPixmap(
            compositeImage.width()/2 - studentImage.width()/2,
            compositeImage.height()/2 - studentImage.height()/2,
            studentImage
            );
    } else {
        logText->append("[" + QDateTime::currentDateTime().toString() + "] Student image not found for: " + surnameForImage);
    }

    imageLabel->setPixmap(compositeImage.scaled(imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio));
    imageLabel->show();
}
