#include "tsitemoniter.h"
#include "webwiget.h"
#include "mainframe.h"

extern webwiget *wk;
extern mainframe *mf;

tsitemoniter::tsitemoniter()
{
    m_stopflag= true;
    urlsite="";
    tempsitecount = 0;
    sleeptime = 3000;
    connect(this,SIGNAL(loadurl()),wk,SLOT(tsitemoniterslot()));
}
void tsitemoniter::run(){
    while(m_stopflag){
        cycletime = mf->QLEsitecycletime->text();
        sleeptime = cycletime.toInt();
        if(tempsitecount == wk->siteplaycount){
            tempsitecount=wk->siteplaycount;
            emit loadurl();
        }else{
            tempsitecount=wk->siteplaycount;
        }
        msleep(sleeptime);
    }
}


