#ifndef XINGCOM_H
#define XINGCOM_H

#include <QObject>
#include <QLibrary>
#include <Windows.h>
#include <QDebug>

class xingcom : public QObject
{
    Q_OBJECT
public:
    explicit xingcom(QObject *parent = 0);
    QLibrary lib;

    typedef BOOL	(*COM_ConnectServer					) (char * ,long );

    COM_ConnectServer       m_connectserver;

signals:

public slots:
};

#endif // XINGCOM_H
