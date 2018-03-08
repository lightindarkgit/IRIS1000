#include "sqlmanage.h"
#include <QDebug>
#include <QThread>

#include <unistd.h>

QString uuidGenerate()
{
    uuid_t uuid;
    char str[36];

    uuid_generate(uuid);
    uuid_unparse_lower(uuid, str);

    QString output = QString(str);

    return output;
}

QString timeGenerate()
{
    QTime current_time = QTime::currentTime();
    QDate current_date = QDate::currentDate();

    QString outputtime = QString("%1 %2")
            .arg(current_date.toString("yyyy-MM-dd"))
            .arg(current_time.toString("hh:mm:ss"));

    QString output = outputtime;

    return output;
}

SqlManage::SqlManage(QObject *parent) :
    QObject(parent),
    lastError(E_MSQL_SUCCESS)
{
    lastError = msqldatabase::get_Instance()->open();
    // qDebug() << "database open return=" << ret;
}

SqlManage::~SqlManage()
{
    msqldatabase::get_Instance()->close();
}

int SqlManage::getLastError()
{
    return lastError;
}

void SqlManage::run(QString str)
{
    cmd = str;

    QString dd = cmd + " : thread locked";
    qDebug() << dd << " (object thread id=" << QThread::currentThreadId() << ")";

    sleep(2);
    dd = cmd + " : thread finish";
    qDebug() << dd << " (object thread id=" << QThread::currentThreadId() << ")";

    return;
}

int SqlManage::setDeviceInfo()
{
    DeviceInfo devInfo;
    devInfo.m_devip = "10.3.1.70";
    devInfo.m_devname = "dj-test";
    devInfo.m_devmac = "dj-mac";
    devInfo.m_devsn = "ai500-20171219";

    int ret = msqldatabase::get_Instance()->setDeviceInfo(&devInfo);

    if (ret==E_MSQL_SUCCESS)
    {
        // 测试读出内容
         DeviceInfo devInfoRead;
        ret = msqldatabase::get_Instance()->getDeviceInfo(&devInfoRead);

        QString info = QString("id=%1, ip=%2, mac=%3, name=%4, place=%5, server=%6, port=%7, sn=%8, sub=%9, memo=%10")
                .arg(devInfoRead.m_devid).arg(devInfoRead.m_devip).arg(devInfoRead.m_devmac)
                .arg(devInfoRead.m_devname).arg(devInfoRead.m_devplace).arg(devInfoRead.m_devserverip)
                .arg(devInfoRead.m_devserverport).arg(devInfoRead.m_devsn).arg(devInfoRead.m_devsubnet)
                .arg(devInfoRead.m_memo);
        qDebug() << info;
        emit sig_printInfo(info);
    }

    return ret;
}

const int mock_iris_num = 9;
static int mock_person_index=0;

// 向pIrisList中插入pPersonInfo这个人的模拟特征，左右眼各插入num个特征
int SqlManage::insertIrisData(const PDBPersonInfo pPersonInfo, int num, QList<PIRISUserInfo>& irisList)
{
    int ret = E_MSQL_SUCCESS;

    int index = 0;

    for (index=0; index<num*2; index++)
    {
        PIRISUserInfo irisInfo = new IRISUserInfo();

        // 模拟填写数据
        irisInfo->m_irisdataid = uuidGenerate();
        irisInfo->m_personid = pPersonInfo->m_personid;

        irisInfo->m_iriscodelen = IK1000_ENROLL_FEATURE_SIZE;

        for (int i=0; i<IK1000_ENROLL_FEATURE_SIZE; i++)
        {
            irisInfo->m_iriscode[i] = (unsigned char)((i+0x1e)&0xff);
        }

        irisInfo->m_eyepiclen = IK1000_IRIS_IMG_SIZE;
        for (int i=0; i<IK1000_IRIS_IMG_SIZE; i++)
        {
            irisInfo->m_eyepic[i] = (unsigned char)((i+0x01)&0xff);
        }

        irisInfo->m_matchiriscodelen = IK1000_IDEN_FEATURE_SIZE;
        for (int i=0; i<IK1000_IDEN_FEATURE_SIZE; i++)
        {
            irisInfo->m_matchiriscode[i] = (unsigned char)((i+0x78)&0xff);
        }

        irisInfo->m_devsn = QString("1234-5678");
        irisInfo->m_eyeflag = IK1000_LEFT_EYE;
        irisInfo->m_regtime = QDateTime::currentDateTime();

        irisInfo->m_groupid = 1;

        irisInfo->m_eyeflag = index%2 + 1;
        irisInfo->m_regtime = QDateTime::currentDateTime();

        irisList.push_back(irisInfo);
    }


    return ret;
}

