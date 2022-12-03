//
// Created by Txwh on 2022/2/6.
//

#ifndef MEDIASTATET_MTFREQUENCYTHREADINTERFACE_H
#define MEDIASTATET_MTFREQUENCYTHREADINTERFACE_H

#include <QObject>
#include <iostream>
#include "MtFrequencyInfo.h"

class MtFrequencyThreadInterface : public QObject{
    Q_OBJECT

public:
    MtFrequencyInfo mtFrequencyInfo;
    QThread mtFrequencyThread;

    bool available = false;

signals:
    void signal_dataUpdated();
    void signal_init_th();
    void signal_destroy();

public slots:
    void init();
    void dataChanged();
    void destroyThread();
};


#endif //MEDIASTATET_MTFREQUENCYTHREADINTERFACE_H
