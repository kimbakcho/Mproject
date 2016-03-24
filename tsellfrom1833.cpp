#include "tsellfrom1833.h"
#include "xing.h"
extern xing *x1;
TSellfrom1833::TSellfrom1833(){
    m_stopflag = true;

}
void TSellfrom1833::run(){
    while(m_stopflag){
        if(x1->vector_1833.size()>0){
            data_1833 *d_1833;

        }else {
            msleep(10);
        }

    }
}

