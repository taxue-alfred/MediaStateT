#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlContext>
#include <QObject>
#include <QWindow>

#include "MtMediaInfo.h"
#include "MtFrequencyForQml.h"
#include "Acrylic.h"
#include "MtBoardConnect.h"

MtFrequencyForQml mtFrequencyForQml;
MtBoardConnect mtBoardConnect;
Acrylic acrylic;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false); // 无窗口时不关闭

    qmlRegisterType<MtMediaInfo>("qt.txwh.MT_info_get", 1, 0, "MT_info_get");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("mtFrequency", &mtFrequencyForQml);
    engine.rootContext()->setContextProperty("mtBoardConnect", &mtBoardConnect);
    engine.rootContext()->setContextProperty("Acrylic", &acrylic);

    engine.load(QUrl(QStringLiteral("qrc:/qml/media_stateT.qml")));

    acrylic.set_QmlEnginePointer(engine);

    return app.exec();
}
