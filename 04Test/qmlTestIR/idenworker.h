#ifndef IDENWORKER_H
#define IDENWORKER_H

#include <QObject>
#include "IKUSBSDK.h"

class idenWorker : public QObject
{
    Q_OBJECT
public:
    explicit idenWorker(QObject *parent = 0);
    void initARG(unsigned char *codeListL, unsigned char *codeListR, int codeNumL, int codeNumR);
    bool getIdenState();
    int startIden();
    int stopIden();

signals:
    void startWorker();
    void idenResult(long index, int flag);

public slots:
    void workProcess();

private:
    volatile bool isStop;
    unsigned char *idenCodeListL;
    unsigned char *idenCodeListR;
    int idenCodeNumL;
    int idenCodeNumR;
};

#endif // IDENWORKER_H
