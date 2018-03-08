#ifndef SQLMANAGE_H
#define SQLMANAGE_H

#include <QObject>

#include <uuid/uuid.h>

#include "msqldatabase.h"

class SqlManage: public QObject
{
    Q_OBJECT
public:
    explicit SqlManage(QObject *parent = 0);
    ~SqlManage();

public:
    int setDeviceInfo();
    int getLastError();

signals:
    void sig_printInfo(QString);

public slots:
    void run(QString str);              // only for test
    int slot_insertPersonIris(int);
    int slot_insertPerson(int);
    int slot_loadPersonIris();
    int slot_insertIrisParas();

private:
    QString cmd;
    int lastError;

private:
    // 向pIrisList中插入pPersonInfo这个人的模拟特征，左右眼各插入num个特征
    int insertIrisData(const PDBPersonInfo pPersonInfo, int num, QList<PIRISUserInfo>& pIrisList);


};
#endif // SQLMANAGE_H
