//
// Created by Txwh on 2022/2/3.
//

#include "InfoCommunication.h"

void InfoCommunication::init() {
    tcpServer = new QTcpServer;
    tcpSocket = new QTcpSocket;
    std::cout << "InfoCommunication: Init" << std::endl;
}

void InfoCommunication::serverListening(const QString & listeningIP, uint16_t listeningPort) {
    //返回主机名
    QString hostname = QHostInfo::localHostName();
    //返回主机信息
    QHostInfo qHostInfo = QHostInfo::fromName(hostname);
    //返回IP地址
    QList<QHostAddress> addList = qHostInfo.addresses();
    //IP地址
    QString IP = "";
    //判断IP地址列表是否为空
    if(!addList.isEmpty()){
        //遍历IP地址列表，输出IP地址信息
        for(int i = 0;i < addList.count();i++){
            QHostAddress aHost = addList.at(i);
            //输出IPv4信息
            if(QAbstractSocket::IPv4Protocol == aHost.protocol()){
                IP = aHost.toString();
                break;
            }
        }

        //开始监听
        QHostAddress addr(listeningIP);
        tcpServer->listen(addr, listeningPort);
        std::cout << "InfoCommunication: ServerStartListening" << std::endl;
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(serverOnNewConnection()));

        localIP = IP.toStdString();
    }
}

void InfoCommunication::serverStopListening() {
    if(tcpServer->isListening()){
        tcpServer->close();
        std::cout << "InfoCommunication: ServerStopListening" << std::endl;
    }
}

void InfoCommunication::serverSendMessage(const std::string & message) {
    QString msg = QString::fromStdString(message);
    //转换为Byte数组
    QByteArray str = msg.toUtf8();
    str.append('\n');
    if(tcpSocket->isOpen()) tcpSocket->write(str);
}

void InfoCommunication::serverOnNewConnection() {
    tcpSocket = tcpServer->nextPendingConnection();//获取接入连接的socket
    QObject::connect(tcpSocket, SIGNAL(connected()), this, SLOT(serverOnClientConnected()));
    QObject::connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(serverOnClientDisconnected()));
    QObject::connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(serverOnStateChange(QAbstractSocket::SocketState)));
    serverOnStateChange(tcpSocket->state());
    QObject::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(serverOnSocketReadyRead()));
    std::cout << "InfoCommunication: GetNewConnection" << std::endl;
}

void InfoCommunication::serverOnClientConnected() {
    std::cout << "InfoCommunication: ClientConnected: IP:" << tcpSocket->peerAddress().toString().toStdString() << std::endl;
    std::cout << "InfoCommunication: ClientConnected Port:" << tcpSocket->peerPort() << std::endl;
}

void InfoCommunication::serverOnClientDisconnected() {
    tcpSocket->close();
    std::cout << "InfoCommunication: ClientDisConnection" << std::endl;
}

void InfoCommunication::serverOnSocketReadyRead() {
    std::cout << "InfoCommunication: Read: \n" << tcpSocket->readAll().toStdString() << std::endl;
}

void InfoCommunication::serverOnStateChange(QAbstractSocket::SocketState socketState) {
    switch(socketState)
    {
        case QAbstractSocket::UnconnectedState:
            std::cout << "Socket State: UnconnectedState" << std::endl; break;
        case QAbstractSocket::HostLookupState:
            std::cout << "Socket State: HostLookupState" << std::endl; break;
        case QAbstractSocket::ConnectingState:
            std::cout << "Socket State: ConnectingState"<< std::endl; break;
        case QAbstractSocket::ConnectedState:
            std::cout << "Socket State: ConnectedState" << std::endl; break;
        case QAbstractSocket::BoundState:
            std::cout << "Socket State: BoundState" << std::endl; break;
        case QAbstractSocket::ClosingState:
            std::cout << "Socket State: ClosingState" << std::endl; break;
        case QAbstractSocket::ListeningState:
            std::cout << "Socket State: ListeningState" << std::endl; break;
    }
}

void InfoCommunication::destroy() {
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpServer->close();
    delete tcpSocket;
    delete tcpServer;
    tcpSocket = nullptr;
    tcpServer = nullptr;
    std::cout << "InfoCommunication: DeletedInfoCommunication" << std::endl;
 }