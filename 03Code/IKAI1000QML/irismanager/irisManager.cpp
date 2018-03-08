/******************************************************************************************
 ** 文件名:   IrisManager.cpp
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

#include "irisManager.h"
#include <QThread>
#include <QDebug>

#include "../Common/Exectime.h"
#include "../Common/Logger.h"

extern std::string StringFromUuid(const uuid_t ud);

IrisManager* IrisManager::m_irisManager = nullptr;

IrisManager::IrisManager(QObject *parent) :
    QObject(parent),
    m_totalLoadCount(0),
    m_loadingCount(0),
    m_loadingNow(false),
    m_loadBlock(256)
{
     msqldatabase::get_Instance()->open();
}

IrisManager::~IrisManager()
{
    releaseData();
}

/*********************************
功   能：单例模式
作   者：yqhe
日   期：20180102
修改 人：
修改内容：
修改日期：
参   数：
     1.
**********************************/
IrisManager* IrisManager::get_instance()
{
    if (nullptr == m_irisManager)
    {
        m_irisManager = new IrisManager();
    }

    return m_irisManager;
}

/*****************************************************************************
 *                         设置加载人员及特征数据的参数
 *  函 数 名：initARG
 *  功    能：设置加载参数
 *  说    明：
 *  参    数：IrisManInitArgs
 *  返 回 值：错误码，0为成功
 *  创 建 人：yqhe
 *  创建时间：2018-02-23
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int IrisManager::initARG(const IrisManInitArgs& args)
{
    int ret = E_IRISMAN_SUCCESS;

    if (m_loadingNow)
    {
        // 正在装载中，不能设置参数
        return E_IRISMAN_LOADING_NOW_ERROR;
    }

    m_irisManInitArgs.loadLocal = args.loadLocal;

    if (args.sendSigBlock<0)   // 检测有效性
    {
        ret = E_IRISMAN_INITARG_ERROR;
    }
    else
    {
        // 如果值无效，仍为缺省设置
        m_irisManInitArgs.sendSigBlock = args.sendSigBlock;
    }

    // 调整单次加载的条数
    if ((m_irisManInitArgs.sendSigBlock>0)
            &&(m_loadBlock>m_irisManInitArgs.sendSigBlock))
    {
        m_loadBlock = m_irisManInitArgs.sendSigBlock;
    }

    if (m_irisManInitArgs.loadLocal)
    {
        //加载用的定时器，初始化这个类后100毫秒，开始加载特征，启动一次即可
        QTimer::singleShot(100, this, SLOT(slot_startLoad()));
    }

    return ret;
}

/*****************************************************************************
 *                         槽函数：开始加载特征
 *  函 数 名：slot_startLoad
 *  功    能：开始加载
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：yqhe
 *  创建时间：2018-02-23
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void IrisManager::slot_startLoad()
{
    Init();
}

/*****************************************************************************
 *                         初始化加载人员及特征数据
 *  函 数 名：Init
 *  功    能：初始化
 *  说    明：
 *  参    数：无
 *  返 回 值：是否成功
 *  创 建 人：fjf
 *  创建时间：2014-03-07
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void IrisManager::Init(void)
{
	Exectime etm(__FUNCTION__);
	//加载超级用户和一般用户的特征及数据
    this->loadData();
}
/*****************************************************************************
 *                         获得特征数据
 *  函 数 名：GetIrisFeature
 *  功    能：获取相应的数据
 *  说    明：
 *  参    数：flag:特征标记
 *           pIrisData :特征缓冲区
 *           size:特征数量
 *  返 回 值：是否成功
 *  创 建 人：fjf
 *  创建时间：2014-01-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
bool IrisManager::getIrisFeature(const EyeFlag& flag,unsigned char *&pIrisData,int& size)
{
	Exectime etm(__FUNCTION__);
    bool bRet = this->_irisData.GetIrisFeature(flag,pIrisData,size);
	return bRet;
}

/*****************************************************************************
 *                         释放特征数据的锁操作
 *  函 数 名：ReleaseFeature
 *  功    能：获取相应的数据
 *  说    明：
 *  参    数：
 *  返 回 值： 错误码，为0表示成功
 *  创 建 人：fjf
 *  创建时间：2014-01-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/

int IrisManager::releaseData(void)
{
	Exectime etm(__FUNCTION__);
    if (m_loadingNow)
    {
        return E_IRISMAN_LOADING_NOW_ERROR;
    }

	std::lock_guard<std::mutex> lk(this->_irisData._dataMutex);
	this->_mapPeople.clear();                                    //清除人员映射
    this->_irisData.ReleaseFeature();

    m_totalLoadCount = 0;
    m_loadingCount = 0;

    return E_IRISMAN_SUCCESS;
}

/*****************************************************************************
 *                         查找指定映射表中的数据
 *  函 数 名：FindKeyPeople
 *  功    能：查找MAP中相应的数据
 *  说    明：取代MAP[].如果使用[]会在没有键值的情况下插入一个默认值，增加无用数据
 *  参    数：
 *  返 回 值：指针
 *  创 建 人：fjf
 *  创建时间：2014-05-04
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
std::shared_ptr<PeopleNode> IrisManager::FindKeyPeople(std::string sKey)
{
	Exectime etm(__FUNCTION__);
	PeopleMap::iterator it = _mapPeople.find(sKey);
	if (_mapPeople.end() != it)
	{
		return it->second;
	}

	return NULL;
}
/*****************************************************************************
 *                         批量添加人员特征
 *  函 数 名：SetIrisFeature
 *  功    能：批量的增加人员的特征到内存缓冲
 *  说    明：
 *  参    数：id:人员信息指针（人员数据）
 *  			flag:特征类型
 *  			pIrisData:特征缓冲区
 *  			size:特征数量
 *  返 回 值：是否成功
 *  创 建 人：fjf
 *  创建时间：2014-01-14
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
bool IrisManager::SetIrisFeature(const InfoData &id,EyeFlag flag, const unsigned char* pIrisData)
{
	Exectime etm(__FUNCTION__);
	//数据库接口写好后，FOR循环移到loaddata函数中，Add函数也调用这个函数来操作
	//for(int len = 0;len < size;len++)
	//{
	//创建人员数据---注意判断一人多个特征
    //std::string sKey = StringFromUuid(id.PeopleData.PersonID);
    std::string sKey = id.PeopleData.PersonID;
	if (NULL == FindKeyPeople(sKey))
	{
		std::shared_ptr<PeopleNode> pTemp = std::make_shared<PeopleNode>();
		pTemp->Name = id.PeopleData.Name;//id[len].PeopleData.name;
		pTemp->CardID = id.PeopleData.CardID;
        pTemp->UserID = id.PeopleData.UserID;
		pTemp->Depart = id.PeopleData.Depart;
        pTemp->IsSuper = id.PeopleData.IsSuper;
        pTemp->PeopleID=id.PeopleData.PersonID;
//        memmove(pTemp->PeopleID,id.PeopleData.PersonID,g_UuidLen);
		_irisData.InserPersonData(pTemp);//add ---remove


		//创建人员ID到人员信息映射MAP
		this->_mapPeople[sKey] = pTemp;
		//_irisData.InsertFeatureData(id[len].ud,pTemp,flag,pIrisData+len*512);
		_irisData.InsertFeatureData(id.ud,pTemp,flag,pIrisData);

	}
	else
	{
		//此处可替换_mapPeople[sKey],但前面进行了判断，所以此处不会出现误插入
		_irisData.InsertFeatureData(id.ud,_mapPeople[sKey],flag,pIrisData);
	}
	//}

	return true;
}
/*****************************************************************************
 *                         批量添加人员特征
 *  函 数 名：GetStringFromChar
 *  功    能：从数组形式转到字符串形式
 *  说    明：
 *  参    数：unc:uuid_t类型的数组
 *  返 回 值：std::string类型的字符串
 *  创 建 人：fjf
 *  创建时间：2014-01-14
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
std::string IrisManager::GetStringFromChar(unsigned char* unc)
{
	Exectime etm(__FUNCTION__);
	//char buf[g_UuidLen + 1];
	//memset(buf,0,g_UuidLen + 1);
	//memmove(buf,unc,g_UuidLen);
	//std::string s(buf);

    return StringFromUuid(unc);
}
/*****************************************************************************
 *                         获得指定特征数据的人员信息
 *  函 数 名：SelectInfoFromFeature
 *  功    能：获取相应的数据
 *  说    明：
 *  参    数：index:特征索引
 *           name :人员信息
 *  返 回 值：是否成功
 *  创 建 人：fjf
 *  创建时间：2014-01-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int IrisManager::getPersonInfoByIndex(int index,PeopleInfo &info, const EyeFlag& type)
{
	Exectime etm(__FUNCTION__);
    bool bret = this->_irisData.SelectInfoFromFeature(index,info,type);

    if (bret)
    {
        return E_IRISMAN_SUCCESS;
    }
    else
    {
        return E_IRISMAN_NOPERSON_ERROR;
    }
}

bool IrisManager::getPersonInfoById(const std::string& irisuuid,PeopleInfo& personinfo)
{
	Exectime etm(__FUNCTION__);
	return this->_irisData.GetPeopleInfoByIrisFeature(irisuuid,personinfo);
}

int IrisManager::deletePerson(const PeopleInfo &info)
{
    Exectime etm(__FUNCTION__);

    int iRet = -1;
    if (m_loadingNow)
    {
        LOG_INFO("DeletePersonAndFeatureData: loading now, wait for a moment");
        return E_IRISMAN_LOADING_NOW_ERROR;
    }

//    std::string sKey = StringFromUuid(info.PersonID);
    std::string sKey = info.PersonID;
    std::shared_ptr<PeopleNode> p = FindKeyPeople(sKey);

    //判断人员信息
    if (NULL == p )
    {
        LOG_INFO("DeleteFeatureData: NULL == p,key: [%s], ret: %d",sKey.c_str(),iRet);
        return E_IRISMAN_NOPERSON_ERROR;
    }

    //锁住当前动作
    {
        std::lock_guard<std::mutex> lk(this->_irisData._dataMutex);

        m_loadingNow = true;

        //删除人员特征－－分左右眼
        for (std::string featureID:p->LeftFeature)
        {
            //删除后仍然需要重组和重新映射
            iRet = this->_irisData.DeleteFeatureData(featureID,EyeFlag::Left);
            if(iRet != 0)
            {
                LOG_ERROR("DeleteFeatureData Left failed. %d", E_IRISMAN_DEL_FEATURE_ERROR)
            }
        }

        for (std::string featureID:p->RightFeature)
        {
            //删除后仍然需要重组和重新映射
            LOG_INFO("test-------step1");
            iRet = this->_irisData.DeleteFeatureData(featureID,EyeFlag::Right);
            LOG_INFO("test--------step2");
            if(iRet != 0)
            {
                LOG_ERROR("DeleteFeatureData Right failed. %d", E_IRISMAN_DEL_FEATURE_ERROR);
            }
        }

        //删除人员及映射
        p->LeftFeature.clear();
        p->RightFeature.clear();
    }

    // TODO
    _irisData.DeletePeopleData(p);

    _mapPeople.erase(sKey);

    m_loadingNow = false;

    return E_IRISMAN_SUCCESS;
}

/*****************************************************************************
 *                         删除指定人员特征
 *  函 数 名：DeleteFeatureData
 *  功    能：在内存中删除相关人员的内存特征及相关数据
 *  说    明：
 *  参    数：ud:删除相关的人员的人员ID
 *  			flag:人员特征的类型
 *  返 回 值：返回删除情况
 *  创 建 人：fjf
 *  创建时间：2014-01-14
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int IrisManager::deleteFeatureData(const InfoData& info)
{
	Exectime etm(__FUNCTION__);
    int iRet = E_IRISMAN_ERROR_BASE;

    if (m_loadingNow)
    {
        LOG_INFO("DeleteFeatureData: loading now, wait for a moment");
        return E_IRISMAN_LOADING_NOW_ERROR;
    }

//    std::string sKey = StringFromUuid(info.PeopleData.PersonID);
    std::string sKey = info.PeopleData.PersonID;
	std::shared_ptr<PeopleNode> p = FindKeyPeople(sKey);

	//判断人员信息
	if (NULL == p )
	{
        LOG_INFO("DeleteFeatureData: NULL == p,key: [%s], ret: %d",sKey.c_str(),iRet);
        return E_IRISMAN_NOPERSON_ERROR;
	}

	//锁住当前动作
    {
        std::lock_guard<std::mutex> lk(this->_irisData._dataMutex);

        m_loadingNow = true;

        //删除人员特征－－分左右眼
        std::list<std::string>::iterator it = p->LeftFeature.begin();
        while (it != p->LeftFeature.end())
        {
            //删除后仍然需要重组和重新映射
            // if(uuid_compare(info.ud,(*it).ud) == 0)
            if (info.ud==(*it))
            {
                iRet = this->_irisData.DeleteFeatureData((*it),EyeFlag::Left);
                if(iRet != 0)
                {
                    LOG_ERROR("DeleteFeatureData Left failed. %d",iRet)
                }
                else
                {
                    p->LeftFeature.erase(it);
                }
                break;
            }
            it ++;
        }

        it = p->RightFeature.begin();
         while (it != p->RightFeature.end())
        {
            //删除后仍然需要重组和重新映射
            // if(uuid_compare(info.ud,(*it).ud) == 0)
             if (info.ud==(*it))
            {
                iRet = this->_irisData.DeleteFeatureData((*it),EyeFlag::Right);
                if(iRet != 0)
                {
                    LOG_ERROR("DeleteFeatureData Right failed. %d",iRet);
                }
                else
                {
                     p->RightFeature.erase(it);
                }
                break;
            }
            it ++;
        }
    }

    // 如果这个人没有虹膜就可以删除映射了
    if(p->LeftFeature.size() == 0 && p->RightFeature.size() == 0 )
    {
        _irisData.DeletePeopleData(p);

        _mapPeople.erase(sKey);
    }

    m_loadingNow = false;

    return E_IRISMAN_SUCCESS;
}

/*****************************************************************************
 *                         添加相应的特征到内存数组
 *  函 数 名：AddFeatureData
 *  功    能：添加相应的数据到内存中的缓冲区，并建立映射，以送入算法进行匹配
 *  说    明：新增的数据不用进行重新映射，只把新的映射添加即可。
 *  参    数：ud:特征ID还是人员ID，最后再与接口定
 *  			flag:特征类型
 *  			pIrisData:特征数据
 *  返 回 值：增加人员特征到内存
 *  创 建 人：fjf
 *  创建时间：2014-01-14
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int IrisManager::addFeatureData(const InfoData& info)
{
	Exectime etm(__FUNCTION__);
	//得动态增加人员信息
	//2014-06-10增加：对人员和特征的加载是否一次加载左右眼，处理InfoData这个数据结构为数组，可以直接插入批量数据
	//std::shared_ptr<PeopleNode> pTemp = std::make_shared<PeopleNode>();
	//pTemp->Name = info.PeopleData.Name;
	//pTemp->Sex = info.PeopleData.Sex;
    //pTemp->UserID = info.PeopleData.UserID;
	//人员处理未增加
	//是否调用SetIrisFeature
	//return this->_irisData.InsertFeatureData(info.ud,pTemp,flag,pIrisData);
    int iRet = E_IRISMAN_ERROR_BASE;
    if (m_loadingNow)
    {
        LOG_INFO("AddFeatureData: loading now, wait for a moment");
        return E_IRISMAN_LOADING_NOW_ERROR;
    }

    m_loadingNow = true;

    if ( this->SetIrisFeature(info,info.TypeControl,info.FeatureData))
	{
        iRet = E_IRISMAN_SUCCESS;
	}

    m_loadingNow = false;

	return iRet;
}

int IrisManager::updatePersonInfo(const PeopleInfo& info)
{
    int nret = E_IRISMAN_ERROR_BASE;

    if (m_loadingNow)
    {
        LOG_INFO("UpdatePersonInfo: loading now, wait for a moment");
        return E_IRISMAN_LOADING_NOW_ERROR;
    }

    m_loadingNow = true;
//    std::string sKey = StringFromUuid(info.PersonID);
    std::string sKey = info.PersonID;
    std::shared_ptr<PeopleNode> pTemp = FindKeyPeople(sKey);

    //判断人员信息
    if (NULL == pTemp )
    {
        LOG_INFO("UpdatePersonInfo: NULL == pTemp,key: [%s], ret: %d",sKey.c_str(),nret);
        return E_IRISMAN_NOPERSON_ERROR;
    }

    pTemp->Name = info.Name;//id[len].PeopleData.name;
    pTemp->CardID = info.CardID;
    pTemp->UserID = info.UserID;
    pTemp->Depart = info.Depart;
    pTemp->IsSuper = info.IsSuper;

    m_loadingNow = false;

    return  nret;
}

/*****************************************************************************
 *                         对特征数据进行处理——包括增、删、改、查
 *  函 数 名：FeatureDataDoWith
 *  功    能：根据情况来控制特征数据的合并等动作
 *  说    明：
 *  参    数：flag:特征标记
 *           pIrisData :特征缓冲区
 *           size:特征数量
 *  返 回 值：是否成功
 *  创 建 人：fjf
 *  创建时间：2014-01-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/

bool IrisManager::FeatureDataDoWith()
{
	Exectime etm(__FUNCTION__);
	bool bRet = false;
	if (_isChange)
	{
		for(InfoData id:_dataBuf)
		{
			//自己处理一下人员信息？
			//this->_irisData.InsertFeatureData(id.ud,id.TypeControl,id.FeatureData);
		}

		//写数据库的行为暂时不知道有没有。现在只支持在脱机同步下自动存储数据库

		this->_dataBuf.clear();
	}
	return bRet;
}
/*****************************************************************************
 *                         对特征数据进行加锁
 *  函 数 名：LockData
 *  功    能：在数据并发时，用锁保证安全
 *  说    明：
 *  参    数：无
 *  返 回 值：是否成功
 *  创 建 人：fjf
 *  创建时间：2014-02-17
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void IrisManager::LockData(void)
{
	Exectime etm(__FUNCTION__);
	_irisData.LockData();
}
/*****************************************************************************
 *                         对特征数据进行争锁
 *  函 数 名：UnlockData
 *  功    能：在数据并发后，对数据操作进行解锁，防止死锁
 *  说    明：
 *  参    数：无
 *  返 回 值：是否成功
 *  创 建 人：fjf
 *  创建时间：2014-02-17
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void IrisManager::UnlockData(void)
{
	Exectime etm(__FUNCTION__);
	_irisData.UnlockData();
}

/*****************************************************************************
 *                         从数据库加载数据
 *  函 数 名：LoadData
 *  功    能：从数据库中读写数据
 *  说    明：
 *  参    数：无
 *  返 回 值：是否成功
 *  创 建 人：fjf
 *  创建时间：2014-02-17
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int IrisManager::loadData(void)
{
	Exectime etm(__FUNCTION__);

    if (m_loadingNow)
    {
        return E_IRISMAN_LOADING_NOW_ERROR;
    }

    // 加载前先释放之前加载的数据
    releaseData();

	//通过读写数据库调用_IrisData函数，增加特征数据
    m_totalLoadCount = msqldatabase::get_Instance()->getIrisTotalNum();
    if (m_totalLoadCount<0)
    {
        return m_totalLoadCount;
    }

    m_loadingNow = true;
    int ret = E_MSQL_SUCCESS;
    m_loadingCount = 0;

    int emitCount = 0;
    int emitBlock = m_irisManInitArgs.sendSigBlock;

    QList<ViewPersonIris> irisInfoList;

    while ((m_loadingCount<m_totalLoadCount)&&(ret==E_MSQL_SUCCESS))
	{

        // 使用缺省条数
        ret = msqldatabase::get_Instance()->getPersonIrisInfo(irisInfoList, m_loadingCount, m_loadBlock);
        if (ret!=E_MSQL_SUCCESS)
        {
            break;
        }

        int len = irisInfoList.size();

		//保存数据并建立映射关系
		for (int size = 0;size < len;size++)
		{
			InfoData id;
            id.PeopleData.Name = irisInfoList[size].m_name.toStdString();
            id.PeopleData.PersonID = irisInfoList[size].m_personid.toStdString();

             id.PeopleData.Sex = irisInfoList[size].m_sex.toStdString();

             memmove(id.FeatureData, irisInfoList[size].m_iriscode, IK1000_ENROLL_FEATURE_SIZE);

            id.TypeControl = (EyeFlag)irisInfoList[size].m_eyeflag;
            id.ud = irisInfoList[size].m_irisdataid.toStdString().c_str();

			//增加卡号、工号、部门   2014-06-18
            id.PeopleData.CardID = irisInfoList[size].m_cardid.toStdString();
            id.PeopleData.UserID = irisInfoList[size].m_userid.toStdString();

            id.PeopleData.IsSuper = irisInfoList[size].m_superid;

			//使用原函数
            SetIrisFeature(id,id.TypeControl,id.FeatureData);

            m_loadingCount ++;

            // 检测是否需要发一次加载进度信号
            if (emitBlock>0)
            {
                int block = m_loadingCount/emitBlock;

                if (block>emitCount)
                {
                    emit loadFeatureResult(m_loadingNow, ret, m_totalLoadCount, m_loadingCount);
                    emitCount = block;
                }
            }
        }

        irisInfoList.clear();

	}

    m_loadingNow = false;

    // 加载完成后，再发一次信号
    emit loadFeatureResult(m_loadingNow, ret, m_totalLoadCount, m_loadingCount);

    return ret;
}

/*****************************************************************************
 *                         获取当前加载状态
 *  函 数 getLoadState
 *  功    能：从数据库中读写数据
 *  说    明：
 *  参    数：OUT loading -- 是否正在加载
 *                 OUT totalCount -- 需要加载的总特征条数
 *                 OUT leftCount -- 已加载的左眼特征个数
 *                 OUT rightCount -- 已加载的右眼特征个数
 *  返 回 值：总特征条数
 *  创 建 人：yqhe
 *  创建时间：2018-02-23
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int  IrisManager::getLoadState(bool& loading, int& totalCount, int& leftCount, int& rightCount)
{
    loading = m_loadingNow;
    totalCount = m_totalLoadCount;

    // GetIrisFeature(EyeFlag flag,unsigned char *&pIrisData,int& size)

    unsigned char *pIrisData;
    EyeFlag flag = EyeFlag::Left;
    this->getIrisFeature(flag, pIrisData, leftCount);

    flag = EyeFlag::Right;
    this->getIrisFeature(flag, pIrisData, rightCount);

    return totalCount;
}


