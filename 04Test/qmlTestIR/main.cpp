#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQuickView>
#include "testclass.h"


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);
//    qmlRegisterType<testclass>("an.qt.testclass", 1, 0, "TestClass");


    QQmlApplicationEngine engine;
    testclass * qPro = new testclass();
    engine.rootContext()->setContextProperty("qPro",qPro);
    engine.addImageProvider(QLatin1String("screenRGB"),qPro->imgProviderRGB);
    engine.addImageProvider(QLatin1String("screenIris"),qPro->imgProviderIris);    
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


//    testclass * qPro = new testclass();
//    QQuickView view;
//    QQmlEngine* engine = view.engine();
//    engine->rootContext()->setContextProperty("qPro", qPro);
//    engine->addImageProvider(QLatin1String("screen"), qPro->imgProvider);
//    view.setSource(QUrl(QLatin1String("qrc:/main.qml")));
//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.show();

    return app.exec();

}
