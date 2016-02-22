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

    /**
     * @brief The mTypes enum
     * \nDefines the different types of messages in int
     * \nHas a right to exist because the switch statement needs constant expressions
     * \nFor a correct enum to string conversation it has to be in the same order as
     * the QMap typeMap!
     */
    enum mTypes{
        NAME,NAMEREQUEST,SHOT,BOARD,REVENGE,CHANGESTAT
    };


    //static const QMap<int,QString> typeMap;
    //constexpr static QMap<int,QString> typeMap;
    QMap<int,QString> typeMap;  ///< Defines the different types of messages in QString

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    //QNetworkSession *networkSession;
    quint16 port;
    QString iam;
    QString ip;
    bool connected;
    QString lastError;

    void delay(quint8 s);
    //quint8 stringToTypes(QString pStr);


public:
    explicit NetworkStuff( QString cliserv, QObject *parent = 0);
    // Wrapper classes for sendData
    void sendShot(quint16 x, quint16 y);
    void sendBoard(char *board);
    void requestName(QString pName);    ///< Send your own name and request the enemy to send his
    void sendName(QString pName);
    QString getLastError(); // Returns the last error message of this class

    QStringList types;
    // Stuipd second type of the QMap to make it possible to make the QMap const
    //static QMap<int,QString> typeMap2;

signals:
    //void sendReady();
    void shotReceived(int, int);    ///< This signal indicates that the enemy sent a shot
    void boardReceived(char*);      ///< This signal indicates that the enemy sent his board
    void nameReceived(QString);     ///< This signal indicates that the enemy sent his name
    void nameRequest(QString);      ///< This signal indicates that the enemy sent a namerequest
    void connectingToHost();        ///< If no ip is present emit this signal to open the ListWindow

public slots:
    int startSocket(QString pIp);

private slots:
    void sessionOpened();
    bool sendData(const QString &pData, QString pType);
    QByteArray receiveData();
    void startServerSocket();
};

#endif // NETWORKSTUFF_H
