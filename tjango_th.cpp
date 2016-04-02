#include "tjango_th.h"
#include "mainframe.h"
#include "xing.h"

extern xing *x1;
extern mainframe *mf;



tjango_th::tjango_th()
{
    m_stopflag = true;
    play_time.setHMS(9,00,00);
    play_end_time.setHMS(18,00,00);
    play_time_sec = QTime(0,0,0).secsTo(play_time);
    play_end_time_sec = QTime(0,0,0).secsTo(play_end_time);
    playtime_flag = true;
    //this->mf = mf1;
    //connect(this,SIGNAL(t0424signal()),mf,SLOT(t0424_slot()));
}

void tjango_th::run(){
    while(m_stopflag){
        time = QTime::currentTime();
        time_sec = QTime(0,0,0).secsTo(time);
        if((time_sec >= play_time_sec) && (time_sec<play_end_time_sec)&&playtime_flag ){
            QByteArray qt_temp[10];
            t0424InBlockdata data;
            qt_temp[0] =  mf->QLLQAcntNo->text().toLocal8Bit();
            data.accno = qt_temp[0].data();
            qt_temp[1] = mf->QLInptPwd->text().toLocal8Bit();
            data.passwd = qt_temp[1].data();
            qt_temp[2] = QString("").toLocal8Bit();
            data.charge = qt_temp[2].data();
            qt_temp[3] = QString("").toLocal8Bit();
            data.cts_expcode = qt_temp[3].data();
            qt_temp[4] = QString("").toLocal8Bit();
            data.dangb = qt_temp[4].data();
            qt_temp[5] = QString("").toLocal8Bit();
            data.prcgb = qt_temp[5].data();
            qt_temp[6] = QString("").toLocal8Bit();
            data.chegb = qt_temp[6].data();
            //qDebug()<<"tjango_th run";
            x1->t0424_Request(true,data);
           }
        if((time_sec >= play_time_sec) && (time_sec<play_end_time_sec)&&playtime_flag ){
            QByteArray qt_temp_0425[10];
            t0425InBlockdata data_0425;
            qt_temp_0425[0] =  mf->QLLQAcntNo->text().toLocal8Bit();
            data_0425.accno = qt_temp_0425[0].data();
            qt_temp_0425[1] = mf->QLInptPwd->text().toLocal8Bit();
            data_0425.passwd = qt_temp_0425[1].data();
            qt_temp_0425[2] = QString("").toLocal8Bit();
            data_0425.expcode = qt_temp_0425[2].data();
            qt_temp_0425[3] = QString("2").toLocal8Bit();
            data_0425.chegb = qt_temp_0425[3].data();
            qt_temp_0425[4] = QString("0").toLocal8Bit();
            data_0425.medosu = qt_temp_0425[4].data();
            qt_temp_0425[5] = QString("1").toLocal8Bit();
            data_0425.sortgb = qt_temp_0425[5].data();
            qt_temp_0425[6] = QString(" ").toLocal8Bit();
            data_0425.cts_ordno = qt_temp_0425[6].data();
            //qDebug()<<"tjango_th run";
            x1->t0425_Request(true,data_0425);
           }
           msleep(1500);
        }
}
