#include "loginwiget.h"
#include "gherder.h"
#include "xingcom.h"
#include "tsearch_push.h"
#include <QApplication>
#include <webwiget.h>
#include "tjango_th.h"
#include "tpricemoniter.h"
#include "tsitemoniter.h"
xing *x1;
xingcom *xcom;
mainframe *mf;
webwiget *wk;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    x1 = new xing();
    if(x1->init()){
        if(x1->ETK_Connect(0)){

        }else{
            qDebug()<<kor("접속 실패");
        }

    }else{
         qDebug()<<kor("초기화 실패");
    }

    Loginwiget w1;

    wk = new webwiget();

    x1->wk=wk;

    mf = new mainframe();



    //xcom = new xingcom();
    wk->show();



    w1.show();

    tjango_th *jango_th;
    jango_th = new tjango_th();
    jango_th->start();

    tpricemoniter *pricemoniter_th;
    pricemoniter_th = new tpricemoniter();
    pricemoniter_th->start();

    tsitemoniter *sitemoniter;
    sitemoniter = new tsitemoniter();
    sitemoniter->start();

    return a.exec();
}
