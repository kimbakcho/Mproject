#include "mainframe.h"

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

    //connect(btn2,SIGNAL(clicked(bool)),xcom,SLOT(com_clicked1()));
    hbox1->addWidget(btn1);
    hbox1->addWidget(btn2);
    hbox2->addWidget(label1);
    vbox1->addLayout(hbox1);
    vbox1->addLayout(hbox2);


    connect(btn1,SIGNAL(clicked(bool)),xcom,SLOT(com_1833_request()));
    connect(btn2,SIGNAL(clicked(bool)),xcom,SLOT(com_1833_result()));
    setLayout(vbox1);

}
void mainframe::setlabel1(QString str){
    label1->setText(str);
}

void mainframe::testfuntion(){
    x1->t1452_Request(true);
}

void mainframe::init(){

}
