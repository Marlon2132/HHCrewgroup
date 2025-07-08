#include "server.h"
#include <QDataStream>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{}

bool Server::start(quint16 port) {
    if (!listen(QHostAddress::Any, port)) {
        emit logMessage(QString("Не удалось запустить сервер: %1").arg(errorString()));
        return false;
    }
    emit logMessage(QString("Сервер запущен на порту %1").arg(port));
    return true;
}

void Server::incomingConnection(qintptr sd) {
    auto socket = new QTcpSocket(this);
    socket->setSocketDescriptor(sd);
    clients.append(socket);
    emit logMessage(QString("Клиент подключился: %1:%2")
                        .arg(socket->peerAddress().toString())
                        .arg(socket->peerPort()));

    connect(socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::onDisconnected);
}

void Server::onReadyRead() {
    auto socket = qobject_cast<QTcpSocket*>(sender());
    QByteArray block = socket->readAll();
    // Простейшая проверка: если первые байты – текст
    if (block.startsWith("TXT:")) {
        QString msg = QString::fromUtf8(block.mid(4));
        emit logMessage(QString("Получено сообщение от %1: %2")
                            .arg(socket->peerAddress().toString())
                            .arg(msg));
    } else {
        emit logMessage(QString("Получён бинарный пакет (%1 байт) от %2")
                            .arg(block.size())
                            .arg(socket->peerAddress().toString()));
        // здесь сохранить в файл, или обработать
    }
}

void Server::onDisconnected() {
    auto socket = qobject_cast<QTcpSocket*>(sender());
    emit logMessage(QString("Клиент отключился: %1:%2")
                        .arg(socket->peerAddress().toString())
                        .arg(socket->peerPort()));
    clients.removeAll(socket);
    socket->deleteLater();
}

void Server::sendText(QTcpSocket *client, const QString &text) {
    QByteArray block = "TXT:" + text.toUtf8();
    client->write(block);
    emit logMessage(QString("Отправлено сообщение клиенту %1: %2")
                        .arg(client->peerAddress().toString())
                        .arg(text));
}

void Server::sendBinary(QTcpSocket *client, const QByteArray &data) {
    client->write(data);
    emit logMessage(QString("Отправлен бинарный пакет (%1 байт) клиенту %2")
                        .arg(data.size())
                        .arg(client->peerAddress().toString()));
}
