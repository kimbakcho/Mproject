#include "loginwiget.h"

Loginwiget::Loginwiget(QWidget *parent) : QWidget(parent)
{
    if (QLibrary::isLibrary("xingAPI.dll")) {
      QLibrary lib("xingAPI.dll");
      //lib.load();
      m_fpConnect = (FP_CONNECT)lib.resolve("ETK_Connect");
      m_fpLogin = (FP_LOGIN)lib.resolve("ETK_Login");
      if (!lib.isLoaded()) {
        qDebug() << lib.errorString();
      }
    }

    hWnd1 = (HWND)winId();
    QString str ="demo.ebestsec.co.kr";
    QByteArray lp2 = str.toLocal8Bit();
    BOOL result = m_fpConnect(hWnd1,lp2, 20001,WM_USER,10000,-1);
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
}
void Loginwiget::loginfuntion(){
    qDebug()<<"clicked";
    QByteArray qbaid = leid->text().toLocal8Bit();
    QByteArray qbapw = lepw->text().toLocal8Bit();
    QByteArray qbaaupw = leaupw->text().toLocal8Bit();
    BOOL result1 = m_fpLogin(hWnd1,qbaid,qbapw,qbaaupw,0,0);
    if(result1){
        qDebug()<<kor("접속");
        this->setVisible(false);
    }else {
        qDebug()<<kor("접속안됨");
    }
}
//----------------------funtion_messagereceve----------------------------
//Main message 받는곳
//-----------------------------------------------------------------------
bool Loginwiget::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    switch (msg->message) {
    case WM_USER+XM_LOGIN:

        break;
    default:
        break;
    }
    if( ){
        QByteArray data = (char *)msg->wParam;
        qDebug() << QString("message1 %1 wpram1 %2").arg(msg->message).arg(QString::fromLocal8Bit(data));
    }
    return false;
}
