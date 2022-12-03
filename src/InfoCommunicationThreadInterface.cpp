//
// Created by Txwh on 2022/2/6.
//

#include "InfoCommunicationThreadInterface.h"

void InfoCommunicationThreadInterface::init(){
    if(!infoCommThread.isRunning()){
        infoCommunication.moveToThread(&infoCommThread);
        infoCommThread.start();

        connect(this, SIGNAL(signal_init()), &infoCommunication, SLOT(init()));
        connect(this, SIGNAL(signal_serverListening(QString, uint16_t)), &infoCommunication, SLOT(serverListening(QString, uint16_t)));
        connect(this, SIGNAL(signal_serverStopListening()), &infoCommunication, SLOT(serverStopListening()));
        connect(this, SIGNAL(signal_serverSendMessage(std::string)), &infoCommunication, SLOT(serverSendMessage(std::string)));

        std::cout << "InfoCommInterface : move to mtFrequencyThread" << std::endl;
    }

    emit signal_init();
}

void InfoCommunicationThreadInterface::serverListening(const QString &listeningIP, uint16_t listeningPort) {
    emit signal_serverListening(listeningIP, listeningPort);
}

void InfoCommunicationThreadInterface::serverSendMessage(const std::string &message) {
    emit signal_serverSendMessage(message);
}

void InfoCommunicationThreadInterface::serverStopListening() {
    emit signal_serverStopListening();
}