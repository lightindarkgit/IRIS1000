#ifndef USERLISTMODEL_H
#define USERLISTMODEL_H
#include <QAbstractListModel>

typedef QVector<QString> UserData;

class VideoListModelPrivate
{
public:
    VideoListModelPrivate()
    {
        int role = Qt::UserRole;
        m_roleNames.insert(role++, "username");
        m_roleNames.insert(role++, "userid");
    }

    ~VideoListModelPrivate()
    {
        clear();
    }

    void load()
    {
        UserData *user;

        for(int i = 0; i < 1000; i++) {
            user = new UserData();
            user->append("张三");
            user->append("(" + QString("%1").arg(i, 10, 10, QChar('0')) + ")");
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
    Q_PROPERTY(QString source READ source WRITE setSource)

public:
    UserListModel(QObject *parent = 0);
    ~UserListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    QString source() const;
    void setSource(const QString& filePath);

    Q_INVOKABLE void reload();
    Q_INVOKABLE void remove(int index);

private:
    VideoListModelPrivate *m_dptr;
    QString m_strXmlFile;
};

#endif // USERLISTMODEL_H
