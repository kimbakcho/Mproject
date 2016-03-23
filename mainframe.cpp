#include "mainframe.h"
#include "xingcom.h"
#include <xing.h>
extern xingcom *xcom;
extern xing *x1;
mainframe::mainframe(QWidget *parent) : QWidget(parent)
{
    btn1 = new QPushButton();
    btn2 = new QPushButton();
    btn1->setText(kor("항목 조회"));
    btn2->setText(kor("항목 결과"));
    hbox1 = new QHBoxLayout;
    label1 = new QLabel();
    label1->setText(kor("test값"));
    hbox2 = new QHBoxLayout;
    vbox1 = new QVBoxLayout;
    trecv = new Tsearch_res();
    trecv->start();
    tpush = new Tsearch_push(trecv);

    //connect(btn2,SIGNAL(clicked(bool)),xcom,SLOT(com_clicked1()));
    hbox1->addWidget(btn1);
    hbox1->addWidget(btn2);
    hbox2->addWidget(label1);
    vbox1->addLayout(hbox1);
    vbox1->addLayout(hbox2);
    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(t1833_request()));
    //connect(btn2,SIGNAL(clicked(bool)),x1,SLOT(com_1833_result()));
    //time play to com_1833_request
    tpush->start();
    setLayout(vbox1);
}
void mainframe::t1833_request(){
    x1->ETK_RequestService("t1833","C:\\ConditionToApi.ADF");
}

void mainframe::init(){

}
