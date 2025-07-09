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
    void datesReceived(const QString &birthDate, const QString &calcDate);

public slots:
    void sendText(QTcpSocket *client, const QString &text);
    void sendBinary(QTcpSocket *client, const QByteArray &data);
    void receiveCyclesAndDaysLvd(int physPct, int psychoPct, int intelPct, int daysLvd);
protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QList<QTcpSocket*> clients;
    QHash<QTcpSocket*, QByteArray> m_buf;

    // Ищет по ФИО+датам запись в бинарной базе database.db
    void findInDatabase(const Request   &req,
                        PersonRecord    &outRec);

    // Формирует и шлёт клиенту бинарный ответ:
    // 2 байта daysLived + 3×4 байта float values[3]
    void sendPersonRecord(QTcpSocket *client,
                          const PersonRecord &rec);

    int m_physPct;
    int m_psychoPct;
    int m_intelPct;
    int m_daysLvd;
};

#endif // SERVER_H
