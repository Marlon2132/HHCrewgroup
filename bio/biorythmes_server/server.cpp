#include "server.h"
#include "mainwindow.h"

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
    if (!socket) return;

    // Буферизуем всё от клиента
    m_buf[socket].append(socket->readAll());
    QByteArray &buf = m_buf[socket];

    // Ждём пока накопится как минимум sizeof(Request) байт
    if (buf.size() < int(sizeof(Request)))
        return;

    // Копируем первые 38 байт в Request
    Request req;
    memcpy(&req, buf.constData(), sizeof(req));
    // Удаляем обработанный кусок из буфера
    buf.remove(0, sizeof(req));

    // Преобразуем ФИО в QString без \0 и пробелов
    QByteArray nameBa(req.fullName, 30);
    int zeroPos = nameBa.indexOf('\0');
    if (zeroPos >= 0)
        nameBa.truncate(zeroPos);
    QString name = QString::fromUtf8(nameBa);

    emit logMessage(
        QString("Получен запрос от %1: ДР %2.%3.%4, расчёт %5.%6.%7")
            .arg(name)
            .arg(req.birthDay)
            .arg(req.birthMonth)
            .arg(req.birthYear)
            .arg(req.calcDay)
            .arg(req.calcMonth)
            .arg(req.calcYear)
        );

    // Поиск в базе
    PersonRecord rec;
    findInDatabase(req, rec);

    // Отправляем daysLived + values[3]
    sendPersonRecord(socket, rec);
}

void Server::receiveCyclesAndDaysLvd(int physPct,int psychoPct, int intelPct, int daysLvd)
{
    m_physPct = physPct;
    m_psychoPct = psychoPct;
    m_intelPct = intelPct;
    m_daysLvd = daysLvd;
}


void Server::findInDatabase(const Request &req, PersonRecord &outRec) {
    auto socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QFile db("database.db");
    if (!db.open(QIODevice::ReadWrite)) {
        emit logMessage("Не удалось открыть database.db");
        socket->write("Ошибка! Серверу не удалось открыть базу данных!");
        return;
    }

    PersonRecord rec;
    while (db.read(reinterpret_cast<char*>(&rec), sizeof(rec))
           == sizeof(rec))
    {
        // Побайтово сравниваем ФИО и даты
        if (memcmp(rec.fullName, req.fullName, 30)  == 0
            && rec.birthDay   == req.birthDay
            && rec.birthMonth == req.birthMonth
            && rec.birthYear  == req.birthYear
            && rec.calcDay    == req.calcDay
            && rec.calcMonth  == req.calcMonth
            && rec.calcYear   == req.calcYear)
        {
            outRec = rec;
            return;
        }
    }

    // запись не найдена

    emit logMessage("Запись не найдена. Осуществляю расчёт...");

    memcpy(outRec.fullName, req.fullName, sizeof(req.fullName));
    outRec.birthDay = req.birthDay;
    outRec.birthMonth = req.birthMonth;
    outRec.birthYear = req.birthYear;
    outRec.calcDay = req.calcDay;
    outRec.calcMonth = req.calcMonth;
    outRec.calcYear = req.calcYear;

    QString bDateStr = QString("%1.%2.%3")
                        .arg(req.birthDay,   2, 10, QChar('0'))
                        .arg(req.birthMonth, 2, 10, QChar('0'))
                        .arg(req.birthYear);
    Date bDate;
    bDate.inputDate(bDateStr);
    QString cDateStr = QString("%1.%2.%3")
                        .arg(req.calcDay,   2, 10, QChar('0'))
                        .arg(req.calcMonth, 2, 10, QChar('0'))
                        .arg(req.calcYear);
    Date cDate;
    bDate.inputDate(cDateStr);

    emit datesReceived(bDateStr, cDateStr);

    outRec.values[0] = (float)m_physPct/100.00;
    outRec.values[1] = (float)m_psychoPct/100.00;
    outRec.values[2] = (float)m_intelPct/100.00;

    outRec.daysLived = (quint16)m_daysLvd;

    // Запись в db

    QByteArray new_note;

    new_note.reserve(sizeof(outRec));
    new_note.append(reinterpret_cast<const char*>(&outRec),sizeof(outRec));

    db.write(new_note);
    db.flush();
    db.close();

    return; // не найдена запись
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
