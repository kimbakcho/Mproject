#include "mainframe.h"

mainframe::mainframe(QWidget *parent) : QWidget(parent)
{
    btn1 = new QPushButton();
    btn2 = new QPushButton();
    btn1->setText("push");
    btn2->setText("push2");
    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(testfuntion()));
    connect(btn2,SIGNAL(clicked(bool)),xcom,SLOT(com_clicked1()));
    hbox.addWidget(btn1);
    hbox.addWidget(btn2);

    setLayout(&hbox);

}
void mainframe::testfuntion(){
    x1->t1452_Request(true);
    xcom->com_clicked();
}

void mainframe::init(){

}
