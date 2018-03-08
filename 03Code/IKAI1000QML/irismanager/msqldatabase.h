/*************************************************
Copyright: 中科虹霸
作者: tangzhuan
日期: 20171205
描述:数据库访问类 采用单例模式
**************************************************/
#ifndef MSQLDATABASE_H
#define MSQLDATABASE_H

#include <unordered_map>
#include <QTime>
#include <QSqlDatabase>
#include<QMap>

class QStringList;
class QString;
class QDateTime;

// modified at 20180208 by yqhe
// 定义特征长度、图像大小
// 为与IKUSBSDK.h中的定义相区别，暂时在原定义的基础上，前缀修改为IK1000_
const int IK1000_ENROLL_FEATURE_SIZE = 1000;
const int IK1000_IDEN_FEATURE_SIZE = 1536;
const int IK1000_BMP_HEAD_SIZE = 1080;

//虹膜图像尺寸大小
const int IK1000_IRIS_IMG_HEIGHT = 480;
const int IK1000_IRIS_IMG_WIDTH = 640;
const int IK1000_IRIS_IMG_SIZE = (IK1000_IRIS_IMG_HEIGHT * IK1000_IRIS_IMG_WIDTH);

// 左右眼标志
const int IK1000_LEFT_EYE = 1;
const int IK1000_RIGHT_EYE = 2;

//device数据结构体
typedef struct _DeviceInfo{
    int m_devid;            //整形
    QString m_devname;     //设备名称
    QString m_devsn;        //设备sn，由生产时确定
    QString m_devip;       //设备IP
    QString m_devmac;       //设备Mac
    QString m_devsubnet;     //设备子网掩码
    QString m_devserverip;    //设备连接服务器IP
    int m_devserverport;     //设备连接服务器端口号
    QString m_devplace;     //设备连接服务器端口号
    QString m_memo;

    _DeviceInfo()
    {
        m_devid = 1;
        m_devserverport = 0;
    }

}DeviceInfo,*PDeviceInfo;

//虹膜信息结构体
typedef struct _IRISUserInfo {
    QString                 m_irisdataid;                                                          //uuid,唯一识别号
    QString                 m_personid;                                                          //人员的uuid
    int                         m_groupid;                                                            // 虹膜组别，一个人最多4组数据，从1开始
    int                         m_iriscodelen;
    unsigned char      m_iriscode[IK1000_ENROLL_FEATURE_SIZE];    //虹膜特征,512字节或1024字节
    int                          m_eyepiclen;
    unsigned char      m_eyepic[IK1000_IRIS_IMG_SIZE];                     //人眼的虹膜图像
    int                         m_matchiriscodelen;
    unsigned char      m_matchiriscode[IK1000_IDEN_FEATURE_SIZE];    //虹膜比对特征
    QString                 m_devsn;                                                            //设备sn，由生产时确定
    int                         m_eyeflag;                                                          //左右眼标志，左眼1，右眼2
    QDateTime           m_regtime;                                                         //注册时的设备时间,对于同一个人的不同特征都是相同的

    _IRISUserInfo()
    {
        m_groupid = 1;
        m_iriscodelen = 0;
        m_eyepiclen = 0;
        m_matchiriscodelen = 0;
        m_eyeflag = IK1000_LEFT_EYE;
    }

}IRISUserInfo, *PIRISUserInfo;

