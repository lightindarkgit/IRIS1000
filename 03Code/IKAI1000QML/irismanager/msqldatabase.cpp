#include "msqldatabase.h"
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include <iostream>

using namespace std;
msqldatabase* msqldatabase::m_baseInstance = 0;
/*********************************
 功      能: 构造函数 定义了数据库的数据库名和路径，用户名和密码
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:无
 返  回 值:
**********************************/
msqldatabase::msqldatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("IKAI1KBio.db");
    database.setUserName("root");
    database.setPassword("123456");
}
/*********************************
 功      能:单例模式的数据库
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:无
 返  回 值:
**********************************/
msqldatabase *msqldatabase::get_Instance()
{
    if(m_baseInstance == 0)
    {
        m_baseInstance = new msqldatabase();
    }
    return m_baseInstance;
}
/*********************************
 功      能:释放数据库对象
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:无
 返  回 值:无
**********************************/
void msqldatabase::Release()
{
    m_baseInstance->close();
    delete m_baseInstance;
    m_baseInstance = NULL;
}
/*********************************
 功      能:打开数据库，并且判断数据库表的完整性
 作      者:tangzhuan
 日      期:20171205
 修  改 人:yqhe
 修改内容:数据表内容有变化，增加数据项
 修改日期:20180208
 参      数:无
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::open()
{
    if (!database.isOpen())
    {
        if (!database.open())
        {
            return E_MSQL_OPEN_ERROR;
        }
    }

    qDebug() << "Database Opened";
    QStringList tableList = database.tables();

    //判断数据表device是否存在，不存在则创建
    if(!tableList.contains("device"))
    {
        QSqlQuery sql_query;
        QString create_sql = "create table device (";
        create_sql.append("devid integer not null DEFAULT 0,");
        create_sql.append("devname varchar(32),");
        create_sql.append("devsn varchar(18) not null,");
        create_sql.append("devip varchar(16),");
        create_sql.append("devmac varchar(18),");
        create_sql.append("devsubnet varchar(16) ,");
        create_sql.append("devserverip varchar(16),");
        create_sql.append("devserverport integer not null DEFAULT 0,");
        create_sql.append("devplace varchar(64),");
        create_sql.append("memo text");
        create_sql.append(")");
        sql_query.prepare(create_sql);//创建表

        if(!sql_query.exec()) //查看创建表是否成功
        {
            dumpError(sql_query, "create table device", create_sql);
            return E_MSQL_OPEN_DEVICE_ERROR;
        }
        else
        {
            qDebug()<< "Table device Created" ;
        }
    }

    //判断数据表irisdatabase是否存在，不存在则创建
    if(!tableList.contains("irisdatabase"))
    {
        QSqlQuery sql_query;

        QString create_sql = "create table irisdatabase (";
        create_sql.append("irisdataid varchar(38) not null primary key,");
        create_sql.append("personid varchar(38) not null,");
        create_sql.append("groupid INTEGER not null,");
        create_sql.append("iriscode BLOB not null,");
        create_sql.append("eyepic BLOB not null,");
        create_sql.append("matchiriscode BLOB not null,");
        create_sql.append("devsn varchar(32) not null,");
        create_sql.append("eyeflag INTEGER not null DEFAULT 0,");
        create_sql.append("regtime datetime not null,");
        create_sql.append("createtime datetime not null default (datetime('now', 'localtime')),");
        create_sql.append("updatetime datetime");
        create_sql.append(")");
        sql_query.prepare(create_sql);//创建表
        if(!sql_query.exec()) //查看创建表是否成功
        {
            dumpError(sql_query, "create table irisdatabase");
            return E_MSQL_OPEN_IRISDATABASE_ERROR;
        }
        else
        {
            qDebug()<< "Table irisdatabase Created" ;
        }
    }
    //判断数据表irisalgo是否存在，不存在则创建
    if(!tableList.contains("irisalgo"))
    {
        QSqlQuery sql_query;
        QString create_sql = "create table irisalgo (";
        create_sql.append("irisdataid varchar(38) not null primary key,");
        create_sql.append("personid varchar(38) not null,");
        create_sql.append("regtime datetime not null,");
        create_sql.append("eyeflag INTEGER not null DEFAULT 0,");
        create_sql.append("groupid INTEGER not null,");
        create_sql.append("createtime datetime not null default (datetime('now', 'localtime')),");
        create_sql.append("updatetime datetime,");
        create_sql.append("memo text,");
        create_sql.append("pupilrow Integer DEFAULT 0,");
        create_sql.append("pupilcol Integer DEFAULT 0,");
        create_sql.append("pupilradius Integer DEFAULT 0,");
        create_sql.append("irisrow Integer not null DEFAULT 0,");
        create_sql.append("iriscol Integer not null DEFAULT 0,");
        create_sql.append("irisradius Integer not null DEFAULT 0,");
        create_sql.append("focusscore Integer not null DEFAULT 0,");
        create_sql.append("percentvisible Integer not null DEFAULT 0,");
        create_sql.append("spoofvalue Integer DEFAULT 0,");
        create_sql.append("interlacevalue Integer not null DEFAULT 0,");
        create_sql.append("qualitylevel Integer DEFAULT 0,");
        create_sql.append("qualityscore Integer not null DEFAULT 0");
        create_sql.append(")");

        sql_query.prepare(create_sql);//创建表

        if(!sql_query.exec()) //查看创建表是否成功
        {
            dumpError(sql_query, "create table irisalgo");
            return E_MSQL_OPEN_IRISALGO_ERROR;
        }
        else
        {
            qDebug()<< "Table irisalgo Created" ;
        }
    }

    //判断数据表person是否存在，不存在则创建
    // modified at 20180301 by yqhe,增加虚拟卡号
    if(!tableList.contains("person"))
    {
        QSqlQuery sql_query;
        QString create_sql = "create table person (";
        create_sql.append("personid varchar(38) not null primary key,");
        create_sql.append("name varchar(256) not null,");
        create_sql.append("id varchar(64) not null,");
        create_sql.append("superid integer not null DEFAULT 0,");
        create_sql.append("sex varchar(4),");
        create_sql.append("cardid varchar(16),");
        create_sql.append("vcardid varchar(16),");      // added at 20180228 by yqhe, 增加虚拟卡
        create_sql.append("idcard varchar(20),");
        create_sql.append("memo text,");
        create_sql.append("profession varchar(32),");
        create_sql.append("hasirisdata Integer not null DEFAULT 0,");
        create_sql.append("address text,");
        create_sql.append("password varchar(16),");
        create_sql.append("createtime datetime not null default (datetime('now', 'localtime')),");
        create_sql.append("updatetime datetime not null");
        create_sql.append(")");
        sql_query.prepare(create_sql);//创建表

        if(!sql_query.exec()) //查看创建表是否成功
        {
            dumpError(sql_query, "create table person");
            return E_MSQL_OPEN_PERSON_ERROR;
        }
        else
        {
            qDebug()<< "Table person Created" ;
        }
    }
    //判断数据表reclog是否存在，不存在则创建
    if(!tableList.contains("reclog"))
    {
        QSqlQuery sql_query;
        QString create_sql = "create table reclog (";
        //create_sql.append("reclogid integer not null DEFAULT 0,");
        // modified at 20180226 by yqhe, 设置为自增长字段
        create_sql.append("reclogid integer PRIMARY KEY  autoincrement,");
        create_sql.append("personid varchar(38) not null,");
        create_sql.append("irisdataid varchar(38) not null,");
        create_sql.append("recogtime datetime not null,");
        create_sql.append("recogtype integer not null DEFAULT 0,");
        create_sql.append("devsn varchar(32) not null,");
        create_sql.append("memo text");
        create_sql.append(")");
        sql_query.prepare(create_sql);//创建表
        if(!sql_query.exec()) //查看创建表是否成功
        {
            dumpError(sql_query, "create table reclog");
            return E_MSQL_OPEN_RECLOG_ERROR;
        }
        else
        {
            qDebug()<< "Table reclog Created" ;
        }
    }
    else
    {
        _001updateReclogAuto();
    }

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:设置识别记录表的logid为自增长类型
                 如果表已经存在，且不是自增长类型
                 则删除之前已有的记录，重新设置字段类型
 作      者:yqhe
 日      期:20180226
 修  改 人:
 修改内容:
 修改日期:
 参      数:无
 返  回 值:无
**********************************/
int msqldatabase::_001updateReclogAuto()
{
    QStringList tableList = database.tables();
    if(!tableList.contains("reclog"))
    {
        // 只做更新操作，如果表不存在，则返回
        return E_MSQL_SUCCESS;
    }

    QSqlQuery sql_query;
    QString query_data = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='reclog' AND sql LIKE  \
            '%reclogid integer PRIMARY KEY  autoincrement%' COLLATE NOCASE;"; //查询数据

    sql_query.prepare(query_data); //查询
    if (!sql_query.exec())
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_MASTER_SELECT_ERROR;
    }

    if (!sql_query.next())
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_MASTER_SELECT_ERROR;
    }

    int value = sql_query.value(0).toInt();
    if (value==0)
    {
        // 之前的考勤记录表没有设置自增长字段
        // sqlite不能修改字段类型，采用
        // 1、删除旧表
        // 2、创建新表
        // 的方式。因为目前在测试阶段，可以直接对数据库操作
         query_data = "DROP TABLE reclog;";
         sql_query.prepare(query_data); //查询
         if (!sql_query.exec())
         {
             dumpError(sql_query, __FUNCTION__);
             return E_MSQL_MASTER_SELECT_ERROR;
         }

         QString create_sql = "create table reclog (";
         //create_sql.append("reclogid integer not null DEFAULT 0,");
         // modified at 20180226 by yqhe, 设置为子增长字段
         create_sql.append("reclogid integer PRIMARY KEY  autoincrement,");
         create_sql.append("personid varchar(38) not null,");
         create_sql.append("irisdataid varchar(38) not null,");
         create_sql.append("recogtime datetime not null,");
         create_sql.append("recogtype integer not null DEFAULT 0,");
         create_sql.append("devsn varchar(32) not null,");
         create_sql.append("memo text");
         create_sql.append(")");
         sql_query.prepare(create_sql);//创建表
         if(!sql_query.exec()) //查看创建表是否成功
         {
             dumpError(sql_query, "create table reclog");
             return E_MSQL_OPEN_RECLOG_ERROR;
         }
         else
         {
             qDebug()<< "Table reclog Created" ;

             // 重置自增长ID
             QString query_data ="UPDATE sqlite_sequence SET seq = 1 WHERE name = 'reclog';";
             sql_query.prepare(query_data); //查询
             if (!sql_query.exec())
             {
                 dumpError(sql_query, __FUNCTION__);
                 return E_MSQL_MASTER_SELECT_ERROR;
             }
         }

    }

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:数据库关闭
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:无
 返  回 值:无
