#include "usermanage.h"
#include <QDebug>
#include <QUuid>

userManage::userManage(QObject *parent) :
    QObject(parent)
{
    // 打开数据库返回不为0,则是有错误
    if (0 != msqldatabase::get_Instance()->open())
    {
        qDebug() << __FUNCTION__ << "errror";
    }
    initPersonInfo();   // 初始化用户信息列表
    idListClear(); // 删除用户id列表初始化为空
    m_page2More = 0;    // 初始化进入编辑更多界面非法
}

/*********************************
 功      能: 读取person结构体中地址信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: QString person结构体的用户ID
**********************************/
QString userManage::userId() const
{
    return m_personInfo.m_id;
}

/*********************************
 功      能: 设置person结构体中地址信息，用于接收QML设置值
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: QString m_address 地址值
 返  回 值: 无
**********************************/
void userManage::setUserId(const QString id)
{
    m_personInfo.m_id = id;
    emit userIdChanged();
}

/*********************************
 功      能: 读取person结构体中地址信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: QString person结构体的用户ID
**********************************/
QString userManage::userName() const
{
    return m_personInfo.m_name;
}

/*********************************
 功      能: 设置person结构体中地址信息，用于接收QML设置值
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: QString m_address 地址值
 返  回 值: 无
**********************************/
void userManage::setUserName(const QString name)
{
    m_personInfo.m_name = name;
    emit userNameChanged();
}

/*********************************
 功      能: 读取person结构体中地址信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: QString person结构体的用户ID
**********************************/
bool userManage::isAdmin() const
{
    return m_personInfo.m_superid;
}

/*********************************
 功      能: 设置person结构体中地址信息，用于接收QML设置值
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: bool isAdmin 地址值
 返  回 值: 无
**********************************/
void userManage::setIsAdmin(const bool isAdmin)
{
    m_personInfo.m_superid = isAdmin;
    emit isAdminChanged();
}

/*********************************
 功      能: 读取person结构体中性别信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: QString person结构体的性别
**********************************/
QString userManage::sex() const
{
    return m_personInfo.m_sex;
}

/*********************************
 功      能: 设置person结构体中性别信息，用于接收QML设置值
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: QString m_sex 性别
 返  回 值: 无
**********************************/
void userManage::setSex(const QString m_sex)
{
    m_personInfo.m_sex = m_sex;
    emit sexChanged();
}

/*********************************
 功      能: 读取person结构体中卡号字段信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: QString person结构体的卡号字段
**********************************/
QString userManage::cardid() const
{
    return m_personInfo.m_cardid;
}

/*********************************
 功      能: 设置person结构体中卡号字段信息，用于接收QML设置值
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: QString m_cardid 卡号字段
 返  回 值: 无
**********************************/
void userManage::setCardid(const QString m_cardid)
{
    m_personInfo.m_cardid = m_cardid;
    emit cardidChanged();
}

/*********************************
 功      能: 读取person结构体中身份证号码信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: QString person结构体的身份证号码
**********************************/
QString userManage::idcard() const
{
    return m_personInfo.m_idcard;
}

/*********************************
 功      能: 设置person结构体中身份证号码信息，用于接收QML设置值
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: QString m_idcard 身份证号码
 返  回 值: 无
**********************************/
void userManage::setIdcard(const QString m_idcard)
{
    m_personInfo.m_idcard = m_idcard;
    emit idcardChanged();
}

// 更多新界面不需要
//QString userManage::memo() const
//{
//    return m_personInfo.m_memo;
//}

//void userManage::setMemo(const QString m_memo)
//{
//    m_personInfo.m_memo = m_memo;
//    emit memoChanged();
//}

/*********************************
 功      能: 读取person结构体中职业信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: QString person结构体的职业
**********************************/
QString userManage::profession() const
{
    return m_personInfo.m_profession;
}

/*********************************
 功      能: 设置person结构体中职业信息，用于接收QML设置值
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: QString m_profession 职业
 返  回 值: 无
**********************************/
void userManage::setProfession(const QString m_profession)
{
    m_personInfo.m_profession = m_profession;
    emit professionChanged();
}

/*********************************
 功      能: 读取person结构体中是否有虹膜数据，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: bool person结构体的是否有虹膜数据
**********************************/
bool userManage::hasirisdata() const
{
    return m_personInfo.m_hasirisdata;
}

/*********************************
 功      能: 设置person结构体中是否有虹膜数据，用于接收QML设置值
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: bool m_hasirisdata 是否有虹膜数据
 返  回 值: 无
**********************************/
void userManage::setHasirisdata(const bool m_hasirisdata)
{
    m_personInfo.m_hasirisdata = m_hasirisdata;
    emit hasirisdataChanged();
}

/*********************************
 功      能: 读取person结构体中地址信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: QString person结构体的地址值
**********************************/
QString userManage::address() const
{
    return m_personInfo.m_address;
}

/*********************************
 功      能: 读取person结构体中地址信息，用于QML
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: QString m_address 地址值
 返  回 值: 无
**********************************/
void userManage::setAddress(const QString m_address)
{
    m_personInfo.m_address = m_address;
    emit addressChanged();
}

