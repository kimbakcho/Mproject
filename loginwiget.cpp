#include "loginwiget.h"

Loginwiget::Loginwiget(QWidget *parent) : QWidget(parent)
{

    glay_1 = new QGridLayout();
    lbid = new QLabel("IP");
    leid = new QLineEdit();
    pbjoin = new QPushButton(kor("立加"));
    glay_1->addWidget(lbid,0,0);
    glay_1->addWidget(leid,0,1);
    glay_1->addWidget(pbjoin,0,2);
    lbpw = new QLabel("PW");
    lepw = new QLineEdit();
    glay_1->addWidget(lbpw,1,0);
    glay_1->addWidget(lepw,1,1);
    lbaupw = new QLabel(kor("牢刘"));
    leaupw = new QLineEdit();
    glay_1->addWidget(lbaupw,2,0);
    glay_1->addWidget(leaupw,2,1);
    lepw->setEchoMode(QLineEdit::Password);
    leaupw->setEchoMode(QLineEdit::Password);
    connect(pbjoin,SIGNAL(clicked(bool)),this,SLOT(loginfuntion()));
    setLayout(glay_1);
}
void Loginwiget::loginfuntion(){
    if(result1){
        qDebug()<<kor("立加");
        this->setVisible(false);
    }else {
        qDebug()<<kor("立加救凳");
    }
}
