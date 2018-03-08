#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtGlobal>
#include "mainclass.h"
#include "userlistmodel.h"
#include "usermanage.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    QString txt;
    QString fileName = context.file;
    fileName = fileName.mid(fileName.lastIndexOf("/") +1, - 1);
    QString funName = context.function;
    funName = funName.mid(funName.lastIndexOf(":") + 1, funName.indexOf("(") );
    switch (type)
    {
    //调试信息提示
    case QtDebugMsg:
        txt = QString("D:");
        break;
    //一般的warning提示
    case QtWarningMsg:
        txt = QString("W:");
        break;
    //严重错误提示
    case QtCriticalMsg:
        txt = QString("C:");
        break;
    //致命错误提示
    case QtFatalMsg:
        txt = QString("F:");
//        abort();
        break;
    }
    txt  += QString("%1(%2 %3 %4)").arg(msg).arg(fileName).arg(context.line).arg(funName);

    QString current_date_time = QDateTime::currentDateTime().toString("yyMMddhhmmss");
    QString message = QString("%1 %2").arg(current_date_time).arg(txt);

    QFile file("/home/root/AI1000.log");
    if(file.open(QIODevice::Append))
    {
        QTextStream text_stream(&file);
        text_stream << message << "\r\n";
        file.flush();
        file.close();
    }
    if(file.size() > 10*1024*1024)
    {
        QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
        QString  gz = "gzlog";  //toString().toLatin1() + "_";
        gz += fileName;
        gz.prepend("/home/root/");
        fileName.prepend("/home/root/AI1000_");
        gz.append(".tar.gz");
        fileName.append(".log");
        file.rename(fileName);
        QProcess gzpro;
        QStringList args;
        args << "-czf" << gz << fileName;
        gzpro.execute("tar", args);
        args.clear();
        args << fileName;
        gzpro.startDetached("rm", args);
    }
    file.close();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    qDebug() << "start main";
    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));
    QGuiApplication app(argc, argv);

    userManage *userManager = new userManage();
    UserListModel *userModel = new UserListModel();
//    QObject::connect(userManager, SIGNAL(sigPersonTableUpdated()), userModel, SLOT(slotModelReload()));
    QQmlApplicationEngine engine;
    mainClass * qPro = new mainClass();

    QObject::connect(userManager, SIGNAL(sigSavePerson(DBPersonInfo)), qPro, SLOT(savePersonIrisData(DBPersonInfo)));
    QObject::connect(qPro, SIGNAL(sigPersonTableUpdated()), userModel, SLOT(slotModelReload()));
    engine.rootContext()->setContextProperty("qPro", qPro);
    engine.rootContext()->setContextProperty("userManager", userManager);
    engine.rootContext()->setContextProperty("userModel", userModel);
    engine.addImageProvider(QLatin1String("screenRGB"), qPro->imgProviderRGB);
    engine.addImageProvider(QLatin1String("screenIris"), qPro->imgProviderIris);
    engine.addImageProvider(QLatin1String("IrisImgLeft"), qPro->imgProIrisImgL);
    engine.addImageProvider(QLatin1String("IrisImgRight"), qPro->imgProIrisImgR);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
