#ifndef TSELLFROM1833_H
#define TSELLFROM1833_H

#include <QObject>
#include <QThread>
#include <Qdebug>
#include <QString>
#include "xing.h"
class TSellfrom1833 : public QThread
{
    Q_OBJECT
public:
    explicit TSellfrom1833();
    bool m_stopflag;
    QString AcntNo_12300;
    QString Pwd_12300;
    QString BalCreTp_12300;
    QString CmsnAppTpCode_12300;
    QString D2balBaseQryTp_12300;
    QString UprcTpCode_12300;
    QByteArray qt_temp_12300[6];
    CSPAQ12300InBlock1data data;
private:
    void run();

signals:

public slots:
};

#endif // TSELLFROM1833_H
