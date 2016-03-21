#ifndef XINGCOM_H
#define XINGCOM_H

#include <QObject>
#include <QLibrary>
#include <Windows.h>
#include <QDebug>
#include <QString>
#include <QAxBase>
#include <QDebug>
#include <QAxObject>
#include "com1_axobj.h"


class xingcom : public QObject
{
    Q_OBJECT
public:
    explicit xingcom(QObject *parent = 0);
    QLibrary lib;

//    typedef BOOL	(*COM_ConnectServer					) (char * ,long );

//    COM_ConnectServer       m_connectserver;
   //QAxObject *comobj;
    com1_axobj *obj;
    com1_axobj *obj1;
    com1_axobj *obj2;
    com1_axobj *XA_Session;
    com1_axobj *XA_DataSet;
    QString htsip;
    QString demoip;
    int serverport;
    bool result_1;

    bool com_connect(int type);
    bool com_login(QByteArray Qid,QByteArray Qpasswd,QByteArray Qauthpasswd);

private :
    QByteArray serverip;

signals:

public slots:
    void XASession_Login_Login(QString str);
    int com_1833_result();
    bool com_1833_request();

};

#endif // XINGCOM_H
