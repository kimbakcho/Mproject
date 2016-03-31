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

        if(tempsitecount == wk->siteplaycount){
            tempsitecount=wk->siteplaycount;
            emit loadurl();
        }else{
            tempsitecount=wk->siteplaycount;
        }
        msleep(2000);
    }
}


