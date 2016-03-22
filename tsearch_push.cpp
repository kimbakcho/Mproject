#include "tsearch_push.h"
#include <xing.h>
#include <xingcom.h>
extern xingcom *xcom;
extern xing *x1;

Tsearch_push::Tsearch_push(Tsearch_res *recvth_temp)
{
    m_stopflag = PLAY;
    play_time.setHMS(19,41,10);
    play_end_time.setHMS(19,41,20);
    play_time_sec = QTime(0,0,0).secsTo(play_time);
    play_end_time_sec = QTime(0,0,0).secsTo(play_end_time);
    playtime_flag = PLAY;
    recvth = recvth_temp;

}
void Tsearch_push::run(){
    while(m_stopflag){
        time = QTime::currentTime();
        //qDebug()<<"QTime : "<<time.toString("hh:mm:s");
        time_sec = QTime(0,0,0).secsTo(time);
        if((time_sec == play_time_sec)&&(time_sec<=play_end_time_sec)&&(playtime_flag)){
            play_time_sec++;
            qDebug()<<"Tserch_push time : "<<time.toString("hh:mm:s");
            //xcom->com_1833_request();
            x1->ETK_RequestService("t1833","C:\\ConditionToApi.ADF");
            //recvth->resume();
            playtime_flag = STOP;
        }else{
            playtime_flag = PLAY;
        }
        msleep(100);
    }
}
