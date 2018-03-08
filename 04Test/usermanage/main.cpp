#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QtQml>
#include "userlistmodel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    qmlRegisterType<UserListModel>("an.qt.CModel", 1, 0, "UserListModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
