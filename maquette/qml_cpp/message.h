#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDebug>

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
public:
    void setAuthor(const QString &a) {
        qDebug() << "setAuthor" << a;
        if (a != m_author) {
            m_author = a;
            emit authorChanged();
        }
    }
    QString author() const {
        qDebug() << "author" << m_author;
        return m_author;
    }
signals:
    void authorChanged();
private:
    QString m_author;
};

#endif // MESSAGE_H

