//
// Created by Txwh on 2022/2/6.
//

#ifndef MEDIASTATET_MTFREQUENCYFORQML_H
#define MEDIASTATET_MTFREQUENCYFORQML_H

#include "MtFrequencyThreadInterface.h"
#include "MtBoardConnect.h"

class MtFrequencyForQml : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool dataReady MEMBER dataReady);

public:
    bool available = false;
    bool dataReady = false;

public:
    Q_INVOKABLE int get_available_num();
    Q_INVOKABLE QList<int> shake_left_value();
    Q_INVOKABLE QList<int> shake_right_value();
    Q_INVOKABLE QList<int> bar_left_value();
    Q_INVOKABLE QList<int> bar_right_value();

public slots:
    void init();
    void destroyVarious();
    void data_update();
};


#endif //MEDIASTATET_MTFREQUENCYFORQML_H