**********************************/
void msqldatabase::close()
{
    database.close();
}
/*********************************
 功      能:设置设备信息
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:IN deviceInfo 设备信息类
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::setDeviceInfo(PDeviceInfo deviceInfo)
{
    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    QSqlQuery sql_query;
    QString query_data = "SELECT count(*) FROM device"; //查询数据

    sql_query.prepare(query_data); //查询
    if (!sql_query.exec())
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_DEVICE_SET_SELECT_ERROR;
    }

    if (!sql_query.next())
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_DEVICE_SET_SELECT_ERROR;
    }

    // 表中只写一行数据
    if(!sql_query.value(0).toInt())
    {
        // 无数据则插入
        QString insert_data = "INSERT INTO device (devid, devname, devsn, devip,devmac,devsubnet,\
                devserverip,devserverport,devplace,memo) \
                VALUES (:devid, :devname, :devsn, :devip,:devmac,:devsubnet,\
                        :devserverip,:devserverport,:devplace,:memo)";
                sql_query.prepare(insert_data);
        sql_query.bindValue(":devid",deviceInfo->m_devid);
        sql_query.bindValue(":devname",deviceInfo->m_devname);
        sql_query.bindValue(":devsn",deviceInfo->m_devsn);
        sql_query.bindValue(":devip",deviceInfo->m_devip);
        sql_query.bindValue(":devmac",deviceInfo->m_devmac);
        sql_query.bindValue(":devsubnet",deviceInfo->m_devsubnet);
        sql_query.bindValue(":devserverip",deviceInfo->m_devserverip);
        sql_query.bindValue(":devserverport",deviceInfo->m_devserverport);
        sql_query.bindValue(":devplace",deviceInfo->m_devplace);
        sql_query.bindValue(":memo",deviceInfo->m_memo);

        if (!sql_query.exec()) //查看插入是否成功
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_DEVICE_SET_INSERT_ERROR;
        }
        else
        {
            dumpError(sql_query, __FUNCTION__);
            qDebug()<<QObject::tr("device table add record success!");
        }
    }
    else
    {
        // 有数据则更新
        QString update_data = "UPDATE device SET devid = :devid, devname = :devname, devsn = :devsn, \
                devip = :devip,devmac = :devmac,devsubnet = :devsubnet,\
                devserverip = :devserverip,devserverport = :devserverport,\
                devplace = :devplace,memo = :memo";

        sql_query.prepare(update_data);

        sql_query.bindValue(":devid",deviceInfo->m_devid);
        sql_query.bindValue(":devname",deviceInfo->m_devname);
        sql_query.bindValue(":devsn",deviceInfo->m_devsn);
        sql_query.bindValue(":devip",deviceInfo->m_devip);
        sql_query.bindValue(":devmac",deviceInfo->m_devmac);
        sql_query.bindValue(":devsubnet",deviceInfo->m_devsubnet);
        sql_query.bindValue(":devserverip",deviceInfo->m_devserverip);
        sql_query.bindValue(":devserverport",deviceInfo->m_devserverport);
        sql_query.bindValue(":devplace",deviceInfo->m_devplace);
        sql_query.bindValue(":memo",deviceInfo->m_memo);

        if (!sql_query.exec()) //查看覆盖是否成功
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_DEVICE_SET_UPDATE_ERROR;
        }
        else
        {
            qDebug()<<QObject::tr("device table update record success!");
        }
    }

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:获取设备信息
 作      者:tangzhuan
 日      期:20171205
 修  改 人:yqhe
 修改内容:修改格式，避免过多的{}
 修改日期:20180209
 参      数:OUT deviceInfo 设备信息类
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::getDeviceInfo(PDeviceInfo deviceInfo)
{
    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    QSqlQuery sql_query;
    QString query_data = "SELECT * FROM device"; //查询数据

    sql_query.prepare(query_data); //查询
    if(!sql_query.exec()) //
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_DEVICE_GET_SELECT_ERROR;
    }

    sql_query.next();
    QSqlRecord rec = sql_query.record();

    if(rec.isEmpty())
    {
        // 没有查询到数据
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_DEVICE_GET_NULL_ERROR;
    }

    deviceInfo->m_devid = rec.value("devid").toInt();
    deviceInfo->m_devip = rec.value("devip").toString();
    deviceInfo->m_devmac = rec.value("devmac").toString();
    deviceInfo->m_devname = rec.value("devname").toString();
    deviceInfo->m_devplace = rec.value("devplace").toString();
    deviceInfo->m_devserverip = rec.value("devserverip").toString();
    deviceInfo->m_devserverport = rec.value("devserverport").toInt();
    deviceInfo->m_devsn = rec.value("devsn").toString();
    deviceInfo->m_devsubnet = rec.value("devsubnet").toString();
    deviceInfo->m_memo = rec.value("memo").toString();

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:检查虹膜数据是否需要插入
 描      述:虹膜特征长度是否不符合要求；虹膜特征在数据库中是否已存在
 作      者:yqhe
 日      期:20180209
 修  改 人:
 修改内容:
 修改日期:
 参      数:IN irisInfo 虹膜信息
 返  回 值:成功返回E_MSQL_SUCCESS,
失败返回错误码
E_MSQL_FORMAT_ERROR 虹膜特征长度不符合要求
E_MSQL_RECORD_EXIST_ERROR 虹膜特征在数据库中已存在
E_MSQL_ACCESS_ERROR 数据库访问错误
前两种错误可以跳过这条虹膜数据不保存
后一种错误就返回保存失败
**********************************/
int msqldatabase::checkIrisData(PIRISUserInfo irisInfo)
{
    if (irisInfo->m_iriscodelen!=IK1000_ENROLL_FEATURE_SIZE)
    {
        // 如果发来的数据中注册特征长度与实际特征长度不一致，则不需要保存这条特征
        return E_MSQL_FORMAT_ERROR;
    }

    // 查询这条特征是否存在
    QSqlQuery sql_query;
    QString query_data = "SELECT count(*) FROM irisdatabase WHERE irisdataid = :irisdataid"; //查询数据
    sql_query.prepare(query_data); //查询
    sql_query.bindValue(":irisdataid", irisInfo->m_irisdataid);

    if (!sql_query.exec())
    {
        // 查询失败
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_ACCESS_ERROR;
    }

    sql_query.next();
    int value = sql_query.value(0).toInt();
    if (value!=0)
    {
        // 这条特征在数据库中已存在，不需要保存
        return E_MSQL_RECORD_EXIST_ERROR;
    }

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:插入虹膜信息列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:yqhe
 修改内容:增加对虹膜数据的检查；增加事务
 修改日期:20180209
 参      数:IN infoList 虹膜信息列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
#include <QFile>
#include <QDataStream>

int msqldatabase::insertIrisInfos(QList<PIRISUserInfo> &infoList)
{
    int nret = E_MSQL_SUCCESS;

    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    qDebug() << "msqldatabase::insertIrisInfos" << infoList.length();
    // 开启事务，全部成功完成后提交，数据保存
    // 如果中间出错，之前的数据全部丢弃
    database.transaction();

//    QFile enrIris("enrIrisdbwrite.txt");
//    enrIris.open(QIODevice::WriteOnly);
//    QDataStream out(&enrIris);
//    QByteArray ba;
//    ba.resize(6 * IK1000_ENROLL_FEATURE_SIZE); //设置容量

    for(int i = 0; i < infoList.length();i++)
    {
        nret = checkIrisData(infoList.at(i));
        if (nret==E_MSQL_ACCESS_ERROR)
        {
            return E_MSQL_IRISDATABASE_INSERT_SELECT_ERROR;
        }

        if (nret!=E_MSQL_SUCCESS)
        {
            // 如果发来的数据格式检查有问题，则不需要保存这条特征
            continue;
        }

        QSqlQuery sql_query;

        //  整理数据，如果没有数据，则写入NULL
        QVariant qvIrisCode = QVariant(QVariant::ByteArray);
        QVariant qvEyePic   = QVariant(QVariant::ByteArray);
        QVariant qvMatchCode= QVariant(QVariant::ByteArray);
        QVariant qvDevSn    = QVariant(QVariant::String);
        QVariant qvRegtime  = QVariant(QVariant::DateTime);

        qDebug() << "msqldatabase::insertIrisInfos [" <<  i << "], featurelen=" << infoList.at(i)->m_iriscodelen;

        if (infoList.at(i)->m_iriscodelen>0)
        {
            QByteArray  feature = QByteArray::fromRawData((const char *)infoList.at(i)->m_iriscode, infoList.at(i)->m_iriscodelen);
            qvIrisCode = feature;
//            memcpy(ba.data() + i * IK1000_ENROLL_FEATURE_SIZE, feature.data(), IK1000_ENROLL_FEATURE_SIZE); //指针移动,写入多个数据
        }

        if (infoList.at(i)->m_eyepiclen>0)
        {
            QByteArray  eyepic = QByteArray::fromRawData((const char *)infoList.at(i)->m_eyepic, infoList.at(i)->m_eyepiclen);
            qvEyePic = eyepic;
        }

        if (infoList.at(i)->m_matchiriscodelen>0)
        {
            QByteArray  match = QByteArray::fromRawData((const char *)infoList.at(i)->m_matchiriscode, infoList.at(i)->m_matchiriscodelen);
            qvMatchCode = match;
        }

        if (!infoList.at(i)->m_devsn.isEmpty())
        {
            qvDevSn = QVariant(infoList.at(i)->m_devsn);
        }

        qvRegtime = QVariant(infoList.at(i)->m_regtime);

        QString insert_data = "INSERT INTO irisdatabase (irisdataid,personid, groupid, iriscode,eyepic,matchiriscode,devsn,eyeflag,regtime)\
                VALUES (:irisdataid,:personid,:groupid, :iriscode,:eyepic,:matchiriscode,:devsn,:eyeflag,:regtime)";
                sql_query.prepare(insert_data);

        sql_query.bindValue(":irisdataid",infoList.at(i)->m_irisdataid);
        sql_query.bindValue(":personid",infoList.at(i)->m_personid);
        sql_query.bindValue(":groupid",infoList.at(i)->m_groupid);
        sql_query.bindValue(":iriscode",qvIrisCode);
        sql_query.bindValue(":eyepic",qvEyePic);
        sql_query.bindValue(":matchiriscode",qvMatchCode);
        sql_query.bindValue(":devsn", qvDevSn);
        sql_query.bindValue(":eyeflag",infoList.at(i)->m_eyeflag);
        sql_query.bindValue(":regtime", qvRegtime);

        if(!sql_query.exec()) //查看插入是否成功
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_IRISDATABASE_INSERT_INSERT_ERROR;
        }

    } // end of for

//    out << ba;
//    enrIris.close();

    //提交
    database.commit();

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:根据personid列表，获取虹膜信息列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:OUT userInfoList 虹膜信息列表
            IN personidList  personid列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::getIrisInfo(QList<PIRISUserInfo>& userInfoList, QStringList personidList)
{
    if(database.isOpen())
    {
        userInfoList.clear();
        for(int i = 0;i < personidList.length();i++)
        {
            QSqlQuery sql_query;
            QString query_data = "SELECT * FROM irisdatabase where personid=:personid"; //查询数据

            sql_query.prepare(query_data); //查询
            sql_query.bindValue(":personid", personidList.at(i));
            if(!sql_query.exec()) //查看查询是否成功
            {
                //                qDebug()<<QObject::tr("SELECT Table failed");
                qDebug()<< sql_query.lastError().number();
                return E_MSQL_IRISDATABASE_GET_SELECT_ERROR;
            }
            else
            {
                //循环获取符合条件的特征和对应的ID
                while(sql_query.next())
                {
                    QSqlRecord rec = sql_query.record();
                    if(!rec.isEmpty())
                    {
                        PIRISUserInfo userInfo = new IRISUserInfo();
                        userInfo->m_devsn = rec.value("devsn").toString();
                        userInfo->m_eyeflag = rec.value("eyeflag").toInt();
                        memcpy(userInfo->m_eyepic,rec.value("eyepic").toByteArray().data(),rec.value("eyepic").toByteArray().size());
                        memcpy(userInfo->m_iriscode,rec.value("iriscode").toByteArray().data(),rec.value("iriscode").toByteArray().size());
                        memcpy(userInfo->m_matchiriscode,rec.value("matchiriscode").toByteArray().data(),rec.value("matchiriscode").toByteArray().size());
                        userInfo->m_irisdataid = rec.value("irisdataid").toString();
                        userInfo->m_personid = rec.value("personid").toString();
                        userInfo->m_regtime = rec.value("regtime").toDateTime();
                        userInfoList << userInfo;
                    }
                    else
                    {
                        qDebug()<< sql_query.lastError().number();
                        return E_MSQL_IRISDATABASE_GET_NULL_ERROR;
                    }
                }
            }
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:根据personid列表，删除虹膜信息列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:IN personidList  personid列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::delIrisInforForPersonid(QStringList personidList)
{
    if(database.isOpen())
    {
        for(int i = 0; i < personidList.length();i++)
        {
            /*****   删除ID对应的用户数据  *****/
            QSqlQuery sql_query;
            QString query_data = "delete from irisdatabase where personid = :personid"; //删除数据

            sql_query.prepare(query_data); //删除
            sql_query.bindValue(":personid", personidList.at(i));
            if(!sql_query.exec()) //查看删除是否成功
            {
                //                qDebug()<<QObject::tr("select failed");
                qDebug()<<sql_query.lastError();
                return E_MSQL_IRISDATABASE_DELPID_DELETE_ERROR;
            }
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:根据irisdataid列表，删除虹膜信息列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:IN irisdataidList  irisdataid列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::delIrisInforForIrisdataid(QStringList irisdataidList)
{
    if(database.isOpen())
    {
        for(int i = 0; i < irisdataidList.length();i++)
        {
            /*****   删除ID对应的用户数据  *****/
            QSqlQuery sql_query;
            QString query_data = "delete from irisdatabase where irisdataid = :irisdataid"; //删除数据

            sql_query.prepare(query_data); //删除
            sql_query.bindValue(":irisdataid", irisdataidList.at(i));
            if(!sql_query.exec()) //查看删除是否成功
            {
                //                qDebug()<<QObject::tr("select failed");
                qDebug()<<sql_query.lastError();
                return E_MSQL_IRISDATABASE_DELIRISID_DELETE_ERROR;
            }
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:获取所有虹膜特征条数
 作      者:yqhe
 日      期:20180219
 修  改 人:
 修改内容:
 修改日期:
 参      数:
 返  回 值:返回查询得到的特征条msqldatabase:数(>=0)，如果失败，则为错误码(<0)
**********************************/
int msqldatabase::getIrisTotalNum()
{
    int ret = E_MSQL_SUCCESS;

    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    QSqlQuery sql_query;
    QString query_data = "SELECT count(*) FROM irisdatabase"; //查询数据

    sql_query.prepare(query_data); //查询
    if (!sql_query.exec())
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_IRISDATABASE_GET_SELECT_ERROR;
    }

    if (!sql_query.next())
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_IRISDATABASE_GET_SELECT_ERROR;
    }

    // 获取虹膜条数msqldatabase:
    ret = sql_query.value(0).toInt();

    return ret;
}

/*********************************
 功      能:按顺序获取部分虹膜特征
                查询顺序为先按人员uuid排序，再按虹膜uuid排序
 作      者:yqhe
 日      期:20180221
 修  改 人:
 修改内容:
 修改日期:
 参      数:OUT irisInfoList -- 查询得到的虹膜数据，当返回值为E_MSQL_SUCCESS时，数据可信
                IN offset -- 查询起点
                IN limit -- 查询条数，缺省为2000
 返  回 值:错误码
                 E_MSQL_IRISDATABASE_GET_NULL_ERROR 没有查询到数据
                 E_MSQL_SUCCESS 有数据，且查询成功
**********************************/
int msqldatabase::getPersonIrisInfo(QList<ViewPersonIris>& irisInfoList, int offset, int limit)
{
    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    irisInfoList.clear();

    QSqlQuery sql_query;

    //查询数据
    // 经测试，如果排序的话，花费时间会很长
    // 5450条虹膜数据，不排序花费0.104秒；排序花费9.841秒；即使加上了索引也是如此，不知道为什么
    // 所以暂时不排序了
    QString query_data = "SELECT idb.personid, idb.irisdataid, idb.eyeflag, idb.iriscode, ";
    query_data += " pp.name, pp.cardid, pp.id, pp.sex, pp.superid  FROM irisdatabase idb ";
    query_data += " LEFT JOIN person pp ON pp.personid=idb.personid ";
//    query_data += " ORDER BY idb.personid, idb.irisdataid ";
    if (limit>0)
    {
        query_data += QString(" limit %1, %2;").arg(offset).arg(limit);
    }

    sql_query.prepare(query_data); //查询
    sql_query.setForwardOnly(true);

    qDebug() << sql_query.lastQuery() <<  QDateTime::currentDateTime();

    if (!sql_query.exec()) //查看查询是否成功
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_IRISDATABASE_GET_SELECT_ERROR;
    }

    qDebug()<<"query over"<<  QDateTime::currentDateTime();

//    QFile enrIris("enrIrisdbread.txt");
//    enrIris.open(QIODevice::WriteOnly);
//    QDataStream out(&enrIris);
//    QByteArray ba;
//    ba.resize(6 * IK1000_ENROLL_FEATURE_SIZE); //设置容量
//    int i=0;

    //循环获取符合条件的特征和对应的ID
    while (sql_query.next())
    {
        QSqlRecord rec = sql_query.record();

        if (rec.isEmpty())
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_IRISDATABASE_GET_NULL_ERROR;
        }

        ViewPersonIris viewInfo;
        viewInfo.m_personid = rec.value("personid").toString();
        viewInfo.m_irisdataid = rec.value("irisdataid").toString();
        viewInfo.m_eyeflag = rec.value("eyeflag").toInt();

       QByteArray feature = rec.value("iriscode").toByteArray();

        memcpy(viewInfo.m_iriscode, feature.data(), feature.size());

//        qDebug() << "read from db, code size=" << feature.size();
//        memcpy(ba.data() + i * IK1000_ENROLL_FEATURE_SIZE, feature.data(), IK1000_ENROLL_FEATURE_SIZE); //指针移动,写入多个数据

        viewInfo.m_name = rec.value("name").toString();
        viewInfo.m_cardid = rec.value("cardid").toString();
        viewInfo.m_userid = rec.value("id").toString();
        viewInfo.m_sex = rec.value("sex").toString();
        viewInfo.m_superid = rec.value("superid").toBool();

        irisInfoList.push_back(viewInfo);
    }

    qDebug()<<"get over"<<  QDateTime::currentDateTime();

//    out << ba;
//    enrIris.close();

    return E_MSQL_SUCCESS;
}


/*********************************
 功      能:插入虹膜注册参数列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:IN enrollInfoList 虹膜注册参数列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::insertEnrollParas(QList<PIRISEnrPara>& enrollInfoList)
{
    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    for(int i = 0; i < enrollInfoList.length();i++)
    {
        QSqlQuery sql_query;
        QString query_data = "SELECT count(*) FROM irisalgo WHERE irisdataid = :irisdataid"; //查询数据

        sql_query.prepare(query_data); //查询
        sql_query.bindValue(":irisdataid",enrollInfoList.at(i)->m_irisdataid);
        //查看当前ID是否存在记录
        if(!sql_query.exec())
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_IRISALGO_INSERT_SELECT_ERROR;
        }

        sql_query.next();
        int value = sql_query.value(0).toInt();

        /*****   如果不存在记录则插入  *****/
        if (value!=0)
        {
            continue;
        }

        QString insert_data = "INSERT INTO irisalgo (irisdataid,personid,regtime,eyeflag,groupid,memo,pupilrow,pupilcol,pupilradius,irisrow,iriscol,irisradius,\
                focusscore,percentvisible,spoofvalue,interlacevalue,qualitylevel,qualityscore)\
                VALUES (:irisdataid,:personid,:regtime,:eyeflag, :groupid, :memo,:pupilrow,:pupilcol,:pupilradius,:irisrow,:iriscol,:irisradius,\
                        :focusscore,:percentvisible,:spoofvalue,:interlacevalue,:qualitylevel,:qualityscore)";
                sql_query.prepare(insert_data); //插入

        sql_query.bindValue(":irisdataid",enrollInfoList.at(i)->m_irisdataid);
        sql_query.bindValue(":personid",enrollInfoList.at(i)->m_personid);
        sql_query.bindValue(":regtime",enrollInfoList.at(i)->m_regtime);
        sql_query.bindValue(":eyeflag",enrollInfoList.at(i)->m_eyeflag);
        sql_query.bindValue(":groupid",enrollInfoList.at(i)->m_groupid);
        sql_query.bindValue(":memo",enrollInfoList.at(i)->m_memo);
        sql_query.bindValue(":pupilrow",enrollInfoList.at(i)->m_pupilrow);
        sql_query.bindValue(":pupilcol",enrollInfoList.at(i)->m_pupilcol);
        sql_query.bindValue(":pupilradius",enrollInfoList.at(i)->m_pupilradius);
        sql_query.bindValue(":irisrow",enrollInfoList.at(i)->m_irisrow);
        sql_query.bindValue(":iriscol",enrollInfoList.at(i)->m_iriscol);
        sql_query.bindValue(":irisradius",enrollInfoList.at(i)->m_irisradius);
        sql_query.bindValue(":focusscore",enrollInfoList.at(i)->m_focusscore);
        sql_query.bindValue(":percentvisible",enrollInfoList.at(i)->m_percentvisible);
        sql_query.bindValue(":spoofvalue",enrollInfoList.at(i)->m_spoofvalue);
        sql_query.bindValue(":interlacevalue",enrollInfoList.at(i)->m_interlacevalue);
        sql_query.bindValue(":qualitylevel",enrollInfoList.at(i)->m_qualitylevel);
        sql_query.bindValue(":qualityscore",enrollInfoList.at(i)->m_qualityscore);

        if(!sql_query.exec()) //查看插入是否成功
        {
            dumpError(sql_query, __FUNCTION__, sql_query.lastQuery());
            return E_MSQL_IRISALGO_INSERT_INSERT_ERROR;
        }
    }

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:根据personid列表，获取虹膜注册参数列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:OUT enrollInfoList 虹膜注册参数列表
            IN  personidList  personid列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::getEnrollPara(QList<PIRISEnrPara>& enrollInfoList, QStringList personidList)
{
    if(database.isOpen())
    {
        enrollInfoList.clear();
        for(int i = 0;i < personidList.length();i++)
        {
            QSqlQuery sql_query;
            QString query_data = "SELECT * FROM irisalgo where personid = :personid"; //查询数据
            sql_query.prepare(query_data); //查询
            sql_query.bindValue(":personid",personidList.at(i));
            if(!sql_query.exec()) //为空
            {
                qDebug()<<QObject::tr("device table get record failed");
                qDebug()<<sql_query.lastError();
                return E_MSQL_IRISALGO_GET_SELECT_ERROR;
            }
            else
            {
                while(sql_query.next())
                {
                    QSqlRecord rec = sql_query.record();
                    PIRISEnrPara enrollInfo = new IRISEnrPara();
                    if(!rec.isEmpty())
                    {
                        enrollInfo->m_focusscore = rec.value("focusscore").toInt();
                        enrollInfo->m_interlacevalue = rec.value("interlacevalue").toInt();
                        enrollInfo->m_iriscol = rec.value("iriscol").toInt();
                        enrollInfo->m_irisdataid =  rec.value("irisdataid").toString();
                        enrollInfo->m_irisradius = rec.value("irisradius").toInt();
                        enrollInfo->m_irisrow = rec.value("irisrow").toInt();
                        enrollInfo->m_memo =  rec.value("memo").toString();
                        enrollInfo->m_percentvisible = rec.value("percentvisible").toInt();
                        enrollInfo->m_personid = rec.value("personid").toString();
                        enrollInfo->m_pupilcol = rec.value("pupilcol").toInt();
                        enrollInfo->m_pupilradius = rec.value("pupilradius").toInt();
                        enrollInfo->m_pupilrow = rec.value("pupilrow").toInt();
                        enrollInfo->m_qualitylevel = rec.value("qualitylevel").toInt();
                        enrollInfo->m_qualityscore = rec.value("qualityscore").toInt();
                        enrollInfo->m_regtime =  rec.value("regtime").toDateTime();
                        enrollInfo->m_spoofvalue = rec.value("spoofvalue").toInt();
                        enrollInfoList << enrollInfo;
                    }
                }
            }
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:根据personid列表，删除虹膜注册参数列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数: IN  personidList  personid列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::delEnrollPara(QStringList personidList)
{
    if(database.isOpen())
    {
        for(int i = 0; i < personidList.length();i++)
        {
            /*****   删除ID对应的用户数据  *****/
            QSqlQuery sql_query;
            QString query_data = "delete from irisalgo where personid = :personid"; //删除数据

            sql_query.prepare(query_data); //删除
            sql_query.bindValue(":personid", personidList.at(i));
            if(!sql_query.exec()) //查看删除是否成功
            {
                qDebug()<<QObject::tr("select failed");
                qDebug()<<sql_query.lastError();
                return E_MSQL_IRISALGO_DEL_DELETE_ERROR;
            }
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:根据人员信息列表，批量添加人员信息
 作      者:tangzhuan
 日      期:20171205
 修  改 人:yqhe
 修改内容:修改格式，避免过多的{}；增加事务；
                 修改查询人员是否存在的条件，只按照personid查询
                 如果人已存在，不做插入操作，继续进行其他人员的操作
 修改日期:20180209
 参      数:IN personInfoList 人员信息列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::addPersonInfos(const QList<PDBPersonInfo>& personInfoList)
{
    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    database.transaction();

    for(int i = 0;i < personInfoList.length();i++)
    {
        QSqlQuery sql_query;
        QString query_data = "SELECT count(*) FROM person WHERE personid = :personid"; //查询数据

        sql_query.prepare(query_data); //查询
        sql_query.bindValue(":personid",personInfoList.at(i)->m_personid);

        //查看当前ID是否存在记录
        if(!sql_query.exec())
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_PERSON_ADD_SELECT_ERROR;
        }

        sql_query.next();
        int value = sql_query.value(0).toInt();

        if (value!=0)
        {
            //  如果有这个人，则不需要添加，继续进行后面的操作
            // 输出进行提示
            qDebug() << "person " << personInfoList.at(i)->m_personid << " already exist, do not insert";
            continue;
        }

        /*****   如果不存在记录则插入  *****/
        QString insert_data = "INSERT INTO person (personid,name,id,superid,sex,cardid, vcardid, idcard,memo,profession,hasirisdata,\
                address,password,updatetime)\
                VALUES (:personid,:name,:id,:superid,:sex,:cardid,:vcardid, :idcard,:memo,:profession,:hasirisdata,\
                        :address,:password,:updatetime)";

                sql_query.prepare(insert_data); //插入

        sql_query.bindValue(":personid",personInfoList.at(i)->m_personid);
        sql_query.bindValue(":name",personInfoList.at(i)->m_name);
        sql_query.bindValue(":id",personInfoList.at(i)->m_id);
        sql_query.bindValue(":superid",personInfoList.at(i)->m_superid);
        sql_query.bindValue(":sex",personInfoList.at(i)->m_sex);
        sql_query.bindValue(":cardid",personInfoList.at(i)->m_cardid);
        sql_query.bindValue(":vcardid",personInfoList.at(i)->m_vcardid);
        sql_query.bindValue(":idcard",personInfoList.at(i)->m_idcard);
        sql_query.bindValue(":memo",personInfoList.at(i)->m_memo);
        sql_query.bindValue(":profession",personInfoList.at(i)->m_profession);
        sql_query.bindValue(":hasirisdata",personInfoList.at(i)->m_hasirisdata);
        sql_query.bindValue(":address",personInfoList.at(i)->m_address);
        sql_query.bindValue(":password",personInfoList.at(i)->m_password);
        sql_query.bindValue(":updatetime", QDateTime::currentDateTime());

        if(!sql_query.exec()) //查看插入是否成功
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_PERSON_ADD_INSERT_ERROR;
        }
    }

    database.commit();

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:根据人员信息列表，批量修改人员信息
 作      者:tangzhuan
 日      期:20171205
 修  改 人:yqhe
 修改内容:修改格式，避免过多的{}；增加事务；
                 更新时间在函数中获取当前时间并设置，不使用参数中的时间
                 如果人不存在，不做修改操作，继续进行其他人员的操作
 修改日期:20180209
 修改人：yqhe
 修改内容： 增加虚拟卡号
 修改日期：20180301
 参      数:IN personInfoList 人员信息列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::updatePersonInfos(const QList<PDBPersonInfo>& personInfoList)
{
    if(!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    database.transaction();

    for(int i = 0;i < personInfoList.length();i++)
    {
        QSqlQuery sql_query;
        QString query_data = "SELECT count(*) FROM person WHERE personid = :personid"; //查询数据

        sql_query.prepare(query_data); //查询
        sql_query.bindValue(":personid",personInfoList.at(i)->m_personid);

        //查看当前ID是否存在记录
        if(!sql_query.exec())
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_PERSON_UPDATE_SELECT_ERROR;
        }

            sql_query.next();
            int value = sql_query.value(0).toInt();

            if (value==0)
            {
                //  如果没有这个人，则不需要更新，继续进行后面的操作
                // 输出进行提示
                qDebug() << "person " << personInfoList.at(i)->m_personid << " do not exist, do not update";
                continue;
            }

            /*****   如果存在记录则更新  *****/
            QString insert_data = "UPDATE person SET personid = :personid,name = :name,id = :id,superid = :superid,sex = :sex,\
                    cardid = :cardid,vcardid=:vcardid, idcard = :idcard,memo = :memo,profession = :profession,\
                    hasirisdata = :hasirisdata,address = :address,password = :password,updatetime = :updatetime \
                   WHERE personid = :personid";
                    sql_query.prepare(insert_data); //更新
            sql_query.bindValue(":personid",personInfoList.at(i)->m_personid);
            sql_query.bindValue(":name",personInfoList.at(i)->m_name);
            sql_query.bindValue(":id",personInfoList.at(i)->m_id);
            sql_query.bindValue(":superid",personInfoList.at(i)->m_superid);
            sql_query.bindValue(":sex",personInfoList.at(i)->m_sex);
            sql_query.bindValue(":cardid",personInfoList.at(i)->m_cardid);
            sql_query.bindValue(":vcardid",personInfoList.at(i)->m_vcardid);
            sql_query.bindValue(":idcard",personInfoList.at(i)->m_idcard);
            sql_query.bindValue(":memo",personInfoList.at(i)->m_memo);
            sql_query.bindValue(":profession",personInfoList.at(i)->m_profession);
            sql_query.bindValue(":hasirisdata",personInfoList.at(i)->m_hasirisdata);
            sql_query.bindValue(":address",personInfoList.at(i)->m_address);
            sql_query.bindValue(":password",personInfoList.at(i)->m_password);
            // sql_query.bindValue(":updatetime",personInfoList.at(i)->m_updatetime);
            sql_query.bindValue(":updatetime", QDateTime::currentDateTime());

            if(!sql_query.exec()) //查看更新是否成功
            {
                //std::cout<<"add record success!"<<std::endl;
                dumpError(sql_query, __FUNCTION__);
                return E_MSQL_PERSON_UPDATE_UPDATE_ERROR;
            }

    }

    database.commit();

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:根据人员信息列表，添加人员信息
 作      者:yqhe
 日      期:20180224
 修  改 人:
 修改内容:
 修改日期:
 参      数:IN personInfo 人员信息
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::addPersonInfo(const PDBPersonInfo personInfo)
{
    QList<PDBPersonInfo> personInfoList;
    personInfoList.push_back(personInfo);

    int ret = addPersonInfos(personInfoList);

    return ret;
}

/*********************************
 功      能:根据人员信息列表，修改人员信息
 作      者:yqhe
 日      期:20180224
 修  改 人:
 修改内容:
 修改日期:
 参      数:IN personInfo 人员信息
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::updatePersonInfo(const PDBPersonInfo personInfo)
{
    QList<PDBPersonInfo> personInfoList;
    personInfoList.push_back(personInfo);

    int ret = updatePersonInfos(personInfoList);

    return ret;
}

/*********************************
 功      能:根据用户id列表，获取人员信息列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:yqhe
 修改内容:修改格式，避免过多的{}；
                 修改输出参数为QMap格式，便于从结果中查找哪些人有结果

 修改日期:20180209
 参      数:OUT personInfoList 人员信息列表
            in   idList       用户id列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::getPersonInfo(QMap<QString, DBPersonInfo>& personInfoMap, const QStringList& idList)
{
    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    personInfoMap.clear();

    for(int i = 0; i < idList.length();i++)
    {
        QSqlQuery sql_query;
        QString query_data = "SELECT * FROM person where id = :id"; //查询数据

        sql_query.prepare(query_data); //查询
        sql_query.bindValue(":id", idList.at(i));

        if(!sql_query.exec()) //查看查询是否成功
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_PERSON_GET_SELECT_ERROR;
        }

        if (sql_query.next())
        {
            DBPersonInfo personInfo;
            int nret = recordGetPersonInfo(sql_query, personInfo);
            if (nret==E_MSQL_SUCCESS)
            {
                personInfoMap.insert(idList.at(i), personInfo);
            }

        }
    }

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:根据用户id列表，删除人员信息列表
 作      者:tangzhuan
 日      期:20171205
 修改内容:修改格式，避免过多的{}；

 修改日期:20180210
 参      数: in   idList       用户id列表
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::delPersonInfo(const QStringList& idList)
{    
    if(!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    for(int i = 0; i < idList.length();i++)
    {
        /*****   删除ID对应的用户数据  *****/
        QSqlQuery sql_query;
        QString query_data = "delete from person where id = :id"; //删除数据

        sql_query.prepare(query_data); //删除
        sql_query.bindValue(":id", idList.at(i));
        if(!sql_query.exec()) //查看删除是否成功
        {
            dumpError(sql_query, __FUNCTION__);
            return E_MSQL_PERSON_DEL_DELETE_ERROR;
        }
    }

    return E_MSQL_SUCCESS;
}

/*********************************
 功      能:获取所有的用户id和用户名
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:OUT mapList <用户id列表,用户名列表>
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::getAllID(QMap<QString, QString>& mapList)
{
    if(database.isOpen())
    {
//        idList.clear();
//        nameList.clear();

        QSqlQuery sql_query;
        QString query_data = "select id,name from person order by id"; //查询数据

        sql_query.prepare(query_data); //查询
        if(!sql_query.exec()) //查看查询是否成功
        {
            qDebug()<<QObject::tr("select failed");
            qDebug()<<sql_query.lastError();
            return E_MSQL_PERSON_GETALLID_SELECT_ERROR;
        }
        else
        {
            //循环提起ID和用户名
            while(sql_query.next())
            {
                QString id,name;
                QSqlRecord rec = sql_query.record();
                if(!rec.isEmpty())
                {
                    id = rec.value("id").toString();
                    name = rec.value("name").toString();
                    mapList[id] = name;
                }
                else
                {
                    qDebug()<<sql_query.lastError();
                    return E_MSQL_PERSON_GETALLID_NULL_ERROR;
                }
            }
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:添加人员识别记录列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:IN recLog 人员识别记录类
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::addRecLog(PRecLog recLog)
{
    if(database.isOpen())
    {
        QSqlQuery sql_query;
//        QString insert_data = "INSERT INTO reclog (reclogid,personid,irisdataid,recogtime,recogtype,devsn,memo)\
//                VALUES (:reclogid,:personid,:irisdataid,:recogtime,:recogtype,:devsn,:memo)";
                QString insert_data = "INSERT INTO reclog (personid,irisdataid,recogtime,recogtype,devsn,memo)\
                        VALUES (:personid,:irisdataid,:recogtime,:recogtype,:devsn,:memo)";
                sql_query.prepare(insert_data); //插入

        // sql_query.bindValue(":reclogid",recLog->m_reclogid);
        sql_query.bindValue(":personid",recLog->m_personid);
        sql_query.bindValue(":irisdataid",recLog->m_irisdataid);
        sql_query.bindValue(":recogtime",recLog->m_recogtime);
        sql_query.bindValue(":recogtype",recLog->m_recogtype);
        sql_query.bindValue(":devsn",recLog->m_devsn);
        sql_query.bindValue(":memo",recLog->m_memo);
        if(!sql_query.exec()) //查看插入是否成功
        {
            //std::cout<<"add record success!"<<std::endl;
            return E_MSQL_RECLOG_ADD_INSERT_ERROR;
        }

    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:根据personid删除人员识别记录列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数: IN  personid   person表中的uuid
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::delRecLogForPersonid(QString personid)
{
    if(database.isOpen())
    {
        /*****   删除ID对应的用户数据  *****/
        QSqlQuery sql_query;
        QString query_data = "delete from reclog where personid = :personid"; //删除数据

        sql_query.prepare(query_data); //删除
        sql_query.bindValue(":personid", personid);
        if(!sql_query.exec()) //查看删除是否成功
        {
            qDebug()<<QObject::tr("select failed");
            qDebug()<<sql_query.lastError();
            return E_MSQL_RECLOG_DELFORID_DELETE_ERROR;
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:根据起始时间和终止时间删除人员识别记录列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数: IN startTime    起始时间
            IN endTime     终止时间
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::delRecLogForTime(QDateTime startTime,QDateTime endTime)
{
    if(database.isOpen())
    {
        /*****   删除ID对应的用户数据  *****/
        QSqlQuery sql_query;
        QString query_data;
        query_data = "delete from reclog where recogtime => startTime = :startTime and  recogtime <= endTime = :endTime";
        sql_query.prepare(query_data); //删除
        sql_query.bindValue(":startTime", startTime);
        sql_query.bindValue(":endTime", endTime);

        if(!sql_query.exec()) //查看删除是否成功
        {
            qDebug()<<QObject::tr("select failed");
            qDebug()<<sql_query.lastError();
            return E_MSQL_RECLOG_DELFORTIME_DELETE_ERROR;
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:根据personid返回人员识别记录列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数:OUT recLogList 人员识别记录列表
            IN  personid   person表中的uuid
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::getRecLogForPersonid(QList<PRecLog> &recLogList, QString personid)
{
    if(database.isOpen())
    {
        QSqlQuery sql_query;
        QString query_data = "SELECT * FROM reclog where personid = :personid"; //查询数据
        sql_query.prepare(query_data); //查询
        sql_query.bindValue(":personid",personid);
        if(!sql_query.exec()) //为空
        {
            qDebug()<<QObject::tr("device table get record failed");
            qDebug()<<sql_query.lastError();
            return E_MSQL_RECLOG_GETFORID_SELECT_ERROR;
        }
        else
        {
            recLogList.clear();

            while(sql_query.next())
            {
                QSqlRecord rec = sql_query.record();
                if(!rec.isEmpty())
                {
                    PRecLog recLog = new RecLog();
                    recLog->m_devsn = rec.value("devsn").toString();
                    recLog->m_irisdataid = rec.value("irisdataid").toString();
                    recLog->m_memo = rec.value("memo").toString();
                    recLog->m_personid = rec.value("personid").toString();
                    recLog->m_reclogid = rec.value("reclogid").toInt();
                    recLog->m_recogtime = rec.value("recogtime").toDateTime();
                    recLog->m_recogtype = rec.value("recogtype").toInt();
                    recLogList << recLog;
                }
            }
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

/*********************************
 功      能:根据起始时间和终止时间返回人员识别记录列表
 作      者:tangzhuan
 日      期:20171205
 修  改 人:
 修改内容:
 修改日期:
 参      数: OUT recLogList 人员识别记录列表
            IN startTime    起始时间
            IN endTime     终止时间
 返  回 值:成功返回0,失败返回错误码
**********************************/
int msqldatabase::getRecLogForTime(QList<PRecLog> &recLogList,QDateTime startTime,QDateTime endTime)
{
    if(database.isOpen())
    {
        QSqlQuery sql_query;
        QString query_data;
        query_data = "SELECT * FROM reclog where recogtime => startTime = :startTime and  recogtime <= endTime = :endTime";
        sql_query.prepare(query_data); //查询
        sql_query.bindValue(":startTime", startTime);
        sql_query.bindValue(":endTime", endTime);

        if(!sql_query.exec()) //为空
        {
            qDebug()<<QObject::tr("device table get record failed");
            qDebug()<<sql_query.lastError();
            return E_MSQL_RECLOG_GETFORTIME_SELECT_ERROR;
        }
        else
        {
            recLogList.clear();

            while(sql_query.next())
            {
                QSqlRecord rec = sql_query.record();
                if(!rec.isEmpty())
                {
                    PRecLog recLog = new RecLog();
                    recLog->m_devsn = rec.value("devsn").toString();
                    recLog->m_irisdataid = rec.value("irisdataid").toString();
                    recLog->m_memo = rec.value("memo").toString();
                    recLog->m_personid = rec.value("personid").toString();
                    recLog->m_reclogid = rec.value("reclogid").toInt();
                    recLog->m_recogtime = rec.value("recogtime").toDateTime();
                    recLog->m_recogtype = rec.value("recogtype").toInt();
                    recLogList << recLog;
                }
            }
        }
    }
    else
    {
        return E_MSQL_OPEN_ERROR;
    }
    return 0;
}

// added at 20180209 by yqhe，所以添加或者更新人员信息的时候，还需要查询卡号是否重复
// 一种是根据卡号没有查到任何人(E_MSQL_PERSON_GETPERSON_NULL_ERROR)，则肯定不重复
// 一种是根据卡号查到人了(E_MSQL_SUCCESS)，但是这个人就是他自己，这样也不是重复
// 通过cardid查询人员信息
// 只有当返回值为E_MSQL_SUCCESS时，PersonInfo中的值才可用
// modified at 20180301 by yqhe
// 这个cardid可以是实体卡号，也可以是虚拟卡号，任何一个查到都可以
int msqldatabase::getPersonByCard(QString cardid, DBPersonInfo& personInfo)
{
    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    QSqlQuery sql_query;
    QString query_data;
    query_data = "SELECT * FROM person where cardid=:cardid OR vcardid=:cardid";
    sql_query.prepare(query_data); //查询
    sql_query.bindValue(":cardid", cardid);

    if (!sql_query.exec()) //为空
    {
        qDebug() << __FUNCTION__ <<sql_query.lastError();
        return E_MSQL_PERSON_GETPERSON_SELECT_ERROR;
    }

    // 只取一条数据，如果有多的也不要
    int nret = E_MSQL_PERSON_GETPERSON_NULL_ERROR;

    if (sql_query.next())
    {
        nret = recordGetPersonInfo(sql_query, personInfo);

        if (nret!=E_MSQL_SUCCESS)
        {
            nret = E_MSQL_PERSON_GETPERSON_NULL_ERROR;
        }
    }

    return nret;

}

// added at 20180209 by yqhe
// 从查询结果填充人员信息
// 返回值：E_MSQL_SUCCESS成功，数据可用；E_MSQL_RECORD_NULL_ERROR没有查询到结果
// modified at 20180301 by yqhe, 增加虚拟卡号
int msqldatabase::recordGetPersonInfo(QSqlQuery& sql_query, DBPersonInfo& personInfo)
{
    QSqlRecord rec = sql_query.record();

    if (rec.isEmpty())
    {
        return E_MSQL_RECORD_NULL_ERROR;
    }

    personInfo.m_personid = rec.value("personid").toString();
    personInfo.m_name =  rec.value("name").toString();
    personInfo.m_id =  rec.value("id").toString();
    personInfo.m_superid = rec.value("superid").toBool();
    personInfo.m_sex = rec.value("sex").toString();

    personInfo.m_cardid = rec.value("cardid").toString();
    personInfo.m_vcardid = rec.value("vcardid").toString();
    personInfo.m_idcard = rec.value("idcard").toString();
    personInfo.m_memo = rec.value("memo").toString();
    personInfo.m_profession = rec.value("profession").toString();
    personInfo.m_hasirisdata = rec.value("hasirisdata").toBool();

    personInfo.m_address = rec.value("address").toString();
    personInfo.m_password = rec.value("password").toString();

    personInfo.m_createtime = rec.value("createtime").toDateTime();
    personInfo.m_updatetime = rec.value("updatetime").toDateTime();

    return E_MSQL_SUCCESS;

}

//  查询数据库中当前是否存在管理员
int msqldatabase::isSuperExist(bool& hasSuper)
{
    if (!database.isOpen())
    {
        return E_MSQL_OPEN_ERROR;
    }

    QSqlQuery sql_query;
    QString query_data;
    query_data = "SELECT count(*) FROM person where superid=1";
    sql_query.prepare(query_data); //查询

    if (!sql_query.exec()) //查询失败
    {
        qDebug() << __FUNCTION__ <<sql_query.lastError();
        return E_MSQL_PERSON_HASSUPTER_SELECT_ERROR;
    }

    if (!sql_query.next())
    {
        dumpError(sql_query, __FUNCTION__);
        return E_MSQL_PERSON_HASSUPTER_SELECT_ERROR;
    }

    int value = sql_query.value(0).toInt();

    if (value==0)
    {
        hasSuper = false;
    }
    else
    {
        hasSuper = true;
    }

    return E_MSQL_SUCCESS;
}

// 统一错误输出方式，并回滚
// 输入参数：
// sqlQuery -- QSqlQuery查询
// function -- 调用的函数名
// sqlString -- 查询语句，缺省为空，如果为空，则不输出查询语句
void msqldatabase::dumpError(const QSqlQuery& sqlQuery, const QString& function, const QString& sqlString)
{
    if (!sqlString.isEmpty())
    {
        qDebug() << "[" << function << "] QueryString : " << sqlString;
    }

    qDebug() << "[" << function << "] SqlError : " << sqlQuery.lastError();
}
