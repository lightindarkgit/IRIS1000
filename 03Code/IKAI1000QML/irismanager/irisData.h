/******************************************************************************************
** 文件名:   irisData.h
×× 主要类:   IrisData
**
** Copyright (c) 中科虹霸有限公司
** 创建人:   fjf
** 日  期:   2013-01-06
** 修改人:
** 日  期:
** 描  述: 虹膜数据类
** ×× 主要模块说明：
**
** 版  本:   1.0.0
** 备  注:
**
*****************************************************************************************/
#pragma once
#include "../Common/common.h"
#include "featureCommon.h"
#include <mutex>

class IrisData
{
public:
	IrisData();
	virtual ~IrisData();
public:
	//与IrisManager中的相对应
    bool GetIrisFeature(EyeFlag flag,unsigned char*&pIrisData,int &size);               //获取虹膜特征，分左右眼获取
	//bool SetIrisFeature(uuid_t ut,short flag,unsigned char *pIrisData,int size);           //注册特征写入并保存
    bool SelectInfoFromFeature(int index,PeopleInfo& name,EyeFlag type);                //根据特征序号获得人员信息
	// 通过虹膜UUID获取人员
    bool GetPeopleInfoByIrisFeature(const std::string&  irisuuid,PeopleInfo& personinfo);
public:
	//memory中的特征的管理操作，增、删、改、查
    bool InsertFeatureData(const std::string& ud,std::shared_ptr<PeopleNode> &pPnode,EyeFlag flag, const unsigned char *pIrisData);            //插入一条

    int DeleteFeatureData(const std::string& ud,EyeFlag flag);

	//分开插入人员和特征，但更新和删除必须同步
	bool InserPersonData(std::shared_ptr<PeopleNode> &pTemp);
	void DeletePeopleData(std::shared_ptr<PeopleNode> &pTemp);

public:
	void ReleaseFeature(void);                //通知特征内存解锁----显示释放所有数据
	bool LockData(void);                      //显示的锁和解锁函数
	bool UnlockData(void);
	void PeopleCount(void);                   //人员计数
	void Init(void);
public:
	//管理员分别操作
    bool BuildSuperData(EyeFlag flag,unsigned char *pIrisData,PeopleNode &pnData);
    bool GetSuperFeature(EyeFlag flag,unsigned char*&pIrisData,int &size);
	bool ReleaseSuperData(void);
public:
	//处理人员特征MAP的方法－－//替代MAP[]操作函数
	int FindKeyFeature(std::string sUuid);
private:
	//对管理员和普通用户分别初始化
	void InitSuperData(void);
	void InitData(void);
public:
	FeatureMap _mapFeature;                   //人员特征ID和特征ID在内存中的索引映射表
public:
	std::mutex _dataMutex;                    //数据加锁的互斥体
private:
	//管理员部分
	PeopleNode _superCount[g_SuperCount];     //管理员特征序列控制在12以内
	unsigned char *_pFeatureData;             //管理特征数据缓冲区
	unsigned char *_pLFeatureData;            //管理员特征ID缓冲区的当前位置指针
	unsigned char *_pRFeatureData;
	unsigned char *_pLHead;                   //特征的左右起始指针
	unsigned char *_pRHead;
    unsigned int _superLCount;                         //左右眼特征数量
    unsigned int _superRCount;


	PIrisToNode   _pPersonInfo;               //特征相关人员的数据缓冲区---暂时不用
	std::mutex _personMutex;                  //人员互斥体－－－分开的目的是减少锁的粒度－－暂时不用

	//特征及人员处理相关数据结构
	std::list<std::shared_ptr<PeopleNode>> _peopleData;        //人员信息链表
	std::list<std::shared_ptr<ControlNode>> _controlData;      //控制节点链表----nouse
	//内存分两块，不再左右逼近－其实就相当于尾指针
	unsigned char *_pPosFeature;                               //特征当前位置  左眼
	ControlNode * _pPosCNode;                                  //人员当前位置  左眼对应人
	unsigned char *_pPosRFeature;                              //特征当前位置  右眼
	ControlNode * _pPosRCNode;                                 //人员当前位置  右眼对应人

	//左右眼特征及人员头指针
	unsigned char * _pLFeatureHead;                            //左眼特征缓冲区头指针
	unsigned char * _pRFeatureHead;                            //右眼
	ControlNode * _pLCNodeHead;                                //左眼对应的控制节点头指针
	ControlNode * _pRCNodeHead;                                //右眼

	int _curPlace;                                             //当前位置索引
	int _curRPlace;                                            //当前位置索引  右眼
	int _countLeft;                                            //左右眼特征和人员数量，这两个是相等的
	int _countRight;
};

