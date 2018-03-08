#include "userlistmodel.h"

UserListModel::UserListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_dptr(new UserListModelPrivate)
{
    reload();
}

UserListModel::~UserListModel()
{
    delete m_dptr;
}

int UserListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
    return m_dptr->m_users.size();
}

QVariant UserListModel::data(const QModelIndex &index, int role) const
{
    UserData *data = m_dptr->m_users[index.row()];
    return data->at(role - Qt::UserRole);
}

QHash<int, QByteArray> UserListModel::roleNames() const
{
    return m_dptr->m_roleNames;
}

void UserListModel::reload()
{
    beginResetModel();

    m_dptr->reset();
    m_dptr->load();

    endResetModel();
}

// modified at 20180301 by yqhe
// 考虑到m_dptr->m_users为空的情况
void UserListModel::remove(int index)
{
    if (m_dptr->m_users.size()<=0)
    {
        return ;
    }

    beginRemoveRows(QModelIndex(), index, index);
    delete m_dptr->m_users.takeAt(index);
    endRemoveRows();
}

// modified at 20180301 by yqhe
// 考虑到m_dptr->m_users为空的情况
QString UserListModel::getUserId(int index)
{
    if (m_dptr->m_users.size()<=0)
    {
        return "";
    }

    UserData *data = m_dptr->m_users[index];
    QString userId = data->at(1);
    return userId.remove("(").remove(")");
}

// modified at 20180301 by yqhe
// 考虑到m_dptr->m_users为空的情况
QString UserListModel::getUserName(int index)
{
    if (m_dptr->m_users.size()<=0)
    {
        return "";
    }

    UserData *data = m_dptr->m_users[index];
    return data->at(0);
}

void UserListModel::slotModelReload()
{
    reload();
}



