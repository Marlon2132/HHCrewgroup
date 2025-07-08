#include "server.h"

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
    if (!socket)
        return;
    //QByteArray block = socket->readAll();

    m_buf[socket].append(socket->readAll());
    QByteArray &buf = m_buf[socket];

    // 1) ждём разделитель имени (‘\n’)
    int pos = buf.indexOf('\n');
    if (pos < 0) {
        // строки ещё нет целиком
        return;
    }

    // 2) извлекаем имя
    QByteArray nameBytes = buf.left(30);

    int zeroPos = nameBytes.indexOf('\0');
    if (zeroPos != -1)
        nameBytes.chop(nameBytes.size() - zeroPos);

    // 3) Преобразуем в QString
    QString name = QString::fromUtf8(nameBytes);

    // удаляем имя+делимитер из буфера
    buf.remove(0, pos + 1);

    // 4) ждём полного блока дат
    if (buf.size() < int(sizeof(ReqDates))) {
        // ждём ещё байт
        return;
    }

    // 4) копируем даты
    ReqDates rd;
    memcpy(&rd, buf.constData(), sizeof(rd));
    buf.remove(0, sizeof(rd));  // убираем обработанную часть
    emit logMessage(QString("Получен запрос от %1.")
                             .arg(socket->peerAddress().toString()));
    emit logMessage(QString("Запрос: '%1', ДР %2.%3.%4, расчёт %5.%6.%7")
                        .arg(name)
                        .arg(rd.birthDay)
                        .arg(rd.birthMonth)
                        .arg(rd.birthYear)
                        .arg(rd.calcDay)
                        .arg(rd.calcMonth)
                        .arg(rd.calcYear));
    // 5) поиск в базе
    PersonRecord rec;
    if (!findInDatabase(nameBytes, rd, rec)) {
        emit logMessage("Запись не найдена в database.db");
        socket->write("ERR");
        return;
    }

    // 6) отправка ответа
    sendPersonRecord(socket, rec);

    // Простейшая проверка: если первые байты – текст
    // if (block.startsWith("TXT:")) {
    //     QString msg = QString::fromUtf8(block.mid(4));
    //     emit logMessage(QString("Получено сообщение от %1: %2")
    //                         .arg(socket->peerAddress().toString())
    //                         .arg(msg));
    // }
    // else if (block.size() != sizeof(Request)) {
    //     emit logMessage(QString("Ошибка! Получен бинарный файл (%1 байт) от %2. Размер должен быть " + QString::number(sizeof(char[30])))
    //                         .arg(block.size())
    //                         .arg(socket->peerAddress().toString()));
    // }
    // else {
    //     emit logMessage(QString("Получен бинарный файл (%1 байт) от %2")
    //                         .arg(block.size())
    //                         .arg(socket->peerAddress().toString()));
    //     // здесь сохранить в файл, или обработать
    // }
}

bool Server::findInDatabase(const QByteArray &nameBytes,
                            const ReqDates &rd,
                            PersonRecord &outRec)
{
    QFile db("database.db");
    if (!db.open(QIODevice::ReadOnly)) {
        emit logMessage("Не удалось открыть database.db");
        return false;
    }

    PersonRecord rec;
    while (db.read(reinterpret_cast<char*>(&rec), sizeof(rec))
           == sizeof(rec))
    {
        if (memcmp(rec.fullName, nameBytes.constData(), 30) == 0
            && rec.birthDay   == rd.birthDay
            && rec.birthMonth == rd.birthMonth
            && rec.birthYear  == rd.birthYear
            && rec.calcDay    == rd.calcDay
            && rec.calcMonth  == rd.calcMonth
            && rec.calcYear   == rd.calcYear)
        {
            outRec = rec;
            return true;
        }
    }
    return false;
}

void Server::sendPersonRecord(QTcpSocket *socket,
                              const PersonRecord &rec)
{
    // Формируем бинарный ответ: daysLived (2 байта) + values[3] (3×4 байта)
    QByteArray resp;
    resp.reserve(sizeof(rec.daysLived) + sizeof(rec.values));

    resp.append(reinterpret_cast<const char*>(&rec.daysLived),
                sizeof(rec.daysLived));
    resp.append(reinterpret_cast<const char*>(rec.values),
                sizeof(rec.values));

    socket->write(resp);
    emit logMessage(QString("Отправлен ответ: Прожито дней: %1, Значения циклов (физ., псих., инт.): %2, %3, %4")
                        .arg(rec.daysLived)
                        .arg(rec.values[0])
                        .arg(rec.values[1])
                        .arg(rec.values[2]));
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
