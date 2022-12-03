//
// Created by Txwh on 2022/2/6.
//

#include "MtFrequencyForQml.h"

MtFrequencyThreadInterface mtFrequencyThreadInterface;
extern MtBoardConnect mtBoardConnect;

void MtFrequencyForQml::init() {
    if(!mtFrequencyThreadInterface.available) mtFrequencyThreadInterface.init();
    connect(&mtFrequencyThreadInterface, SIGNAL(signal_dataUpdated()), this, SLOT(data_update()));
    available = true;
}

int MtFrequencyForQml::get_available_num() {
    return mtFrequencyThreadInterface.mtFrequencyInfo.available_num;
}

QList<int> MtFrequencyForQml::shake_left_value() {
    return mtFrequencyThreadInterface.mtFrequencyInfo.shake_left_value;
}

QList<int> MtFrequencyForQml::shake_right_value() {
    return mtFrequencyThreadInterface.mtFrequencyInfo.shake_right_value;
}

QList<int> MtFrequencyForQml::bar_left_value() {
    return mtFrequencyThreadInterface.mtFrequencyInfo.bar_left_value;
}

QList<int> MtFrequencyForQml::bar_right_value() {
    return mtFrequencyThreadInterface.mtFrequencyInfo.bar_right_value;
}

void MtFrequencyForQml::data_update() {
    dataReady = true;
}

void MtFrequencyForQml::destroyVarious() {
    if(!mtBoardConnect.available){
        mtFrequencyThreadInterface.destroyThread();
    }
    dataReady = false;
    available = false;
}
