#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

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
};

#endif // SERVER_H
