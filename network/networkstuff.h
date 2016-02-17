#ifndef NETWORKSTUFF_H
#define NETWORKSTUFF_H

#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QMessageBox>
#include <QHostAddress>
#include <QTime>
#include <QEventLoop>
#include <QApplication>

/**
 * @brief The NetworkStuff class
 * \nThis class handles the network stuff with tcp sockets. There is only one class because the task of the server
 * is just do listen if a client wants to connect. Except this the client and the server does the same thing.
 */
class NetworkStuff : public QObject
{
    Q_OBJECT

private:
    struct shot{
        int x;
        int y;
    };

    enum mTypes{
        NAME,NAMEREQUEST,SHOT,BOARD,CHANGESTAT
    };

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    //QNetworkSession *networkSession;
    quint16 port;
    QString iam;
    bool connected;
    QString lastError;

    void delay(quint8 s);
    quint8 stringToTypes(QString pStr);


public:
    explicit NetworkStuff( QString cliserv, QObject *parent = 0);
    void sendShot(quint16 x, quint16 y);
    shot receiveShot();
    void sendBoard(char *board);
    char *receiveBoard();
    QString getLastError(); // Returns the last error message of this class
    void requestName(QString pName);
    void sendName(QString pName);

    QStringList types;

signals:
    //void sendReady();
    void shotReceived(int, int);
    void boardReceived(char*);
    void nameReceived(QString);
    void nameRequest(QString);

public slots:
    int startSocket(QString ip);

private slots:
    void sessionOpened();
    bool sendData(const QString &pData, const QString &pType);
    QByteArray receiveData();
    void startServerSocket();
};

#endif // NETWORKSTUFF_H
