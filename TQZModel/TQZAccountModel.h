#ifndef TQZACCOUNTMODEL_H
#define TQZACCOUNTMODEL_H

#include <QObject>

class TQZAccountModel
{
public:
    explicit TQZAccountModel(QMap<QString, QString> accountMap);

    virtual ~TQZAccountModel();

public:
    QString username();
    QString password();
    QString broker();
    QString tradefront();
    QString marketfront();
    QString appid();
    QString authcode();
    QString appinfo();
    QString interface();

private:
    QString m_username;
    QString m_password;
    QString m_broker;
    QString m_tradefront;
    QString m_marketfront;
    QString m_appid;
    QString m_authcode;
    QString m_appinfo;
    QString m_interface;

signals:

};

#endif // TQZACCOUNTMODEL_H
