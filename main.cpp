#include "mainwindow.h"
#include "loginwiget.h"
#include "gherder.h"
#include <QApplication>
xing *x1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    x1 = new xing();
    if(x1->init()){
        if(x1->ETK_Connect(0)){

        }else{
            qDebug()<<kor("���� ����");
        }

    }else{
         qDebug()<<kor("�ʱ�ȭ ����");
    }
    Loginwiget w1;
    w1.show();

    return a.exec();
}
