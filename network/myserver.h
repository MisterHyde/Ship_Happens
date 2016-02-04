#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    bool Start_Server();
    bool Client_Ready();
    struct shot {
        int x, y;
    };

public slots:
    void newConnection();
    void Send_Board(char *board);
    char *Receive_Board();
    void Close_Server();
    void Send_Shot(struct shot);
    struct shot Receive_Shot();

signals:
        void sendReady();

private:

    bool Connected;
    QTcpServer *server;
    QTcpSocket *socket;

};

#endif // MYSERVER_H