//irisalgo数据结构体
typedef struct _IRISEnrPara {
    QString m_irisdataid;                 //uuid，唯一识别号
    QString m_personid;                 //人员的uuid
    QDateTime m_regtime;            //注册时的设备时间,对于同一个人的不同特征都是相同的
    int         m_eyeflag;
    int         m_groupid;                  // 虹膜组别，一个人最多4组数据，从1开始
    QString m_memo;                    //
    int m_pupilrow;                 //瞳孔行
    int m_pupilcol;                 //瞳孔列
    int m_pupilradius;           //瞳孔半径QString m_personid;
    int m_irisrow;                  //虹膜行
    int m_iriscol;                   //虹膜列
    int m_irisradius;             //虹膜半径
    int m_focusscore;          //焦点分数
    int m_percentvisible;     //可见百分比
    int m_spoofvalue;          //
    int m_interlacevalue;    //交错值
    int m_qualitylevel;         //质量水平
    int m_qualityscore;        //质量分数QString m_personid;

    _IRISEnrPara()
    {
        m_eyeflag = 0;
        m_groupid=0;

        m_pupilrow = 0;
        m_pupilcol = 0;
        m_pupilradius = 0;

        m_irisrow = 0;
        m_iriscol = 0;
        m_irisradius = 0;

        m_focusscore = 0;
        m_percentvisible = 0;
        m_spoofvalue = 0;
        m_interlacevalue = 0;

        m_qualitylevel = 0;
        m_qualityscore = 0;
    }

}IRISEnrPara,*PIRISEnrPara;

// 人员虹膜信息的视图数据结构体－－可根据实际情况进行增删
// 用于虹膜特征转载，包括注册虹膜特征和部分人员信息
typedef struct __ViewPersonIris
{
    QString m_personid;
    QString m_userid;
    QString m_name;
    QString m_sex;
    QString m_cardid;
    bool m_superid;      //是否是管理员: 0不是，1是

    QString m_irisdataid;
    unsigned char m_iriscode[IK1000_ENROLL_FEATURE_SIZE];    //虹膜特征,512字节或1024字节
    int m_eyeflag;


    __ViewPersonIris()
    {
        m_eyeflag = IK1000_LEFT_EYE;
    }
}ViewPersonIris,*PViewPersonIris;

//person数据结构体
typedef struct _DBPersonInfo {
    QString m_personid; //uuid标识人员的唯一性
    QString m_name;     //姓名,用户名
    QString m_id;       //用户id，唯一
    bool m_superid;      //是否是管理员: 0不是，1是
    QString m_sex;      //性别
    QString m_cardid;   //卡号字段，此字段前面补0，凑齐8位
    QString m_vcardid;   //虚拟卡号字段，此字段前面补0，凑齐8位, added at 20180301 by yqhe
    QString m_idcard;   //身份证号码
    QString m_memo;     //
    QString m_profession;   //职业
    bool m_hasirisdata;      //是否有虹膜数据：1--有,0—没有
    QString m_address;      //常用住址
    QString m_password;     //用户密码，经过MD5变换后的密码字符串，只有superid为1（表示是管理员）才可以设置密码
    QDateTime m_createtime;     // 创建时间，写入数据库时不需要，读出人员数据的时候会填写
    QDateTime m_updatetime;     // 更新时间，写入数据库时不需要，读出人员数据的时候会填写

    _DBPersonInfo()
    {
        m_superid = false;
        m_hasirisdata = false;
    }
}DBPersonInfo,*PDBPersonInfo;

//reclog数据结构体
typedef struct _RecLog {
    int m_reclogid;         //Integer
    QString m_personid;     //人员表的uuid
    QString m_irisdataid;      //虹膜表uuid
    QDateTime m_recogtime;  //识别时间
    int m_recogtype;        //识别类别，人脸、虹膜、卡号
    QString m_devsn;        //设备sn，由生产时确定
    QString m_memo;         //
}RecLog,*PRecLog;

//函数调用错误码
const int E_MSQL_ERROR_BASE = 0;     //基础错误码
const int E_MSQL_SUCCESS = 0;     //基础错误码

//与open函数相关的错误码,以1**开头
const int E_MSQL_OPEN_ERROR = E_MSQL_ERROR_BASE - 100;//数据库打开失败
const int E_MSQL_OPEN_DEVICE_ERROR = E_MSQL_ERROR_BASE - 110;//device数据表创建失败
const int E_MSQL_OPEN_IRISDATABASE_ERROR = E_MSQL_ERROR_BASE - 120;//irisdatabase数据表创建失败
const int E_MSQL_OPEN_IRISALGO_ERROR = E_MSQL_ERROR_BASE - 130;//irisalgo数据表创建失败
const int E_MSQL_OPEN_PERSON_ERROR = E_MSQL_ERROR_BASE - 140;//person数据表创建失败
const int E_MSQL_OPEN_RECLOG_ERROR = E_MSQL_ERROR_BASE - 150;//reclog数据表创建失败