/*********************************
 功      能: 删除待删除列表idList中的用户
 作      者: liben
 日      期: 20180304
 修  改 人:
 修改内容:
 修改日期:
 参      数:  无
 返  回 值: int 表示当前从那个界面进入的编辑更多界面，1表示新建用户，2表示编辑用户
**********************************/
int userManage::page2More() const
{
    return m_page2More;
}

/*********************************
 功      能: 设置进入编辑更多界面的前一个界面
 作      者: liben
 日      期: 20180304
 修  改 人:
 修改内容:
 修改日期:
 参      数:  int 表示当前从那个界面进入的编辑更多界面，1表示新建用户，2表示编辑用户
 返  回 值:  无
**********************************/
void userManage::setPage2More(const int m_previousPage)
{
    m_page2More = m_previousPage;
    emit page2MoreChanged();
}

void userManage::saveNewUser()
{
//    if(m_personInfo.m_id.isEmpty())
//    {
//        ///告诉qml字段空
//        qDebug()  <<"saving............ failed";
//        return;
//    }
    // 数据合法性检测已经有QML界面进行检测

//    DBPersonInfo personInfo;
//    QList<PDBPersonInfo> personInfoList;
    m_personInfo.m_personid = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
//    qDebug() << "PersonId: " << personInfo.m_personid;
//    personInfo.m_name = m_personInfo.m_name;
//    personInfo.m_id = m_personInfo.m_id;
//    personInfo.m_superid = m_personInfo.m_superid;
//    qDebug() << "UserId: " << personInfo.m_id;
//    qDebug() << "UserName: " << personInfo.m_name;
//    qDebug() << "isAdmin:  "<< m_isAdmin;

    emit sigSavePerson(m_personInfo);
    initPersonInfo();   // 初始化person结构体
//    personInfoList.push_back(&personInfo);
//    if(E_MSQL_SUCCESS == msqldatabase::get_Instance()->addPersonInfo(personInfoList))
//    {
//        qDebug() << "AddPersonInfo is successful.";
//        emit sigPersonTableUpdated();
//    }
//    else
    //        qDebug() << "AddPersonInfo is failed.";
}

/*********************************
 功      能: 将改变的person信息存回数据库
 作      者: liben
 日      期: 20180302
 修  改 人:
 修改内容:
 修改日期:
 参      数: 无
 返  回 值: 无
**********************************/
void userManage::updateUser()
{
    int ret = 0;
    ret = msqldatabase::get_Instance()->updatePersonInfo(&m_personInfo);  // 修改用户信息失败
    if (0 != ret)
    {
        qDebug() << "update errror! user's uuid " << m_personInfo.m_personid << "  " << ret;
    }
}

/*********************************
 功      能: 根据userId改变m_personInfo的值
 作      者: liben
 日      期: 20180301
 修  改 人:
 修改内容:
 修改日期:
 参      数: IN userId  用户id
 返  回 值: 无
**********************************/
void userManage::changPersonInfo(IN QString userId)
{
    // 此函数调用于由用户列表进入编辑用户界面之前，以实现获取person表的制定记录
    // 那么当退出编辑界面的时候，则考虑需要重新初始化personInfoList列表
    QStringList userIdList(userId);
    QMap<QString, DBPersonInfo> personInfoMap;
    int ret = 0;
    ret = msqldatabase::get_Instance()->getPersonInfo(personInfoMap, userIdList); // 获得person表中指定用户id的记录
    if (0 != ret)
    {
        qDebug() << __FUNCTION__ << "get person record error" << userId << "  " << ret;
        return;
    }
    initPersonInfo();   // 重新初始化person结构体
    m_personInfo = personInfoMap.first();    // 由于只是查找一项，直接获取第一个就可以了
    // 挨个发送信息改变的信号
    emit userIdChanged();
    emit userNameChanged();
    emit isAdminChanged();
    emit sexChanged();
    emit cardidChanged();
    emit idcardChanged();
    emit professionChanged();
    emit hasirisdataChanged();
    emit addressChanged();
}

/*********************************
 功      能: 根据QML传入的用户id，将此id加入待删除列表idList中
 作      者: liben
 日      期: 20180304
 修  改 人:
 修改内容:
 修改日期:
 参      数: IN QString userId 用户在删除界面的用户id
 返  回 值: 无
**********************************/
void userManage::idListAdd(IN QString userId)
{
    idList.append(userId);
}

/*********************************
 功      能: 删除待删除列表idList中的用户
 作      者: liben
 日      期: 20180304
 修  改 人:
 修改内容:
 修改日期:
 参      数:  无
 返  回 值: 无
**********************************/
void userManage::idListDelete()
{
    int ret = msqldatabase::get_Instance()->delPersonInfo(idList);  // 调用数据库删除函数
    // TODO 此处，仅仅删除了person表，对于其他表该如何操作？？？
    if (0 != ret)   // 说明失败
    {
        qDebug() << __FUNCTION__ << "del person record error" << "  " << ret;
        return;
    }
    idListClear();  // 清空列表
}

