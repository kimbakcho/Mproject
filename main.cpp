#include "loginwiget.h"
#include "gherder.h"
#include "xingcom.h"
#include "tsearch_push.h"
#include <QApplication>
#include <webwiget.h>
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



    //xcom = new xingcom();

    mf = new mainframe();

    w1.show();


    wk = new webwiget();
    wk->show();




    return a.exec();
}