//与device数据表函数相关的错误码,以2**开头
const int E_MSQL_DEVICE_SET_SELECT_ERROR = E_MSQL_ERROR_BASE - 210;//setDeviceInfo函数 SELECT操作失败
const int E_MSQL_DEVICE_SET_INSERT_ERROR = E_MSQL_ERROR_BASE - 220;//setDeviceInfo函数 INSERT操作失败
const int E_MSQL_DEVICE_SET_UPDATE_ERROR = E_MSQL_ERROR_BASE - 230;//setDeviceInfo函数 UPDATE操作失败
const int E_MSQL_DEVICE_GET_SELECT_ERROR = E_MSQL_ERROR_BASE - 240;//getDeviceInfo函数 SELECT操作失败
const int E_MSQL_DEVICE_GET_NULL_ERROR = E_MSQL_ERROR_BASE - 250;//getDeviceInfo函数 数据库中没有设备信息

//与irisdatabase数据表函数相关的错误码,以3**开头
const int E_MSQL_IRISDATABASE_INSERT_SELECT_ERROR = E_MSQL_ERROR_BASE - 310;//insertIrisInfo函数 SELECT操作失败
const int E_MSQL_IRISDATABASE_INSERT_DATABEING_INSERT_ERROR = E_MSQL_ERROR_BASE - 320;//insertIrisInfo函数 数据存在 INSERT操作失败
const int E_MSQL_IRISDATABASE_INSERT_INSERT_ERROR = E_MSQL_ERROR_BASE - 330;//insertIrisInfo函数 INSERT操作失败
const int E_MSQL_IRISDATABASE_GET_SELECT_ERROR = E_MSQL_ERROR_BASE - 340;//getIrisInfo函数 SELECT操作失败
const int E_MSQL_IRISDATABASE_GET_NULL_ERROR = E_MSQL_ERROR_BASE - 350;//getIrisInfo函数 数据库中没有对应信息
const int E_MSQL_IRISDATABASE_DELPID_DELETE_ERROR = E_MSQL_ERROR_BASE - 360;//delIrisInforForPersonid函数 DELETE操作失败
const int E_MSQL_IRISDATABASE_DELIRISID_DELETE_ERROR = E_MSQL_ERROR_BASE - 370;//delIrisInforForIrisdataid函数 DELETE操作失败

//与irisalgo数据表函数相关的错误码,以4**开头
const int E_MSQL_IRISALGO_INSERT_SELECT_ERROR = E_MSQL_ERROR_BASE - 410;//insertEnrollPara函数 SELECT操作失败
const int E_MSQL_IRISALGO_INSERT_DATABEING_INSERT_ERROR = E_MSQL_ERROR_BASE - 420;//insertEnrollPara函数 数据存在 INSERT操作失败
const int E_MSQL_IRISALGO_INSERT_INSERT_ERROR = E_MSQL_ERROR_BASE - 430;//insertEnrollPara函数 INSERT操作失败
const int E_MSQL_IRISALGO_GET_SELECT_ERROR = E_MSQL_ERROR_BASE - 440;//getEnrollPara函数 SELECT操作失败
const int E_MSQL_IRISALGO_DEL_DELETE_ERROR = E_MSQL_ERROR_BASE - 450;//delEnrollPara函数 DELETE操作失败

