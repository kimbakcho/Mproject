#include "xingcom.h"
#include <mainframe.h>
extern mainframe *mf;
xingcom::xingcom(QObject *parent) : QObject(parent)
{
    htsip = "hts.ebestsec.co.kr";
    demoip = "demo.ebestsec.co.kr";
    serverport = 20001;
    XA_Session = new com1_axobj();
    XA_Session->setControl("XA_Session.XASession");
    XA_DataSet = new com1_axobj();
    XA_DataSet->setControl("XA_DataSet.XAQuery");
    //connect server
    com_connect(0);

}
bool xingcom::com_connect(int type){
    bool result_in;
    if(type){
        serverip = htsip.toLocal8Bit();
    }else{
        serverip = demoip.toLocal8Bit();
    }
    char * serveripch = serverip.data();
    result_in= XA_Session->dynamicCall("ConnectServer(char *,int)",serveripch,serverport).toBool();
    return result_in;
}

bool xingcom::com_login(QByteArray Qid,QByteArray Qpasswd,QByteArray Qauthpasswd){
    bool result_in;
    char *id = Qid.data();
    char *pw = Qpasswd.data();
    char *aupw = Qauthpasswd.data();
    result_in = XA_Session->dynamicCall("Login(char *,char *,char *,int,bool)",id,pw,aupw,0,false).toBool();
    if(result_in){
        qDebug()<<"COM login";
    }else {
        qDebug()<<"COM can't login";
    }
    return result_in;
}
bool xingcom::com_1833_request(){
    bool result_in;
    int result_int;
    result_in = XA_DataSet->dynamicCall("LoadFromResFile(char *)","\Res\\t1833.res").toBool();
    result_int = XA_DataSet->dynamicCall("RequestService(char *,char *)","t1833","C:\\ConditionToApi.ADF").toInt();
    return result_in;
}

int xingcom::com_1833_result(){
    int result_int;
    //get count
    result_int = XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock","JongCnt",0).toInt();
    qDebug()<<QString("com_1833_result_JongCnt : %1").arg(result_int);
    QString serarch_str;
    QString shcode;
    QString hname;
    QString sign;
    QString signcnt;
    QString close;
    QString change;
    QString diff;
    QString volume;
    QString choice_shcode;
    QString choice_hname;
    QString choice_diff;
    QString choice_close;

    int volume_temp = 0;
    for(int i=0;i<result_int;i++){
        shcode = XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","shcode",i).toString();
        hname = XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","hname",i).toString();
        sign = XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","sign",i).toString();
        signcnt = XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","signcnt",i).toString();
        close = XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","close",i).toString();
        diff =  XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","diff",i).toString();
        change = XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","change",i).toString();
        volume =XA_DataSet->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","volume",i).toString();
        //qDebug()<<QString("1833_info hname = %1,diff = %2,volume = %3,price=%4").arg(hname).arg(diff).arg(volume).arg(close);
        if(volume_temp<volume.toInt()){
            choice_hname = hname;
            choice_diff = diff;
            choice_close = close;
            volume_temp = volume.toInt();
        }
    }
    QString result_str = QString("1833_reuslt hname = %1,diff = %2,volume = %3,price=%4").arg(choice_hname).arg(choice_diff).arg(volume_temp).arg(choice_close);
    qDebug()<<result_str;
    mf->setlabel1(result_str);
    return result_int;
}

void xingcom::XASession_Login_Login(QString str){
    qDebug()<<QString::fromLocal8Bit("xA Ãâ·Â1 : %1").arg(str);

}

