/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2018-02-10
描述: 识别工作者线程
**************************************************/
#ifndef IDENWORKER_H
#define IDENWORKER_H

#include <QObject>
#include "IKUSBSDK.h"

class idenWorker : public QObject
{
    Q_OBJECT
public:
    explicit idenWorker(QObject *parent = 0);
//初始化参数
    void initARG(unsigned char *codeListL, unsigned char *codeListR, int codeNumL, int codeNumR);
//获取识别线程的状态，false正在识别，true停止识别
    bool getIdenState();
    int startIden();  //开始识别接口
    int stopIden();   //停止识别接口

signals:
    void startWorker();   //请求开始识别的信号
    void idenResult(long index, int flag);   //识别结果的信号

public slots:
    void workProcess();  //识别过程

private:
    volatile bool m_isStop;       //线程停止识别状态
    unsigned char *m_idenCodeListL;   //左眼的虹膜地址
    unsigned char *m_idenCodeListR;  //右眼的虹膜地址
    int m_idenCodeNumL;   //左眼虹膜数量
    int m_idenCodeNumR;   //右眼虹膜数量
};

#endif // IDENWORKER_H
