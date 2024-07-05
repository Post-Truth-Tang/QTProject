#include "TQZAccountModel.h"

#include <QMap>
#include <QString>
#include <QHash>
#include <QDebug>


TQZAccountModel::TQZAccountModel(QMap<QString, QString> accountMap)
{
    QMap<QString, QString>::const_iterator iterator;
    for (iterator = accountMap.constBegin(); iterator != accountMap.constEnd(); iterator++) {

        if ("username" == iterator.key()) {
            this->m_username = iterator.value();
        } else if ("password" == iterator.key()) {
            this->m_password = iterator.value();
        } else if ("broker" == iterator.key()) {
            this->m_broker = iterator.value();
        } else if ("tradefront" == iterator.key()) {
            this->m_tradefront = iterator.value();
        } else if ("marketfront" == iterator.key()) {
            this->m_marketfront = iterator.value();
        } else if ("authcode" == iterator.key()) {
            this->m_authcode = iterator.value();
        } else if ("appid" == iterator.key()) {
            this->m_appid = iterator.value();
        } else if ("appinfo" == iterator.key()) {
            this->m_appinfo = iterator.value();
        } else if ("interface" == iterator.key()) {
            this->m_interface = iterator.value();
        } else {
            qDebug() << "unknown key: " << iterator.key() << endl;
        }
    }
}

QString TQZAccountModel::username() {
    return this->m_username;
}
QString TQZAccountModel::password() {
    return this->m_password;
}
QString TQZAccountModel::broker() {
    return this->m_broker;
}
QString TQZAccountModel::tradefront() {
    return this->m_tradefront;
}
QString TQZAccountModel::marketfront() {
    return this->m_marketfront;
}
QString TQZAccountModel::appid() {
    return this->m_appid;
}
QString TQZAccountModel::authcode() {
    return this->m_authcode;
}
QString TQZAccountModel::appinfo() {
    return this->m_appinfo;
}
QString TQZAccountModel::interface() {
    return this->m_interface;
}


TQZAccountModel::~TQZAccountModel() {

}
