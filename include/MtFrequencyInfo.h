//
// Created by Txwh on 2022/1/17.
//

#ifndef MEDIASTATET_MTFREQUENCYINFO_H
#define MEDIASTATET_MTFREQUENCYINFO_H

#include <QThread>
#include <QObject>
#include <QTimer>

#include "MtMediaInfo.h"
#include "FFTW_Call.h"
#include "InfoCommunication.h"

/**@refer: https://www.cnblogs.com/judes/p/11249300.html**/

class MtFrequencyInfo : public QObject{
    Q_OBJECT

private:
    AudioSource audioSource;
    PCMData_handle pcmDataHandle;
    FFTW_Call fftwCallLeft;
    FFTW_Call fftwCallRight;

    QTimer * timer;

public:
    bool isAvailable = false;
    int available_num;
    QList<int> shake_left_value;
    QList<int> shake_right_value;
    QList<int> bar_left_value;
    QList<int> bar_right_value;

private:
    void tidyFreDataInList();
    void tidyBarDataInList(int & bar_available_num);

public slots:
    void init();
    void update_shake_value();
    void update_bar_value();
    void destroy();

signals:
    void signal_updated_value();
};

#endif //MEDIASTATET_MTFREQUENCYINFO_H