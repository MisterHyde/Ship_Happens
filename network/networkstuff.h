#ifndef NETWORKSTUFF_H
#define NETWORKSTUFF_H

#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QMessageBox>

class NetworkStuff : public QObject
{
    Q_OBJECT

private:
    struct shot{
        int x;
        int y;
    };
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QNetworkSession *networkSession;

public:
    explicit NetworkStuff( QString cliserv, QObject *parent = 0);
    bool startSocket(QString ip);

signals:

public slots:

private slots:
    void sessionOpened();
    void sendData(QString data);
    void receiveShot();

};

#endif // NETWORKSTUFF_H
