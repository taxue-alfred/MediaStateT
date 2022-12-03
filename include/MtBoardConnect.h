//
// Created by Txwh on 2022/2/5.
//

#ifndef MEDIASTATET_MTBOARDCONNECT_H
#define MEDIASTATET_MTBOARDCONNECT_H

#include <QObject>
#include <QString>
#include <iostream>

#include "MtFrequencyThreadInterface.h"
#include "Netease_Music_info.h"
#include "InfoCommunicationThreadInterface.h"
#include "MtFrequencyForQml.h"

class MtBoardConnect : public QObject{
    Q_OBJECT

public:
    InfoCommunicationThreadInterface infoCommunicationThreadInterface;

    QTimer *timer;

public:
    bool available = false;

public slots:
    void init();
    void tidyData();
    void sendMessage();
    void destroyConnect();

private:
    std::string message = "";

private:
    void getConfig(std::string & IP, uint16_t & port);
};


#endif //MEDIASTATET_MTBOARDCONNECT_H
