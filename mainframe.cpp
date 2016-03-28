#include "mainframe.h"
#include "xingcom.h"
#include <xing.h>
#include <webwiget.h>
extern xingcom *xcom;
extern xing *x1;
extern webwiget *wk;
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
    gbox1 = new QGridLayout;

    QAcntNo = new QLabel(kor("AcntNo"));
    QInptPwd = new QLabel(kor("InptPwd"));
    QIsuNo = new QLabel(kor("IsuNo"));
    QOrdQty = new QLabel(kor("OrdQty"));
    QOrdPrc = new QLabel(kor("OrdPrc"));
    QBnsTpCode = new QLabel(kor("BnsTpCode"));
    QOrdprcPtnCode = new QLabel(kor("OrdprcPtnCode"));
    QMgntrnCode = new QLabel(kor("MgntrnCode"));
    QOrdCndiTpCode = new QLabel(kor("OrdCndiTpCode"));
    QLLQAcntNo = new QLineEdit();
    QLInptPwd = new QLineEdit();
    QLIsuNo = new QLineEdit();
    QLOrdQty = new QLineEdit();
    QLOrdPrc = new QLineEdit();
    QLBnsTpCode = new QLineEdit();
    QLOrdprcPtnCode = new QLineEdit();
    QLMgntrnCode = new QLineEdit();
    QLOrdCndiTpCode = new QLineEdit();
    QLInptPwd->setEchoMode(QLineEdit::Password);

    Qaccount = new QLabel(kor("account price"));
    QLaccount = new QLineEdit();

    Qusebuy = new QCheckBox();
    QLusebuy = new QLabel(kor("auto use buy"));

    functiontestbtn1 = new QPushButton("test");
    tsf1833 = new TSellfrom1833();

    rich_address = new QLineEdit();
    rich_label = new QLabel("rich_address");

//--read---
    QSettings settings1("config.ini",QSettings::IniFormat);
    settings1.beginGroup("ancnt");
    QLLQAcntNo->setText(settings1.value("AcntNo").toByteArray());
    QLInptPwd->setText(settings1.value("InptPwd").toByteArray());
    QLaccount->setText(settings1.value("price").toByteArray());
    Qusebuy->setChecked(settings1.value("usebuy").toBool());
    settings1.endGroup();
//---------
    gbox1->addWidget(QAcntNo,0,0);
    gbox1->addWidget(QLLQAcntNo,0,1);

    gbox1->addWidget(QInptPwd,1,0);
    gbox1->addWidget(QLInptPwd,1,1);
    gbox1->addWidget(Qaccount,2,0);
    gbox1->addWidget(QLaccount,2,1);
    gbox1->addWidget(QLusebuy,3,0);
    gbox1->addWidget(Qusebuy,3,1);
    gbox1->addWidget(functiontestbtn1,4,0);
    gbox1->addWidget(rich_label,5,0);
    gbox1->addWidget(rich_address,5,1);

//    gbox1->addWidget(QIsuNo,2,0);
//    gbox1->addWidget(QLIsuNo,2,1);

//    gbox1->addWidget(QOrdQty,3,0);
//    gbox1->addWidget(QLOrdQty,3,1);

//    gbox1->addWidget(QOrdPrc,4,0);
//    gbox1->addWidget(QLOrdPrc,4,1);

//    gbox1->addWidget(QBnsTpCode,5,0);
//    gbox1->addWidget(QLBnsTpCode,5,1);

//    gbox1->addWidget(QOrdprcPtnCode,6,0);
//    gbox1->addWidget(QLOrdprcPtnCode,6,1);

//    gbox1->addWidget(QMgntrnCode,7,0);
//    gbox1->addWidget(QLMgntrnCode,7,1);

