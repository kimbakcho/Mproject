#include "xingcom.h"

xingcom::xingcom(QObject *parent) : QObject(parent)
{

    obj = new com1_axobj();
    obj->setControl("XA_Session.XASession");
    obj1 = new com1_axobj();
    obj1->setControl("XA_DataSet.XAQuery");
    bool result_1;
    result_1 = obj->dynamicCall("ConnectServer(char *,int)","demo.ebestsec.co.kr",20001).toBool();
      if(result_1){
            qDebug()<<"true";
        }else {
            qDebug()<<"false";
        }
    result_1 = obj->dynamicCall("Login(char *,char *,char *,int,bool)","vngkgk62","super624","123",0,false).toBool();
      if(result_1){
          qDebug()<<"true";
      }else {
          qDebug()<<"false";
      }


    int result_2;
   // result_2 = obj1->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock","JongCnt",0).toInt();
}
void xingcom::com_clicked(){
    //obj1->setProperty("ResFileName","\\Res\\t1101.res");
    QByteArray sstr_1;
    QString sttrc;
    int result3;
    bool result_1;
    //sstr_1 = obj1->property("ResFileName").toByteArray();
    result_1 = obj1->dynamicCall("LoadFromResFile(char *)","\Res\\t1833.res").toBool();
    //result_1 = obj1->dynamicCall("LoadFromResFile(char *)","\Res\\t1101.res").toBool();
    result3 = obj1->dynamicCall("RequestService(char *,char *)","t1833","C:\\ConditionToApi.ADF").toInt();

    //result3 = obj1->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock","JongCnt",0).toInt();
    if(result_1){
        qDebug()<<"true";
    }else {
        qDebug()<<"false";
    }
}
void xingcom::com_clicked1(){
    int result3;
    int result2;
    result3 = obj1->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock","JongCnt",0).toInt();
    result3 = obj1->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock","JongCnt",0).toInt();
    qDebug()<<QString("GetFieldData : %1").arg(result3);
    QByteArray str;
    QString str2;
    for(int i=0;i<result3;i++){
        str2 = obj1->dynamicCall("GetFieldData(char *,char *,int)","t1833OutBlock1","hname",i).toString();
        //str2 = QString::fromLocal8Bit(str);
        qDebug()<<QString("GetFieldData : %1").arg(str2);
    }
}

void xingcom::XASession_Login_Login(QString str){
    qDebug()<<QString::fromLocal8Bit("xA Ãâ·Â1 : %1").arg(str);

}

