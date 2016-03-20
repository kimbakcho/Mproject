#include "com1_axobj.h"

com1_axobj::com1_axobj()
{

}

void com1_axobj::connectNotify(const QMetaMethod & signal){
    qDebug()<<"signel";

}
bool com1_axobj::event(QEvent * e){
     qDebug()<<"signel";
     return true;
}
bool com1_axobj::doVerb(const QString & verb){
    qDebug()<<"signel";
    return true;
}

