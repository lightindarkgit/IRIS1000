#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "testclass.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    testclass * qPro = new testclass();
    engine.rootContext()->setContextProperty("qPro",qPro);
    engine.addImageProvider(QLatin1String("screenRGB"),qPro->imgProviderRGB);
//    engine.addImageProvider(QLatin1String("screenIris"),qPro->imgProviderIris);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