//  模拟插入人员和特征，一个人左右眼各配9条特征
int SqlManage::slot_insertPersonIris(int totalCount)
{
    int ret=E_MSQL_SUCCESS;

    int index;
    QList<PDBPersonInfo> personList;
    QList<PIRISUserInfo> irisList;

    for (index=0; index<totalCount; index++)
    {
        PDBPersonInfo personInfo = new DBPersonInfo();
        QString value;

        // 模拟填写数据
        personInfo->m_personid = uuidGenerate();
        value = QString("name-%1").arg(mock_person_index);
        personInfo->m_name = value;

        value = QString("ID-%1").arg(mock_person_index);
        personInfo->m_id = value;
        mock_person_index++;

        personList.push_back(personInfo);

        ret = insertIrisData(personInfo, mock_iris_num, irisList);
        if (ret==E_MSQL_SUCCESS)
        {
            ret = msqldatabase::get_Instance()->insertIrisInfos(irisList);
            QString info = QString("insert person [%3]'s iris %2 over, ret=%1").arg(ret).arg(irisList.size()).arg(personInfo->m_name);
            emit sig_printInfo(info);
        }

        while (!irisList.isEmpty())
        {
            QList<PIRISUserInfo>::iterator it = irisList.begin();
            irisList.erase(it);
            delete *it;
        }

    }

    if (ret==E_MSQL_SUCCESS)
    {
        ret = msqldatabase::get_Instance()->addPersonInfos(personList);
        QString info = QString("insert person %2 over, ret=%1").arg(ret).arg(personList.size());
        emit sig_printInfo(info);

    }

    return ret;
}


//int SqlManage::slot_insertPersonIris(int totalCount)
//{
//    int index = 0;

//    QList<PIRISUserInfo> irisList;

//    for (index=0; index<totalCount; index++)
//    {
//        PIRISUserInfo irisInfo = new IRISUserInfo();

//        // 模拟填写数据
//        irisInfo->m_irisdataid = uuidGenerate();
//        irisInfo->m_personid = uuidGenerate();

////        // 测试数据，制造最后一个不合格的数据，让插入返回，看事务是否起效果了
////        if (index==totalCount-1)
////        {
////            qDebug() << "modify last " << index << "'s irisdataid";
////            irisInfo->m_irisdataid = irisList.at(index-1)->m_irisdataid;
////        }

//        irisInfo->m_iriscodelen = IK1000_ENROLL_FEATURE_SIZE;

//        for (int i=0; i<IK1000_ENROLL_FEATURE_SIZE; i++)
//        {
//            irisInfo->m_iriscode[i] = (unsigned char)((i+0x1e)&0xff);
//        }

//        irisInfo->m_eyepiclen = IK1000_IRIS_IMG_SIZE;
//        for (int i=0; i<IK1000_IRIS_IMG_SIZE; i++)
//        {
//            irisInfo->m_eyepic[i] = (unsigned char)((i+0x01)&0xff);
//        }

//        irisInfo->m_matchiriscodelen = IK1000_IDEN_FEATURE_SIZE;
//        for (int i=0; i<IK1000_IDEN_FEATURE_SIZE; i++)
//        {
//            irisInfo->m_matchiriscode[i] = (unsigned char)((i+0x78)&0xff);
//        }

//        irisInfo->m_devsn = QString("1234-5678");
//        irisInfo->m_eyeflag = IK1000_LEFT_EYE;
//        irisInfo->m_regtime = QDateTime::currentDateTime();

//        irisInfo->m_groupid = index%4 + 1;

//        irisInfo->m_eyeflag = index%2 + 1;
//        irisInfo->m_regtime = QDateTime::currentDateTime();

//        // qDebug() << "input [" << index  << "] irisdataid=" << irisInfo->m_irisdataid;
//        irisList.push_back(irisInfo);
//    }

//    emit sig_printInfo("start insert person&iris");

//    int rolling = 0;
//    int ret;
//    int rollingtime=1;  // 测试时，设置为180，重复180次，最终加入9000条特征
//    for (rolling=0; rolling<rollingtime; rolling++)
//    {
//        // 循环插入180次50条特征，最终是9000条特征
//        ret = msqldatabase::get_Instance()->insertIrisInfo(irisList);
//        QString info = QString("insert person&iris %2 over, ret=%1").arg(ret).arg((rolling+1)*50);
//        emit sig_printInfo(info);

//        QList<PIRISUserInfo>::iterator it = irisList.begin();
//        for (; it!=irisList.end(); it++)
//        {
//           (*it)->m_irisdataid = uuidGenerate();
//        }
//    }

//    while (!irisList.isEmpty())
//    {
//        QList<PIRISUserInfo>::iterator it = irisList.begin();
//        irisList.erase(it);
//        delete *it;
//    }

//    return ret;
//}

