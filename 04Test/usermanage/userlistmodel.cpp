#include "userlistmodel.h"

UserListModel::UserListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_dptr(new VideoListModelPrivate)
{
}

UserListModel::~UserListModel()
{
    delete m_dptr;
}

int UserListModel::rowCount(const QModelIndex &parent) const
{
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

QString UserListModel::source() const
{
    return m_strXmlFile;
}

void UserListModel::setSource(const QString &filePath)
{
    m_strXmlFile = filePath;
    reload();
}

void UserListModel::reload()
{
    beginResetModel();

    m_dptr->reset();
    m_dptr->load();

    endResetModel();
}

void UserListModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    delete m_dptr->m_users.takeAt(index);
    endRemoveRows();
}



