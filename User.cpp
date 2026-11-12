#include "User.h"

User::User(int id, const QString &name):id(id), name(name)
{

}

int User::getId() const{
    return id;
}

QString User::getName() const{
    return name;
}
