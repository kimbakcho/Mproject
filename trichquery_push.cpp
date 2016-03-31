#include "trichquery_push.h"
#include "webwiget.h"
extern webwiget *wk;
trichquery_push::trichquery_push()
{
    m_stopflag = true;
    play_time.setHMS(8,55,10);
    play_end_time.setHMS(15,30,00);
    play_time_sec = QTime(0,0,0).secsTo(play_time);
    play_end_time_sec = QTime(0,0,0).secsTo(play_end_time);
    playtime_flag = true;
    connect(this,SIGNAL(palyonsignal()),wk,SLOT(autostep()));
}
void trichquery_push::run(){
    while(m_stopflag){
        time = QTime::currentTime();
        time_sec = QTime(0,0,0).secsTo(time);
        if((time_sec == play_time_sec) && playtime_flag){

            qDebug()<<"trichquery_push time : "<<time.toString("hh:mm:ss");
            emit palyonsignal();
            playtime_flag =false;
        }else if(time_sec != play_time_sec){
            playtime_flag =true;
        }
        msleep(100);
    }
}

