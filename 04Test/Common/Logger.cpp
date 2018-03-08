#include "Logger.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
//    QByteArray localMsg = msg.toLocal8Bit();
//    switch (type) {
//    case QtDebugMsg:
//        fprintf(stderr, "D:%s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
//        break;
//    case QtInfoMsg:
//        fprintf(stderr, "I %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
//        break;
//    case QtWarningMsg:
//        fprintf(stderr, "W: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
//        break;
//    case QtCriticalMsg:
//        fprintf(stderr, "C: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
//        break;
//    case QtFatalMsg:
//        fprintf(stderr, "F: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
//        abort();
//    }

    QFile file("text.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    QTextStream out(&file);
    out << msg << endl;
}

void Logger::LOGD(const char *msg)
{
    QString qmsg = QString("%s").arg(msg);
    qDebug() << qmsg;
}

 void Logger::LOGI(const char* msg)
 {
     QString qmsg = QString("%s").arg(msg);
     qInfo() << qmsg;
 }

void Logger::LOGW(const char* msg)
{
    QString qmsg = QString("%s").arg(msg);
    qWarning() << qmsg;
}

void Logger::LOGE(const char* msg)
{
    QString qmsg = QString("%s").arg(msg);
    qCritical() << qmsg;
}

