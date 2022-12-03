//
// Created by Txwh on 2022/2/3.
//

#ifndef MEDIASTATET_INFOCOMMUNICATION_H
#define MEDIASTATET_INFOCOMMUNICATION_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <iostream>

class InfoCommunication : public QObject{
    Q_OBJECT
private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

public:
    std::string localIP = "false";

public slots:
    void init();
    /**
     * @return 返回IP地址
     * **/
    void serverListening(const QString & listeningIP, uint16_t listeningPort);
    void serverStopListening();
    void serverSendMessage(const std::string & message);
    void destroy();

private slots:
    void serverOnNewConnection();
    void serverOnClientConnected();
    void serverOnClientDisconnected();
    void serverOnSocketReadyRead();
    void serverOnStateChange(QAbstractSocket::SocketState socketState);
};

#endif //MEDIASTATET_INFOCOMMUNICATION_H
