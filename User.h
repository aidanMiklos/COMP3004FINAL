#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(int id, const QString &name);
    virtual ~User()=default;
    int getId() const;
    QString getName() const;
    virtual QString getRole() const=0;
private:
    int id;
    QString name;
};

#endif // USER_H
