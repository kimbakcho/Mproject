#include "mainwindow.h"
#include "loginwiget.h"
#include "xing.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Loginwiget w1;
    w1.show();
    xing x1;
    x1.init();
//    if(x1.ETK_Connect(0)){
//        qDebug()<<"true";
//    }else{
//        qDebug()<<"false";
//    }



//------------------------------------------------------------------------------
// Loginwiget xingapi.init()->
//------------------------------------------------------------------------------


    return a.exec();
}
