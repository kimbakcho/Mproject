#include "loginwiget.h"


Loginwiget::Loginwiget(QWidget *parent) : QWidget(parent)
{

    glay_1 = new QGridLayout();
    lbid = new QLabel("IP");
    leid = new QLineEdit();
    pbjoin = new QPushButton(kor("접속"));
    glay_1->addWidget(lbid,0,0);
    glay_1->addWidget(leid,0,1);
    glay_1->addWidget(pbjoin,0,2);
    lbpw = new QLabel("PW");
    lepw = new QLineEdit();
    glay_1->addWidget(lbpw,1,0);
    glay_1->addWidget(lepw,1,1);
    lbaupw = new QLabel(kor("인증"));
    leaupw = new QLineEdit();
    glay_1->addWidget(lbaupw,2,0);
    glay_1->addWidget(leaupw,2,1);
    lepw->setEchoMode(QLineEdit::Password);
    leaupw->setEchoMode(QLineEdit::Password);
    connect(pbjoin,SIGNAL(clicked(bool)),this,SLOT(loginfuntion()));
    setLayout(glay_1);
    //read setting-----------------------------------------
     QSettings settings("config.ini",QSettings::IniFormat);
    settings.beginGroup("setlogin");
    leid->setText(settings.value("id").toByteArray());
    lepw->setText(settings.value("pw").toByteArray());
    leaupw->setText(settings.value("aupw").toByteArray());
    settings.endGroup();
    //-----------------------------------------------------

}
void Loginwiget::loginfuntion(){
    //dll login
    bool result_1 = x1->ETK_Login(leid->text().toLocal8Bit(),lepw->text().toLocal8Bit(),leaupw->text().toLocal8Bit());
    //com login
    xcom->com_login(leid->text().toLocal8Bit(),lepw->text().toLocal8Bit(),leaupw->text().toLocal8Bit());
    if(result_1){
        //write setting--------------------------------------------
        QSettings settings("config.ini",QSettings::IniFormat);
        settings.beginGroup("setlogin");
        settings.setValue("id",leid->text().toLocal8Bit());
        settings.setValue("pw",lepw->text().toLocal8Bit());
        settings.setValue("aupw",leaupw->text().toLocal8Bit());
        settings.endGroup();
        //---------------------------------------------------------
        qDebug()<<"join";

        mf->show();


        close();
    }else {
        qDebug()<<"false join";
    }
}
