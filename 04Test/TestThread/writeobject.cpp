#include "writeobject.h"
#include <QDebug>
#include <QThread>

#include <unistd.h>

WriteObject::WriteObject(QObject *parent) :
    QObject(parent)
{
}

void WriteObject::run(QString str)
{
    cmd = str;

    QString dd = cmd + " : thread locked";
    qDebug() << dd << " (object thread id=" << QThread::currentThreadId() << ")";

    sleep(2);
    dd = cmd + " : thread finish";
    qDebug() << dd << " (object thread id=" << QThread::currentThreadId() << ")";

    return;
}
