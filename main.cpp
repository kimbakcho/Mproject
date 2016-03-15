#include "mainwindow.h"
#include "loginwiget.h"
#include "xing.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Loginwiget w1;
    w1.show();
    xing *x1 = new xing();
    x1->init();
    //x1->show();




//------------------------------------------------------------------------------
// Loginwiget xingapi.init()->
//------------------------------------------------------------------------------


    return a.exec();
}
