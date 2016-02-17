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
    types << "NAME:" << "NAMEREQUEST:" << "SHOT:" << "BOARD:";
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
bool NetworkStuff::sendData(const QString &pData, const QString &pType){
    if(pData.isEmpty()){
        qDebug() << "NetworkStuff::sendData(): Zu übertragende Daten waren leer.";
        return false;
    }

    if(!connected){
        if(iam == "server")
            lastError = "Es wurde noch keine Verbindung zum Client hergestellt.";
        else
            lastError = "Es wurde noch keine Verbindung zum Server hergestellt.";
        qDebug() << lastError;
        return false;
    }

    QByteArray type = pType.toUtf8();
    QByteArray data = pData.toUtf8();
    QByteArray msg = QByteArray::number(type.size()) + type + data;
    qDebug() << "Zu übertragende Zeichen:" << msg;
    return tcpSocket->write(msg) == msg.size();
}

/**
 * @brief NetworkStuff::receiveData
 * @return
 * \nThis slot is called if the readyRead() signal is emited.\n
 * Reads the complete buffer of the tcp socket and decide, depending on the size of the message, which signal to emit.
 */
QByteArray NetworkStuff::receiveData(){
    QByteArray data = {0};
    data = tcpSocket->readAll();
    qDebug() << "Angekommene Daten:" << data << data.size();

    if(data.isEmpty()){
        qDebug() << "NetworkStuff::receiveData(): Message ist empty";
    }

    QString msg = (QString)data;
    QString buff = msg.mid(0,1);
    quint8 typeSize = buff.toInt();
    QString type = msg.mid(1, typeSize);
    msg = msg.mid(typeSize+1);

    switch(stringToTypes(type)){
        case BOARD:
            data = msg.toUtf8();
            emit boardReceived(data.data());
            break;
        case SHOT:
            int x;
            x = msg.mid(0,1).toInt();
            int y;
            y = msg.mid(1,2).toInt();
            emit shotReceived(x, y);
            break;
        case NAME:
            emit nameReceived(msg);
            break;
        case NAMEREQUEST:
            emit nameRequest(msg);
            break;
        default:
            qDebug() << "NetworkStuff::receiveData(): Get bad message";
    }

//    if(data.size() == 2){
//        emit shotReceived(data[0], data[1]);
//    }
//    else if(data.size() > 100){
//        QString msg = (QString)data;
//        //int typeLength = msg.indexOf(":");
//        QString type = msg;
//        type.remove(msg.size()-101,msg.size());
//        msg.remove(0, (msg.size()-100));
//        // Convert to QByteArray so it could be converted to char* because the game class doesn't use qt
//        data = msg.toUtf8();
//        emit boardReceived(data.data());
//    }

    qDebug() << "Daten erhalten:" << data;
    /// \todo Is it neccessary that the received message is returned?
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
int NetworkStuff::startSocket(QString ip){
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
    if(!sendData(shott, types.at(mTypes::SHOT))){
        qDebug() << "NetworkStuff::sendShot(): Fehler bei der Übertragung";
    }
}

/**
 * @brief NetworkStuff::receiveShot
 * @return
 * \nA wraper for receiveData() to convert the message into the needet format (struct shot).
 * \todo unused function here. I thought I should seperate the different types of message. But I didn't
 */
NetworkStuff::shot NetworkStuff::receiveShot(){
    char * data = receiveData().data();
    shot shott;
    shott.x = data[0];
    shott.y = data[1];
    return shott;
}

/**
 * @brief NetworkStuff::sendBoard
 * @param board
 * \nA wraper for sendData() which does the convertion of the parameter from char* to QString.
 */
void NetworkStuff::sendBoard(char *board){
    if(!sendData(QString(board),types.at(mTypes::BOARD))){
        qDebug() << "NetworkStuff::sendBoard(): Board konnte nicht übertragen werden. TCP error:";
    }
}

/**
 * @brief NetworkStuff::receiveBoard
 * @return
 * \nAnother wraper for receiveBoard(). Returns the received board
 * \todo wird gar nicht aufgerufen...
 */
char *NetworkStuff::receiveBoard(){
    //QString msg = QString(receiveData.data());
    //QString type = msg.remove(0, msg.size()-100);

    return receiveData().data();
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

QString NetworkStuff::getLastError()
{
    return lastError;
}

void NetworkStuff::requestName(QString pName)
{
    sendData(pName, types.at(mTypes::NAMEREQUEST));
}

void NetworkStuff::sendName(QString pName)
{
    sendData(pName, types.at(mTypes::NAME));
}

///\todo Get rid of this hole mTypes thing and do it with QMap
quint8 NetworkStuff::stringToTypes(QString pStr)
{
    mTypes blub;
    if(pStr.contains("BOARD"))
        blub = BOARD;
    else if(pStr.contains("NAME"))
        blub = NAME;
    else if(pStr.contains("NAMEREQUEST"))
        blub = NAMEREQUEST;
    else if(pStr.contains("SHOT"))
        blub = SHOT;
    else if(pStr.contains("CHANGESTAT"))
        blub = CHANGESTAT;

    return blub;
}
