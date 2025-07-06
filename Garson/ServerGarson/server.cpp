#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>
#include <QRandomGenerator>

class ServerWindow : public QMainWindow {
    Q_OBJECT
public:
    ServerWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
        setupServer();
    }

private slots:
    void startServer() {
        if (server->isListening()) {
            logText->append("Server already running!");
            return;
        }

        if (server->listen(QHostAddress::Any, 12345)) {
            logText->append("Server started on port 12345");
            logText->append("Waiting for connections...");
        } else {
            logText->append("Error: " + server->errorString());
        }
    }

    void newConnection() {
        QTcpSocket *clientSocket = server->nextPendingConnection();
        connect(clientSocket, &QTcpSocket::readyRead, this, &ServerWindow::readClientData);
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

        logText->append("New client connected: " + clientSocket->peerAddress().toString());
    }

    void readClientData() {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
        if (!clientSocket) return;

        QString message = QString::fromUtf8(clientSocket->readAll()).trimmed();
        logText->append("Received: " + message);

        // Проверка формата сообщения
        QRegExp pattern("^Hello, Garson, I'm (.+)!$");
        if (pattern.exactMatch(message)) {
            QString surname = pattern.cap(1).trimmed();
            logText->append("Correct message from: " + surname);

            // Отправка ответа
            QString response = "I'm not Garson, I'm Server! Go To Sleep To the Garden!";
            clientSocket->write(response.toUtf8());

            // Запуск анимации
            startDancingImage(surname);
        } else {
            logText->append("Incorrect message format");

            // Отправка ошибки
            QString error = "Error: Invalid message format! Use: \"Hello, Garson, I'm [Surname]!\"";
            clientSocket->write(error.toUtf8());
        }
    }

    void startDancingImage(const QString& surname) {
        // Остановка предыдущей анимации
        if (animation) {
            animation->stop();
            delete animation;
        }

        // Установка текста вместо фото (можно заменить на загрузку реального изображения)
        imageLabel->setText("Student: " + surname);
        imageLabel->setStyleSheet("background-color: lightblue; font-weight: bold;");
        imageLabel->adjustSize();
        imageLabel->show();

        // Создание анимации
        animation = new QPropertyAnimation(imageLabel, "pos");
        animation->setDuration(2000);
        animation->setLoopCount(-1); // Бесконечная анимация

        // Генерация случайных позиций
        QRect geo = this->geometry();
        for (int i = 0; i < 5; ++i) {
            int x = QRandomGenerator::global()->bounded(geo.width() - imageLabel->width());
            int y = QRandomGenerator::global()->bounded(geo.height() - imageLabel->height());
            animation->setKeyValueAt(i * 0.2, QPoint(x, y));
        }

        animation->start();
    }

private:
    void setupUI() {
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Кнопка запуска сервера
        QPushButton *startButton = new QPushButton("Start Server", this);
        connect(startButton, &QPushButton::clicked, this, &ServerWindow::startServer);

        // Лог-поле
        logText = new QTextEdit(this);
        logText->setReadOnly(true);

        // Метка для изображения (изначально скрыта)
        imageLabel = new QLabel(this);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->hide();
        imageLabel->setMinimumSize(100, 100);

        layout->addWidget(startButton);
        layout->addWidget(logText);
        layout->addWidget(imageLabel);

        setCentralWidget(centralWidget);
        setWindowTitle("Garson Server");
        resize(600, 400);
    }

    void setupServer() {
        server = new QTcpServer(this);
        connect(server, &QTcpServer::newConnection, this, &ServerWindow::newConnection);
        animation = nullptr;
    }

    QTcpServer *server;
    QTextEdit *logText;
    QLabel *imageLabel;
    QPropertyAnimation *animation;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ServerWindow serverWindow;
    serverWindow.show();
    return app.exec();
}

#include "main.moc"
