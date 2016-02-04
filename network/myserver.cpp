#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QObject(parent)
{
}

bool MyServer::Start_Server(){
    server = new QTcpServer(this);
    Connected=0;
    int hmpf=0,hmpff=0;

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any,1234)){

        return 0;
    }
    else{
        //while (Connected==0){}
        return 1;
    }
}

void MyServer::newConnection(){

    socket = new QTcpSocket(this);
    Connected=1;

    connect(socket,SIGNAL(readyRead()),this,SLOT(Receive_Board()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(Receive_Shot()));

}

void MyServer::Send_Board(char *board){
    const char *poard = board;

    socket->write(poard);
}

char *MyServer::Receive_Board(){

    QByteArray board;
    board = socket->readAll();
    return board.data();
}

void MyServer::Send_Shot(struct shot shot){

    socket->write((const char*)&shot,sizeof(struct shot));
}

struct MyServer::shot MyServer::Receive_Shot(){

    QByteArray cords = socket->readAll();
    struct shot shot;
    memcpy(((char *)&shot), cords.constData(), sizeof(struct shot));
    return shot;
}

bool MyServer::Client_Ready(){
    QByteArray read = socket->readAll();
    if (read=="READY"){
        emit sendReady();
        return 1;
    }
    return 0;
}

void MyServer::Close_Server(){
    server->close();
}

