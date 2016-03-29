#include "tpricemoniter.h"
#include <webwiget.h>
#include <xing.h>
extern webwiget *wk;
extern xing *x1;

tpricemoniter::tpricemoniter()
{
    m_stopflag = true;
}

void tpricemoniter::run(){
    while(m_stopflag){

        mapkeylist = wk->richdatamap.keys();
        int count = mapkeylist.count();
        for(int i=0;i<count;i++){
            QString key = mapkeylist.at(i);
            QByteArray qt_temp;
            t1101InBlockdata data;
            qt_temp = QString(key).toLocal8Bit();
            data.shcode = qt_temp.data();
            x1->t1101_Request(true,data);
            msleep(300);
        }
        if(count == 0){
            msleep(100);
        }
    }
}

