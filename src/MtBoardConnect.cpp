//
// Created by Txwh on 2022/2/5.
//

#include "MtBoardConnect.h"

extern MtFrequencyThreadInterface mtFrequencyThreadInterface;
extern MtFrequencyForQml mtFrequencyForQml;

void MtBoardConnect::init() {
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(sendMessage()));
    timer->start(45);

    if(!mtFrequencyThreadInterface.available){
        mtFrequencyThreadInterface.init();
    }

    connect(&mtFrequencyThreadInterface, SIGNAL(signal_dataUpdated()), this, SLOT(tidyData()));

    std::string IP = "";
    uint16_t port = 0;
    //从配置文件获取IP地址和端口
    getConfig(IP, port);

    std::cout << "MtBoardConnect: \n\t Connect IP Address : " << IP << std::endl;
    std::cout << "\t Connect Port : " << port << std::endl;

    infoCommunicationThreadInterface.init();
    infoCommunicationThreadInterface.serverListening(QString::fromStdString(IP), port);
    available = true;
}

void MtBoardConnect::getConfig(std::string & IP, uint16_t & port) {
    std::ifstream configFile("config.txt", std::ios::in);
    if (!configFile.is_open())
    {
        std::cout << "读取配置文件失败！请检查config.txt" << std::endl;
        return;
    }
    std::string port_str;
    std::getline(configFile, IP);
    std::getline(configFile, port_str);
    port = std::stoi(port_str);
    configFile.close();
}

void MtBoardConnect::tidyData() {
    message.clear();
    //等待mtFre为活跃状态
    if(mtFrequencyThreadInterface.mtFrequencyInfo.isAvailable){
        for(int i = 1; i <= 6 ; i++){
            message.append(std::to_string(mtFrequencyThreadInterface.mtFrequencyInfo.bar_left_value.at(i)));
            message.append(" ");
        }
        message.append("\n");
        for(int i = 1; i<=6; i++){
            message.append(std::to_string(mtFrequencyThreadInterface.mtFrequencyInfo.bar_right_value.at(i)));
            message.append(" ");
        }
        message.append("\n");
    }
}

void MtBoardConnect::sendMessage() {
    infoCommunicationThreadInterface.serverSendMessage(message);
}

void MtBoardConnect::destroyConnect() {
    if(!mtFrequencyForQml.available){
        mtFrequencyThreadInterface.destroyThread();
    }
    infoCommunicationThreadInterface.serverStopListening();
    available = false;
}