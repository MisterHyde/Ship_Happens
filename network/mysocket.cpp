#include "mysocket.h"
#include <QString>
#include <QTextStream>
#include <string.h>

MySocket::MySocket(QObject *parent) :
    QObject(parent)
{
}

bool MySocket::Start_Socket(QString ip){
    socket = new QTcpSocket(this);

    //connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(Receive_Board()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(Receive_Shot()));

    socket->connectToHost(ip,1234);

    if (!socket->waitForConnected(3000)){

        return 0;
    }
    else
        return 1;
}
void MySocket::Send_Board(char *board){
    const char* poard = board;
    socket->write(poard);
}

char *MySocket::Receive_Board(){
    QByteArray board;
    board = socket->readAll();
    return board.data();
}

void MySocket::Send_Shot(struct shot shot){

    socket->write((const char*)&shot,sizeof(struct shot));
}

struct MySocket::shot MySocket::Receive_Shot(){
    QByteArray cords = socket->readAll();
    struct shot shot;
    memcpy(((char *)&shot), cords.constData(), sizeof(struct shot));
    return shot;
}

void MySocket::Ready(){
    socket->write("READY");
}

void MySocket::Close_Socket(){
    socket->close();
}
