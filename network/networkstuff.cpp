#include "networkstuff.h"

NetworkStuff::NetworkStuff(QString cliserv, QObject *parent)
    : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    if(cliserv == "server"){
        tcpServer = new QTcpServer(this);

        if (!tcpServer->listen()) {
    //        QMessageBox::critical(this, tr("Fortune Server"),
    //                              tr("Unable to start the server: %1.")
    //                              .arg(tcpServer->errorString()));
    //        close();
            return;
        }
        QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }

        // if we did not find one, use IPv4 localhost
       if (ipAddress.isEmpty())
           ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
       qDebug() << "The server is running on\n\nIP: " << ipAddress << "\nport:" << tcpServer->serverPort() << "\n\nRun the Fortune Client example now.";

        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));

    }
}

void NetworkStuff::sessionOpened(){

}

void NetworkStuff::sendData(QString data){
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);

    out.setVersion(QDataStream::Qt_5_0);
    // Write a quint16 at the first place to overwrite it later with the size of the hole sended block to make it easyer to read, for the receiving part
    out << (quint16)0;
    out << data;
    // Head back to the quint16 at the first place in the stream
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));

    tcpSocket->write(block);
    // Waits till there are data to read (ACK) on the tcpSocket. Without timeout (-1)
    tcpSocket->waitForReadyRead(-1);
    char * receive;
    tcpSocket->read(receive,3);
    qDebug() << receive;
}

void NetworkStuff::receiveShot(){
    //tcpSocket->readData()
}

bool NetworkStuff::startSocket(QString ip){
    tcpSocket->connectToHost(QHostAddress("192.168.0.188"), 56565);
}
