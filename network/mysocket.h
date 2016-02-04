#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>


class MySocket : public QObject
{
    Q_OBJECT

public:
    explicit MySocket(QObject *parent = 0);
    bool Start_Socket(QString);
    void Ready();
    struct shot {
        int x, y;
    };

public slots:

    void Send_Board(char *board);
    char *Receive_Board();
    void Close_Socket();
    void Send_Shot(struct shot);
    struct shot Receive_Shot();

signals:




private:

    QTcpSocket *socket;
};

#endif // MYSOCKET_H
