#include "tsitemoniter.h"
#include "webwiget.h"
extern webwiget *wk;

tsitemoniter::tsitemoniter()
{
    m_stopflag= true;
    urlsite="";
    tempsitecount = 0;
    connect(this,SIGNAL(loadurl()),wk,SLOT(tsitemoniterslot()));
}
void tsitemoniter::run(){
    while(m_stopflag){
<<<<<<< HEAD
        cycletime = mf->QLEsitecycletime->text();

        sleeptime = cycletime.toInt();
         //qDebug()<<QString("cycle time = %1,%2").arg(cycletime).arg(sleeptime);
=======

>>>>>>> parent of be5b78d... 546456546
        if(tempsitecount == wk->siteplaycount){
            tempsitecount=wk->siteplaycount;
            emit loadurl();
        }else{
            tempsitecount=wk->siteplaycount;
        }
        msleep(2000);
    }
}


