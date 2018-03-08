#ifndef WRITEOBJECT_H
#define WRITEOBJECT_H

#include <QObject>

class WriteObject : public QObject
{
    Q_OBJECT
public:
    explicit WriteObject(QObject *parent = 0);
    
signals:
    
public slots:
    void run(QString str);
private:
    QString cmd;

    
};

#endif // WRITEOBJECT_H
