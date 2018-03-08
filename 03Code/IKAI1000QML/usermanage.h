#ifndef USERMANAGE_H
#define USERMANAGE_H

#define OUT
#define IN

#include <QObject>
#include "msqldatabase.h"

/* 此类用于同数据库进行交互，负责用户的新增，修改，删除等操作
 */
class userManage : public QObject
{
    Q_OBJECT
    // person结构中变量对应传入QML中变量名
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged) //用户id，唯一
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)  //姓名,用户名
    Q_PROPERTY(bool isAdmin READ isAdmin WRITE setIsAdmin NOTIFY isAdminChanged)  //是否是管理员: 0不是，1是
    Q_PROPERTY(QString sex READ sex WRITE setSex NOTIFY sexChanged) //性别
    Q_PROPERTY(QString cardid READ cardid WRITE setCardid NOTIFY cardidChanged) //卡号字段，此字段前面补0，凑齐8位
    Q_PROPERTY(QString idcard READ idcard WRITE setIdcard NOTIFY idcardChanged) //身份证号码
//    Q_PROPERTY(QString memo READ memo WRITE setMemo NOTIFY memoChanged) // 备注信息   // 更多新界面不需要
    Q_PROPERTY(QString profession READ profession WRITE setProfession NOTIFY professionChanged) //职业
    Q_PROPERTY(bool hasirisdata READ hasirisdata WRITE setHasirisdata NOTIFY hasirisdataChanged)    //是否有虹膜数据：1--有,0—没有
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged) // 常用住址
    Q_PROPERTY(int page2More READ page2More WRITE setPage2More NOTIFY page2MoreChanged) // 表示编辑更多界面的前一个界面

public:
    explicit userManage(QObject *parent = 0);    

    QString userId() const;
    void setUserId(const QString id);
    QString userName() const;
    void setUserName(const QString name);
    bool isAdmin() const;
    void setIsAdmin(const bool isAdmin);
    QString sex() const;
    void setSex(const QString m_sex);
    QString cardid() const;
    void setCardid(const QString m_cardid);
    QString idcard() const;
    void setIdcard(const QString m_idcard);
//    QString memo() const; // 更多新界面不需要
//    void setMemo(const QString m_memo);   // 更多新界面不需要
    QString profession() const;
    void setProfession(const QString m_profession);
    bool hasirisdata() const;
    void setHasirisdata(const bool m_haririsdata);
    QString address() const;
    void setAddress(const QString m_address);
    int page2More() const;
    void setPage2More(const int m_previousPage);

    Q_INVOKABLE void saveNewUser();
    Q_INVOKABLE void updateUser();  // 将改变的信息存回数据库
    Q_INVOKABLE void changPersonInfo(IN QString userId);   // 通过userId改变personInfo内的数据，以便于读取

    Q_INVOKABLE void initPersonInfo()   // 初始化personInfoList,在退出编辑界面时需要再次调用
    {
        // NOTIFY 此处将person数据结构体中所有数据都初始化一遍，就是说会出现某个值为空，是否影响存入数据库
        m_personInfo.m_personid = QString("");  // uuid设置为空
        m_personInfo.m_name = QString("");  // 姓名设置为空
        m_personInfo.m_id = QString("");    // 用户id设置遍为空
        m_personInfo.m_superid = false; // 设置默认为非管理员
        m_personInfo.m_sex = QString("");   // 设置性别默认为空 TODO 此处性别初始化是否应该为空
        m_personInfo.m_cardid = QString(""); // 设置卡号字段默认为空
        m_personInfo.m_idcard = QString(""); // 设置身份证号默认为空
        m_personInfo.m_memo = QString("");  // 备注信息默认为空
        m_personInfo.m_profession = QString(""); // 设置职业默认为空
        m_personInfo.m_hasirisdata = false; // 设置默认没有虹膜数据
        m_personInfo.m_address = QString(""); // 设置用户常用住址默认为空
        m_personInfo.m_password = QString("");  // 设置用户密码默认为空
        // 还缺少创建时间，更新时间，这两个值写入时无需填写，读出会自动填写
    }
    // 用于清空带删除用户id的列表
    // 在用户删除界面，有取消按钮，所以对应用户id先暂存入此列表中
    // 在用户点击完成，正式删除，并清空列表
    // 一旦用户点击取消，那么就将列表清空，且不删除
    Q_INVOKABLE void idListClear()
    {
        idList.clear();
    }
    Q_INVOKABLE void idListAdd(IN QString userId);  // 向待删除列表idList中添加用户
    Q_INVOKABLE void idListDelete();    // 删除idList中的用户

signals:
    // 对应结构体中变量值变化的信号
    void userIdChanged();
    void userNameChanged();
    void isAdminChanged();
    void sexChanged();
    void cardidChanged();
    void idcardChanged();
//    void memoChanged();   // 更多新界面不需要
    void professionChanged();
    void hasirisdataChanged();
    void addressChanged();
    void page2MoreChanged();

    void sigPersonTableUpdated();

    void sigSavePerson(DBPersonInfo personInfo);
    void personInfoListChanged();

private:
    bool isAdministrator(const QString uid);

private:
    DBPersonInfo m_personInfo;  // 对应数据库person表中一条记录
    QStringList idList; // 用于保存删除用户的列表
    int m_page2More;  // 用于标志是从哪个界面进入编辑更多界面的，以便于在编辑更多界面返回，默认为0,1表示从新建用户，2表示从编辑用户
};

#endif // USERMANAGE_H
