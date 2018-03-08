/******************************************************************************************
** 文件名:   IrisManager.h
×× 主要类:   IrisManager
**
** Copyright (c) 中科虹霸有限公司
** 创建人:   fjf
** 日  期:   2013-12-30
** 修改人:
** 日  期:
** 描  述: 虹膜特征管理类
** ×× 主要模块说明：
**
** 版  本:   1.0.0
** 备  注:
**
*****************************************************************************************/

#ifndef IRISMANAGER_H
#define IRISMANAGER_H

#include <QObject>
#include <QTimer>

#include <list>
#include <vector>
#include "irisData.h"
#include "msqldatabase.h"

// 特征管理线程的初始化参数
typedef struct __IrisManInitArgs
{
    bool loadLocal;     // 是否从本地加载
    int sendSigBlock;   // 加载多少条特征后发一次消息

    __IrisManInitArgs()
    {
        loadLocal = true;
        sendSigBlock = 256;
    }

}IrisManInitArgs, *PIrisManInitArgs;

//函数调用错误码
const int E_IRISMAN_ERROR_BASE = 0 - 0x1000;     //基础错误码
const int E_IRISMAN_SUCCESS = 0;     //基础错误码

const int E_IRISMAN_LOADING_NOW_ERROR = E_IRISMAN_ERROR_BASE - 0x1;
const int E_IRISMAN_INITARG_ERROR = E_IRISMAN_ERROR_BASE - 0x2;
const int E_IRISMAN_NOPERSON_ERROR = E_IRISMAN_ERROR_BASE - 0x3;
const int E_IRISMAN_DEL_FEATURE_ERROR = E_IRISMAN_ERROR_BASE - 0x4;

class IrisManager : public QObject
{
    Q_OBJECT
private:
    explicit IrisManager(QObject *parent = 0);
    ~IrisManager();

public:
    static IrisManager* get_instance();

    int initARG(const IrisManInitArgs& args);

    // 普通人员特征的加载
    //获取虹膜特征指针，分左右眼获取
    bool getIrisFeature(const EyeFlag& flag,unsigned char*&pIrisData,int &size);
    int loadData(void);                //显式从数据库中加载全部特征及相关数据
    int releaseData(void);          // 显式释放所有数据

   // 当前特征加载状态
    int  getLoadState(bool& loading, int& totalCount, int& leftCount, int& rightCount);

public:
    //特征的管理操作，增、删、改、查
    int deletePerson(const PeopleInfo &info);                   // 人员和特征全部删除
    int deleteFeatureData(const InfoData& info);              // 只删除特征，人员信息保留

    int addFeatureData(const InfoData& info);                 // 增加人员及特征，例如在本机注册时增加或从网络传来数据时增加
    int updatePersonInfo(const PeopleInfo& info);          // 修改人员信息，例如在本机修改人员信息或从网络床来数据时修改

public:
    int getPersonInfoByIndex(int index, PeopleInfo& info, const EyeFlag& type);      //根据特征序号获得人员信息
    bool getPersonInfoById(const std::string&  irisuuid, PeopleInfo& personinfo);                        // 通过虹膜id获得人员信息

private:
	//the first
    bool SetIrisFeature(const InfoData &id,EyeFlag flag, const unsigned char *pIrisData);   //单条注册特征写入并保存
	bool GetAlgorithm(void);

	//处理特征的合并、删除和修改
	bool FeatureDataDoWith();
	std::string GetStringFromChar(unsigned char* unc);                                          //UUID从数组到字符串

private:
	void LockData(void);                //显示的锁和解锁函数
	void UnlockData(void);
	void Init(void);

private:
	//数据库的操作管理----2014-2-13数据库的管理从数据层转移到管理层
	int ReadFeature();
	int UpdateFeature();
	int DeleteFeature();
	int SelectFeaure();
private:
	//替代MAP[]操作函数
	std::shared_ptr<PeopleNode> FindKeyPeople(std::string sKey);

private:
	IrisData _irisData;
    std::list<InfoData> _dataBuf;           //实时更新的数据进入到特征时的缓冲
	bool _isChange;                                 //是否有数据可以处理
	//处理两级映射
    PeopleMap _mapPeople;                 //人员ID和人员信息映射
    FeatureMap _mapFeature;               //人员特征ID和特征ID在内存中的索引映射表

private:
    // std::vector<ViewPersonIris> _vpData;    //从数据库加载的人员特征数据

    static IrisManager* m_irisManager;

    int m_totalLoadCount;   // 需要加载的总的特征条数
    int m_loadingCount; // 已加载的条数

    bool m_loadingNow;
    IrisManInitArgs m_irisManInitArgs;
    int m_loadBlock;  // 每次加载的条数，
                            // 如果这个数值大于m_irisManInitArgs中设置的发消息条数，则这个数值修改为m_irisManInitArgs中的值


signals:
    void loadFeatureResult(bool, int, int, int); //  是否正在加载；加载错误码，0为成功；总特征条数；已加载特征条数

public slots:

private slots:
    void slot_startLoad();

};

#endif
