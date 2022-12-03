//
// Created by Txwh on 2022/2/6.
//

#include "MtFrequencyThreadInterface.h"

void MtFrequencyThreadInterface::init() {
    if(!mtFrequencyThread.isRunning()){
        mtFrequencyInfo.moveToThread(&mtFrequencyThread);

        connect(this, SIGNAL(signal_init_th()), &mtFrequencyInfo, SLOT(init()));
        connect(this, SIGNAL(signal_destroy()), &mtFrequencyInfo, SLOT(destroy()));
        connect(&mtFrequencyInfo, SIGNAL(signal_updated_value()), this, SLOT(dataChanged()));

        mtFrequencyThread.start();

        std::cout << "MtFrequencyThread: create mtFrequencyThread!" << std::endl;
    }
    emit signal_init_th();
    available = true;
}

void MtFrequencyThreadInterface::dataChanged() {
    //通知上层类，数据已经更新完毕信号
    emit signal_dataUpdated();
}

void MtFrequencyThreadInterface::destroyThread() {
    available = false;

    emit signal_destroy();
}