//与person数据表函数相关的错误码,以5**开头
const int E_MSQL_PERSON_ADD_SELECT_ERROR = E_MSQL_ERROR_BASE - 510;//addPersonInfo函数 SELECT操作失败
const int E_MSQL_PERSON_ADD_DATABEING_INSERT_ERROR = E_MSQL_ERROR_BASE - 520;//addPersonInfo函数 数据存在 INSERT操作失败
const int E_MSQL_PERSON_ADD_INSERT_ERROR = E_MSQL_ERROR_BASE - 530;//addPersonInfo函数 INSERT操作失败
const int E_MSQL_PERSON_UPDATE_SELECT_ERROR = E_MSQL_ERROR_BASE - 540;//updatePersonInfo函数 SELECT操作失败
const int E_MSQL_PERSON_UPDATE_DATANOTBEING_UPDATE_ERROR = E_MSQL_ERROR_BASE - 550;//updatePersonInfo函数 数据不存在 UPDATE操作失败
const int E_MSQL_PERSON_UPDATE_UPDATE_ERROR = E_MSQL_ERROR_BASE - 560;//updatePersonInfo函数 UPDATE操作失败
const int E_MSQL_PERSON_GET_SELECT_ERROR = E_MSQL_ERROR_BASE - 570;//getPersonInfo函数 SELECT操作失败
const int E_MSQL_PERSON_DEL_DELETE_ERROR = E_MSQL_ERROR_BASE - 580;//delPersonInfo函数 DELETE操作失败
const int E_MSQL_PERSON_GETALLID_SELECT_ERROR = E_MSQL_ERROR_BASE - 590;//getAllID函数 SELECT操作失败
const int E_MSQL_PERSON_GETALLID_NULL_ERROR = E_MSQL_ERROR_BASE - 500;//getAllID函数 SELECT操作 NULL
const int E_MSQL_PERSON_GETPERSON_SELECT_ERROR = E_MSQL_ERROR_BASE - 501;//getPerson函数 SELECT操作失败
const int E_MSQL_PERSON_GETPERSON_NULL_ERROR = E_MSQL_ERROR_BASE - 502; //getPerson函数未查到相应人员
const int E_MSQL_PERSON_HASSUPTER_SELECT_ERROR = E_MSQL_ERROR_BASE - 503;//isSuperExist SELECT操作失败

//与reclog数据表函数相关的错误码,以6**开头
const int E_MSQL_RECLOG_ADD_INSERT_ERROR = E_MSQL_ERROR_BASE - 610;//addRecLog函数 INSERT操作失败
const int E_MSQL_RECLOG_DELFORID_DELETE_ERROR = E_MSQL_ERROR_BASE - 620;//delRecLogForPersonid函数 DELETE操作失败
const int E_MSQL_RECLOG_DELFORTIME_DELETE_ERROR = E_MSQL_ERROR_BASE - 630;//delRecLogForTime函数 DELETE操作失败
const int E_MSQL_RECLOG_GETFORID_SELECT_ERROR = E_MSQL_ERROR_BASE - 640;//getRecLogForPersonid函数 SELECT操作失败
const int E_MSQL_RECLOG_GETFORTIME_SELECT_ERROR = E_MSQL_ERROR_BASE - 650;//getRecLogForTime函数 SELECT操作失败


// 对数据库操作的总的错误，以-10**开头，例如没有任何记录的返回码
const int E_MSQL_RECORD_NULL_ERROR =  E_MSQL_ERROR_BASE -1001; //未查到相应记录
const int E_MSQL_RECORD_EXIST_ERROR =  E_MSQL_ERROR_BASE -1002; //数据已存在
const int E_MSQL_FORMAT_ERROR =  E_MSQL_ERROR_BASE -1003;           //数据格式错误
const int E_MSQL_ACCESS_ERROR =  E_MSQL_ERROR_BASE -1004;           //数据库访问错误
const int E_MSQL_MASTER_SELECT_ERROR =  E_MSQL_ERROR_BASE -1005;  //查询sqlite_master表出错

class msqldatabase
{
private:
    msqldatabase();    
public:
    static msqldatabase* get_Instance();//单例模式

