#include "mainframe.h"

mainframe::mainframe(QWidget *parent) : QWidget(parent)
{
    btn1 = new QPushButton();
    btn2 = new QPushButton();
    btn1->setText(kor("항목 조회"));
    btn2->setText(kor("항목 결과"));

    //connect(btn2,SIGNAL(clicked(bool)),xcom,SLOT(com_clicked1()));
    hbox.addWidget(btn1);
    hbox.addWidget(btn2);
    connect(btn1,SIGNAL(clicked(bool)),xcom,SLOT(com_1833_request()));
    connect(btn2,SIGNAL(clicked(bool)),xcom,SLOT(com_1833_result()));
    setLayout(&hbox);

}
void mainframe::testfuntion(){
    x1->t1452_Request(true);
}

void mainframe::init(){

}
