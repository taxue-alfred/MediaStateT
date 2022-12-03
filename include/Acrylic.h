#ifndef MEDIASTATET_ACRYLIC_H
#define MEDIASTATET_ACRYLIC_H

#include <QObject>
#include <QWindow>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <iostream>

#include "WindowCompositionAttribute.h"

class Acrylic : public QObject{
    Q_OBJECT
private:
    QQmlApplicationEngine * Qml_engine;

    HWND hwnd;
    HMODULE huser;
    pfnSetWindowCompositionAttribute setWindowCompositionAttribute;

public:
    QQmlApplicationEngine* set_QmlEnginePointer(QQmlApplicationEngine & engine);

public:
    Q_INVOKABLE WId open_acrylic();
};

#endif //MEDIASTATET_ACRYLIC_H
