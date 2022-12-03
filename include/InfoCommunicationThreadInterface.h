//
// Created by Txwh on 2022/2/6.
//

#ifndef MEDIASTATET_INFOCOMMUNICATIONTHREADINTERFACE_H
#define MEDIASTATET_INFOCOMMUNICATIONTHREADINTERFACE_H

#include <iostream>
#include "InfoCommunication.h"

class InfoCommunicationThreadInterface : public QObject{
    Q_OBJECT

private:
    InfoCommunication infoCommunication;
    QThread infoCommThread;

signals:
    void signal_init();
    void signal_serverListening(QString IP, uint16_t port);
    void signal_serverStopListening();
    void signal_serverSendMessage(const std::string & message);

public:
    void init();
    void serverListening(const QString &listeningIP, uint16_t listeningPort);
    void serverStopListening();
    void serverSendMessage(const std::string & message);
};


#endif //MEDIASTATET_INFOCOMMUNICATIONTHREADINTERFACE_H