    static void Release();//释放数据库对象
    int open();//打开数据库，并判断数据库表的完整性
    void close();//关闭数据库

    //device数据表：
    int setDeviceInfo(PDeviceInfo deviceInfo);//设置设备自身硬件信息
    int getDeviceInfo(PDeviceInfo deviceInfo);//获取设备自身硬件信息

    //irisdatabase数据表：    
    int insertIrisInfos(QList<PIRISUserInfo>& infoList);//插入虹膜信息
    int getIrisInfo(QList<PIRISUserInfo>& userInfoList,QStringList personidList);//获取虹膜信息
    int delIrisInforForPersonid(QStringList personidList);//根据personidList删除虹膜信息
    int delIrisInforForIrisdataid(QStringList irisdataidList);//根据irisdataidList删除虹膜信息
    int getIrisTotalNum(); // 获取所有虹膜特征条数
    int getPersonIrisInfo(QList<ViewPersonIris>& irisInfoList, int offset, int limit=2000); // 按顺序获取部分虹膜特征

    //irisalgo数据表:
    int insertEnrollParas(QList<PIRISEnrPara>& enrollInfoList);//插入虹膜注册参数
    int getEnrollPara(QList<PIRISEnrPara>& enrollInfoList,QStringList personidList);//获取虹膜注册参数
    int delEnrollPara(QStringList personidList);//删除虹膜注册参数

    //person数据表:
    int addPersonInfos(const QList<PDBPersonInfo>& personInfoList);//批量添加用户信息
    int updatePersonInfos(const QList<PDBPersonInfo>& personInfoList);//批量修改用户信息
    int getPersonInfo(QMap<QString, DBPersonInfo>& personInfoMap, const QStringList& idList);//获取用户信息
    int delPersonInfo(const QStringList& idList);//删除用户信息
    int getAllID(QMap<QString,QString>& mapList);//获取所有<ID,用户名>

    // added at 20180209 by yqhe，所以添加或者更新人员信息的时候，还需要查询卡号是否重复
    int getPersonByCard(QString cardid, DBPersonInfo& personInfo);  // 通过cardid查询人员信息

    // added at 20180212 by yqhe，进入管理界面前，需要判断是否存在管理员
    int isSuperExist(bool& hasSuper);       //  查询数据库中当前是否存在管理员

    // added at 20180224 by yqhe，增加添加或修改单独某个用户的功能
    int addPersonInfo(const PDBPersonInfo personInfo);//添加用户信息
    int updatePersonInfo(const PDBPersonInfo personInfo);//修改用户信息

    //reclog数据表:
    int addRecLog(PRecLog recLog);//添加人员识别记录
    int delRecLogForPersonid(QString personid);//删除人员的识别记录
    int delRecLogForTime(QDateTime startTime = QDateTime::fromString("1970-01-01 00:00:00"),\
                           QDateTime endTime = QDateTime::currentDateTime());//start and end time 删除人员的识别记录
    int getRecLogForPersonid(QList<PRecLog> &recLogList ,QString personid);//获取人员的识别记录
    int getRecLogForTime(QList<PRecLog> &recLogList,\
                       QDateTime startTime = QDateTime::fromString("1970-01-01 00:00:00"),\
                       QDateTime endTime = QDateTime::currentDateTime());//start and end time 获取人员的识别记录

private:    
    QSqlDatabase database;//数据库对象
    static msqldatabase* m_baseInstance;

private:

    // added at 20180209 by yqhe
    // 从查询结果填充人员信息
    int recordGetPersonInfo(QSqlQuery& sql_query, DBPersonInfo& personInfo);

    // 统一错误输出方式，并回滚
    void dumpError(const QSqlQuery& sql_query, const QString& function, const QString& sqlString="");

    // 检查虹膜数据是否需要插入
   int checkIrisData(PIRISUserInfo irisInfo);

   int _001updateReclogAuto();   //  设置识别记录表的logid为自增长类型

};

#endif // MSQLDATABASE_H