//    gbox1->addWidget(QOrdCndiTpCode,8,0);
//    gbox1->addWidget(QLOrdCndiTpCode,8,1);

    hbox1->addWidget(btn1);
    hbox1->addWidget(btn2);
    hbox2->addWidget(label1);
    vbox1->addLayout(hbox1);
    vbox1->addLayout(hbox2);
    vbox1->addLayout(gbox1);


    //trecv = new Tsearch_res();
    //trecv->start();
    //tpush = new Tsearch_push(trecv);

    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(t1833_request()));

    connect(QLLQAcntNo,SIGNAL(textEdited(QString)),this,SLOT(QLLQAcntNo_change(QString)));
    connect(QLInptPwd,SIGNAL(textEdited(QString)),this,SLOT(QLInptPwd_change(QString)));
    connect(QLaccount,SIGNAL(textEdited(QString)),this,SLOT(QLaccount_change(QString)));
    connect(Qusebuy,SIGNAL(toggled(bool)),this,SLOT(Qusebuy_change(bool)));
    connect(functiontestbtn1,SIGNAL(clicked(bool)),this,SLOT(functiontestbtn1_push()));
    //connect(btn2,SIGNAL(clicked(bool)),x1,SLOT(com_1833_result()));
    //time play to com_1833_request
    //tpush->start();
    setLayout(vbox1);
}
void mainframe::t1833_request(){
    x1->ETK_RequestService((char *)"t1833",(char *)"C:\\ConditionToApi.ADF");
}

void mainframe::init(){

}
void mainframe::QLLQAcntNo_change(QString str){
    //write setting--------------------------------------------
    QSettings settings2("config.ini",QSettings::IniFormat);
    settings2.beginGroup("ancnt");
    settings2.setValue("AcntNo",str.toLocal8Bit());
    settings2.endGroup();
    //---------------------------------------------------------
}
void mainframe::QLInptPwd_change(QString str){
    //write setting--------------------------------------------
    QSettings settings2("config.ini",QSettings::IniFormat);
    settings2.beginGroup("ancnt");
    settings2.setValue("InptPwd",str.toLocal8Bit());
    settings2.endGroup();
    //---------------------------------------------------------
}
void mainframe::QLaccount_change(QString str){
    //write setting--------------------------------------------
    QSettings settings2("config.ini",QSettings::IniFormat);
    settings2.beginGroup("ancnt");
    settings2.setValue("price",str.toLocal8Bit());
    settings2.endGroup();
    //---------------------------------------------------------
}
void mainframe::Qusebuy_change(bool data){
    //write setting--------------------------------------------
    QSettings settings2("config.ini",QSettings::IniFormat);
    settings2.beginGroup("ancnt");
    settings2.setValue("usebuy",data);
    settings2.endGroup();
    //---------------------------------------------------------

}
void mainframe::functiontestbtn1_push(){
//    QByteArray qt_temp[10];
//    CSPAQ13700InBlock1data data;
//    qt_temp[0] = QString("55501003267").toLocal8Bit();
//    data.AcntNo = qt_temp[0].data();
//    qt_temp[1] = QString("0000").toLocal8Bit();
//    data.InptPwd = qt_temp[1].data();
//    qt_temp[2] = QString("00").toLocal8Bit();
//    data.OrdMktCode = qt_temp[2].data();
//    qt_temp[3] = QString("2").toLocal8Bit();
//    data.BnsTpCode = qt_temp[3].data();
//    qt_temp[4] = QString("").toLocal8Bit();
//    data.IsuNo = qt_temp[4].data();
//    qt_temp[5] = QString("").toLocal8Bit();
//    data.ExecYn = qt_temp[5].data();
//    qt_temp[6] = QString("").toLocal8Bit();
//    data.OrdDt = qt_temp[6].data();
//    qt_temp[7] = QString("").toLocal8Bit();
//    data.SrtOrdNo2 = qt_temp[7].data();
//    qt_temp[8] = QString("0").toLocal8Bit();
//    data.BkseqTpCode = qt_temp[8].data();
//    qt_temp[9] = QString("00").toLocal8Bit();
//    data.OrdPtnCode = qt_temp[9].data();
//    x1->CSPAQ13700_Request(true,data);

    //tsf1833->start();
    wk->getparser();


}