// 测试加载虹膜特征
int SqlManage::slot_loadPersonIris()
{
    int ret = E_MSQL_SUCCESS;
    QString info;

    ret=msqldatabase::get_Instance()->getIrisTotalNum();
    info = QString("totally %1 iris (<0 means error)").arg(ret);
    emit sig_printInfo(info);

    int totalcount=ret;

    QList<ViewPersonIris> irisInfoList;

    int num = 0;
    ret = E_MSQL_SUCCESS;
    while ((num<totalcount)&&(ret==E_MSQL_SUCCESS))
    {
        ret = msqldatabase::get_Instance()->getPersonIrisInfo(irisInfoList, num, 256);
        num +=irisInfoList.size();
        info = QString("get %1 person&iris Info over, ret=%2").arg(num).arg(ret);
        emit sig_printInfo(info);
        irisInfoList.clear();
    }

    return 0;
}

// 测试插入注册参数表，只插入一条数据测试
int SqlManage::slot_insertIrisParas()
{
    //:insertEnrollParas(QList<PIRISEnrPara>& enrollInfoList)
    IRISEnrPara irisParam;
    irisParam.m_personid = uuidGenerate();
    irisParam.m_irisdataid = uuidGenerate();

    irisParam.m_groupid = 1;
    irisParam.m_eyeflag = 2;

    irisParam.m_regtime =  QDateTime::currentDateTime();

    QList<PIRISEnrPara> enrollInfoList;
    enrollInfoList.push_back(&irisParam);
    int ret = msqldatabase::get_Instance()->insertEnrollParas(enrollInfoList);

    return ret;
}

// int addPersonInfo(const QList<PDBPersonInfo>& personInfoList);//添加用户信息
int SqlManage::slot_insertPerson(int totalCount)
{
    int index = 0;
    int ret;

    QList<PDBPersonInfo> personList;

    /*
    for (index=0; index<totalCount; index++)
    {
        PDBPersonInfo personInfo = new DBPersonInfo();
        QString value;

        // 模拟填写数据
        personInfo->m_personid = uuidGenerate();
        value = QString("name-%1").arg(index);
        personInfo->m_name = value;

        value = QString("ID-%1").arg(index);
        personInfo->m_id = value;

        personList.push_back(personInfo);

    }

    emit sig_printInfo("start insert person");

    int rolling = 0;
    int ret;
    int rollingtime=1;  // 测试时，设置为180，重复180次，最终加入9000条人员
    for (rolling=0; rolling<rollingtime; rolling++)
    {
        ret = msqldatabase::get_Instance()->addPersonInfo(personList);
        QString info = QString("insert person %2 over, ret=%1").arg(ret).arg((rolling+1)*50);
        emit sig_printInfo(info);

//        QList<PIRISUserInfo>::iterator it = irisList.begin();
//        for (; it!=irisList.end(); it++)
//        {
//           (*it)->m_irisdataid = uuidGenerate();
//        }
    }

    while (!personList.isEmpty())
    {
        QList<PDBPersonInfo>::iterator it = personList.begin();
        personList.erase(it);
        delete *it;
    }
    */

    QStringList idList;
    idList.push_back("ID-47"); // 47
    idList.push_back("ID-31"); // 31

    QMap<QString, DBPersonInfo> personInfoMap;
    ret = msqldatabase::get_Instance()->getPersonInfo(personInfoMap, idList);
    if (ret==E_MSQL_SUCCESS)
    {
        qDebug() << "get " << personInfoMap.size() << "person";
        QMap<QString, DBPersonInfo>::iterator mapIt;
        for (mapIt=personInfoMap.begin(); mapIt!=personInfoMap.end(); ++mapIt)
        {
            DBPersonInfo pinfo = mapIt.value();
            qDebug() << "key=" << mapIt.key() << ", name=" << pinfo.m_name << ", id="
                     << pinfo.m_id << ", personid=" << pinfo.m_personid << ", updateTime=" << pinfo.m_updatetime.toString();
        }
    }
    else
    {
        QString info;
        info = QString("get person info error ret=%1").arg(ret);
        emit sig_printInfo(info);
        return ret;
    }

    //  测试更新人员
    DBPersonInfo personInfo = personInfoMap.begin().value();
     personInfo.m_name = "name-47-mod";
     personList.push_back(&personInfo);

    ret = msqldatabase::get_Instance()->updatePersonInfos(personList);

    QString info;
    info = QString("update person info ret=%1").arg(ret);
    emit sig_printInfo(info);

    // 测试删除人员
    idList.clear();
    idList.push_back("ID-31");
    ret = msqldatabase::get_Instance()->delPersonInfo(idList);
    info = QString("del person info ret=%1").arg(ret);
    emit sig_printInfo(info);

    // 测试获取所有id
    QMap<QString, QString> mapAllId;
    ret = msqldatabase::get_Instance()->getAllID(mapAllId);
    info = QString("get person all id ret=%1").arg(ret);
    emit sig_printInfo(info);

    QMap<QString,QString>::Iterator  it;
    for  (it=mapAllId.begin(); it!=mapAllId.end(); ++it)
    {
        qDebug() << "key : " << it.key() << " value : " << it.value();
    }

    bool hasSuper = false;
    ret = msqldatabase::get_Instance()->isSuperExist(hasSuper);

    qDebug() << "isSuperExist ret = " << ret << ", result = " << hasSuper;

    return ret;
}
