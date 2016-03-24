#include "tsellfrom1833.h"

#include "mainframe.h"
extern xing *x1;
extern mainframe *mf;
TSellfrom1833::TSellfrom1833(){
    m_stopflag = true;

}
void TSellfrom1833::run(){
    while(m_stopflag){
        if(x1->vector_1833.size()>0){

            AcntNo_12300 = mf->QLLQAcntNo->text();
            Pwd_12300 = mf->QLInptPwd->text();
            BalCreTp_12300 = QString("0"); //0 전체 1 현물
            CmsnAppTpCode_12300 = QString("0");
            D2balBaseQryTp_12300 = QString("0");
            UprcTpCode_12300 = QString("0");

            qt_temp_12300[0] = AcntNo_12300.toLocal8Bit();
            data.AcntNo = qt_temp_12300[0].data();

            qt_temp_12300[1] = Pwd_12300.toLocal8Bit();
            data.Pwd = qt_temp_12300[1].data();

            qt_temp_12300[2] = BalCreTp_12300.toLocal8Bit();
            data.BalCreTp = qt_temp_12300[2].data();

            qt_temp_12300[3] = CmsnAppTpCode_12300.toLocal8Bit();
            data.CmsnAppTpCode = qt_temp_12300[3].data();

            qt_temp_12300[4] = D2balBaseQryTp_12300.toLocal8Bit();
            data.D2balBaseQryTp = qt_temp_12300[4].data();

            qt_temp_12300[5] = UprcTpCode_12300.toLocal8Bit();
            data.UprcTpCode = qt_temp_12300[5].data();

            x1->CSPAQ12300_Request(true,data);

        }else {

        }
        msleep(2000);

    }
}

