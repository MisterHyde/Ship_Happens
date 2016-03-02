#include "networkstuff.h"

/**
 * @brief NetworkStuff::NetworkStuff
 * @param cliserv
 * @param parent
 * \nConstructor.\n
 * The parameter cliserv defines if the instance of this class is the server or not.\n
 * The port number of the server is defined here.\n
 * If this instance is a server it start listening on the given port.\n
 * Else a socket is started.
 */
NetworkStuff::NetworkStuff(QString cliserv, QObject *parent)
    : QObject(parent), port(56565)
{
    // Have to be the same order as the enum mTypes!
    typeMap.insert(0, "NAME");
    typeMap.insert(1, "NAMEREQUEST");
    typeMap.insert(2, "SHOT");
    typeMap.insert(3, "BOARD");
    typeMap.insert(4, "REVENGE");
    typeMap.insert(5, "CHANGESTAT");
    iam = cliserv;
    connected = false;
    lastError = "";

    if(cliserv == "server"){
        tcpServer = new QTcpServer(this);
        tcpServer->listen(QHostAddress::Any, port);
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(startServerSocket()));
        qDebug() << "Ich bin der Server!";
    }
    else{
        tcpSocket = new QTcpSocket(this);
        qDebug() << "Ich bin der Client!";
    }
}

void NetworkStuff::sessionOpened(){

}

/**
 * @brief NetworkStuff::sendData
 * @param data
 * @return
 * \nThis methode sends the message(data) through the established tcp connection.\n
 * If data is empty return false as well as if the transmited amout of data isn't the same as the size of the message.
 */
bool NetworkStuff::sendData(const QString &pData, QString pType){
    if(pData.isEmpty()){
        qDebug() << "NetworkStuff::sendData(): Zu übertragende Daten waren leer.";
        return false;
    }

    if(!connected){
        if(iam == "server"){
            lastError = "Es wurde noch keine Verbindung zum Client hergestellt.";
        }
        else{
            lastError = "Es wurde noch keine Verbindung zum Server hergestellt.";
            if(ip.isEmpty())
                emit this->connectingToHost();
            else
                startSocket(ip);
        }
        qDebug() << lastError;
        return false;
    }

    QByteArray data = pData.toUtf8();
    QByteArray msg = "";
    // If the size of the type is lower than 10 append a 0 so it use allways 2 characters
    if(pType.size() <= 10)
        msg = "0";
    msg += QByteArray::number(pType.size()) + pType + data;

    return tcpSocket->write(msg) == msg.size();
}

/**
 * @brief NetworkStuff::receiveData
 * @return
 * \nThis slot is called if the readyRead() signal is emited.\n
 * Reads the complete buffer of the tcp socket and decide, depending on the size of the message, which signal to emit.
 * A message consists of type length + type + data.
 * The type length is allways 2 and says how many characters type contains.
 */
QByteArray NetworkStuff::receiveData(){
    QByteArray data = {0};
    data = tcpSocket->readAll();
    qDebug() << "Angekommene Daten:" << data << data.size();

    if(data.isEmpty()){
        qDebug() << "NetworkStuff::receiveData(): Message ist empty";
    }

    QString msg = (QString)data;
    // Copy the size of the type
    QString buff = msg.mid(0,2);
    quint8 typeSize = buff.toInt();
    QString type = msg.mid(2, typeSize);
    // Remove the type and the size of the type
    msg = msg.remove(0, typeSize+2);


    if(type == typeMap.value(0)){
        // NAME
        emit nameReceived(msg);
    }
    else if(type == typeMap.value(1)){
        // NAMEREQUEST
        emit nameRequest(msg);
    }
    else if(type == typeMap.value(2)){
        // SHOT
        int x = -1;
        x = msg.mid(0,1).toInt();
        int y = -1;
        y = msg.mid(1,2).toInt();
        emit shotReceived(x, y);
    }
    else if(type == typeMap.value(3)){
        // BOARD
        data = msg.toUtf8();
        emit boardReceived(data.data());
    }
    else if(type == typeMap.value(4)){
        // REVENGE
        if(msg == "1")
            emit revengeReceived(true);
        else
            emit revengeReceived(false);
    }
    else if(type == typeMap.value(5)){
        // CHANGESTAT
    }
    else{
        lastError = "Message with unkown type received: " + msg;
    }

    return data;
}

/**
 * @brief NetworkStuff::startServerSocket
 * \nSlot connected to the newConnection() signal of the server.\n
 * Opens a tcp socket with the next pending connection.\n
 * Connect the signal "readyRead()" of the socket with the slot "receiveData()".
 */
void NetworkStuff::startServerSocket(){
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    connected = true;
}

/**
 * @brief NetworkStuff::startSocket
 * @param ip
 * @return
 * \nConnect to the given ip address with at the defined in the constructor.\n
 * Waits a second for the connection to establish.\n
 * Returns the state of the socket.
 */
int NetworkStuff::startSocket(QString pIp){
    ip = pIp;
    tcpSocket->connectToHost(QHostAddress(ip), port);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    /// \todo Here a litte pause wasn't that bad especially because after this function comes an if which just works if SocketState== 3 (means ConnectedState)
    delay(1);
    connected = true;
    return tcpSocket->state();
}

/**
 * @brief NetworkStuff::sendShot
 * @param x
 * @param y
 * \nA wraper around the sendData() with other parameters.
 */
void NetworkStuff::sendShot(quint16 x, quint16 y){
    QString shott = QString::number(x) + QString::number(y);
    if(!sendData(shott, "SHOT")){
        qDebug() << "NetworkStuff::sendShot(): Fehler bei der Übertragung";
    }
}

/**
 * @brief NetworkStuff::sendBoard
 * @param board
 * \nA wraper for sendData() which does the convertion of the parameter from char* to QString.
 */
void NetworkStuff::sendBoard(char *board){
    if(!sendData(QString(board), "BOARD")){
        qDebug() << "NetworkStuff::sendBoard(): Board konnte nicht übertragen werden. TCP error:";
    }
}

/**
 * @brief NetworkStuff::delay
 * @param s
 * \nWaits the number of seconds given with the parameter "s" without blocking the qt event loop
 */
void NetworkStuff::delay(quint8 s)
{
    QTime dieTime= QTime::currentTime().addSecs(s);
    while (QTime::currentTime() < dieTime)
        QApplication::processEvents(QEventLoop::AllEvents, 100);
}

/**
 * @brief NetworkStuff::getLastError
 * @return
 * \nReturns the last error.
 * \nCurrently usless because there is no error handler
 */
QString NetworkStuff::getLastError()
{
    return lastError;
}

/**
 * @brief NetworkStuff::requestName
 * @param pName
 * \nWrapper methode for sendData() to send a namerequest with your name
 */
void NetworkStuff::requestName(QString pName)
{
    sendData(pName, "NAMEREQUEST");
}

/**
 * @brief NetworkStuff::sendName
 * @param pName
 * \nWrapper mehtode for sendData() to send your name
 */
void NetworkStuff::sendName(QString pName)
{
    sendData(pName, "NAME");
}

/**
 * @brief NetworkStuff::sendRevenge
 * @param pRev
 * \nWrapper methode for sendData() to send if you want a revenge or not
 */
void NetworkStuff::sendRevenge(bool pRev)
{
    if(pRev)
        sendData("1", "REVENGE");
    else
        sendData("0", "REVENGE");
}
