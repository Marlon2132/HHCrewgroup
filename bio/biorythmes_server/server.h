#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QFile>
#include <QDataStream>
#include "records.h"

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    bool start(quint16 port);

signals:
    void logMessage(const QString &msg);

public slots:
    void sendText(QTcpSocket *client, const QString &text);
    void sendBinary(QTcpSocket *client, const QByteArray &data);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QList<QTcpSocket*> clients;
    QHash<QTcpSocket*, QByteArray> m_buf;

    // Ищет по ФИО+датам запись в бинарной базе database.db
    // nameBytes — ровно 30 байт ФИО из запроса (без '\0')
    // rd        — даты из запроса (ReqDates)
    // outRec    — найденная запись
    bool findInDatabase(const QByteArray &nameBytes,
                        const ReqDates   &rd,
                        PersonRecord     &outRec);

    // Формирует и шлёт клиенту бинарный ответ:
    // 2 байта daysLived + 3×4 байта float values[3]
    void sendPersonRecord(QTcpSocket *client,
                          const PersonRecord &rec);
};

#endif // SERVER_H
