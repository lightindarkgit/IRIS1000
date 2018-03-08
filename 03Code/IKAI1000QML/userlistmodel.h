#ifndef USERLISTMODEL_H
#define USERLISTMODEL_H
#include <QAbstractListModel>
#include <QDebug>
#include "msqldatabase.h"

typedef QVector<QString> UserData;

class UserListModelPrivate
{
public:
    UserListModelPrivate()
    {
        int role = Qt::UserRole;
        m_roleNames.insert(role++, "username");
        m_roleNames.insert(role++, "userid");
        msqldatabase::get_Instance()->open();
    }

    ~UserListModelPrivate()
    {
        clear();
    }

    void load()
    {
        UserData *user;
        QMap<QString, QString> m_maplist;

        msqldatabase::get_Instance()->getAllID(m_maplist);
        qDebug() << "Count: " << m_maplist.count();

        QMap<QString, QString>::Iterator it;
        for(it = m_maplist.begin(); it != m_maplist.end(); ++it) {
            user = new UserData();
            user->append(it.value());
            user->append("(" + it.key() + ")");
            m_users.append(user);
            user = 0;
        }
    }

    void reset()
    {
        clear();
    }

    void clear()
    {
        int count = m_users.size();
        if(count > 0)
        {
            for(int i = 0; i < count; i++)
            {
                delete m_users.at(i);
            }
            m_users.clear();
        }
    }

    QHash<int, QByteArray> m_roleNames;
    QVector<UserData*> m_users;
};

class UserListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    UserListModel(QObject *parent = 0);
    ~UserListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void reload();
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE QString getUserId(int index);
    Q_INVOKABLE QString getUserName(int index);

public slots:
    void slotModelReload();

private:
    UserListModelPrivate *m_dptr;
};

#endif // USERLISTMODEL_H
