#include "tsearch_res.h"
#include "xingcom.h"
extern xingcom *xcom;
Tsearch_res::Tsearch_res()
{
    m_mflag = PLAY;
    m_recvmflag = true;
}
void Tsearch_res::run(){
    while(m_mflag){
        m_mutex.lock();
            m_recvmflag = true;
            m_waitcondition.wait(&m_mutex);
            while(m_recvmflag){
                //recv_result = xcom->com_1833_result();
                if(recv_result>0){
                    m_recvmflag = false;
                }else {
                    m_recvmflag = true;
                }
                msleep(100);
            }
        m_mutex.unlock();
    }
}
void Tsearch_res::resume(){
    m_mutex.lock();
    m_waitcondition.wakeAll();
    m_mutex.unlock();
}
