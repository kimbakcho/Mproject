#include "xing.h"
#include "mainframe.h"

extern mainframe *mf;

xing::xing(QWidget *parent) : QWidget(parent)
{
    htsip = "hts.ebestsec.co.kr";
    demoip = "demo.ebestsec.co.kr";
    serverport = 20001;
}
bool xing::init()
{
    if (QLibrary::isLibrary("xingAPI.dll")) {
      lib.setFileName("xingAPI.dll");
      lib.load();
      m_fpConnect = (FP_CONNECT)lib.resolve("ETK_Connect");
      m_fpIsConnected = (FP_ISCONNECTED)lib.resolve("ETK_IsConnected");
      m_fpDisconnect = (FP_DISCONNECT)lib.resolve("ETK_Disconnect");
      m_fpLogin = (FP_LOGIN)lib.resolve("ETK_Login");
      m_fpGetLastError = (FP_GETLASTERROR)lib.resolve("ETK_GetLastError");
      m_fpGetErrorMessage = (FP_GETERRORMESSAGE)lib.resolve("ETK_GetErrorMessage");
      m_fpRequest = (FP_REQUEST)lib.resolve("ETK_Request");
      m_fpAdviseRealData = (FP_ADVISEREALDATA)lib.resolve("ETK_AdviseRealData");
      m_fpUnadviseRealData = (FP_UNADVISEREALDATA)lib.resolve("ETK_UnadviseRealData");
      m_fpUnadviseWindow = (FP_UNADVISEWINDOW)lib.resolve("ETK_UnadviseWindow");
      m_fpReleaseRequestData = (FP_RELEASEREQUESTDATA)lib.resolve("ETK_ReleaseRequestData");
      m_fpGetAccountListCount = (FP_GETACCOUNTLISTCOUNT)lib.resolve("ETK_GetAccountListCount");
      m_fpGetAccountList = (FP_GETACCOUNTLIST)lib.resolve("ETK_GetAccountList");
      m_fpGetCommMedia = (FP_GETCOMMMEDIA)lib.resolve("ETK_GetCommMedia");
      m_fpGetETKMedia = (FP_GETETKMEDIA)lib.resolve("ETK_GetETKMedia");
      m_fpGetClientIP = (FP_GETCLIENTIP)lib.resolve("ETK_GetClientIP");
      m_fpGetServerName = (FP_GETSERVERNAME)lib.resolve("ETK_GetServerName");
      m_fpSetHeaderInfo = (FP_SETHEADERINFO)lib.resolve("ETK_SetHeaderInfo");
      m_fpReleaseMessageData = (FP_RELEASEMESSAGEDATA)lib.resolve("ETK_ReleaseMessageData");
      m_fpRequestService = (FP_REQUESTSERVICE)lib.resolve("ETK_RequestService" );
      if (!lib.isLoaded()) {
        qDebug() << lib.errorString();
        return false;
      }
    }

    //set handler
    set_windid((HWND)winId());

    return true;
}
void xing::set_windid(HWND data){
    this->xing_winid = data;
}
HWND xing::get_windid(){
    return this->xing_winid;
}
// this funtion is connect
bool xing::ETK_Connect(int type) {
    //type 1 is hts.ebestsec.co.kr connect ������
    //type 0 is demo.ebestsec.co.kr connect ��������
    if(type){
        serverip = htsip.toLocal8Bit();
    }else{
        serverip = demoip.toLocal8Bit();
    }
    char * serveripch = serverip.data();
    bool result_1 = m_fpConnect(get_windid(),serveripch,serverport,WM_USER,10000,-1);
    return result_1;
}
// this funtion is login
bool xing::ETK_Login(QByteArray Qid,QByteArray Qpasswd,QByteArray Qauthpasswd){
    char *id = Qid.data();
    char *pw = Qpasswd.data();
    char *aupw = Qauthpasswd.data();
    bool result_in = m_fpLogin(get_windid(),id,pw,aupw,0,0);
    if(result_in){
        qDebug()<<"COM login";
    }else {
        qDebug()<<"COM can't login";
    }
    return result_in;
}
// this funtion is request
int xing::ETK_Request(char * pszCode,void *lpData,int nDataSize,BOOL bNext,char * pszNextKey,int nTimeOut){
    int result_1;
    result_1 = m_fpRequest(get_windid(),pszCode,lpData,nDataSize,bNext,pszNextKey,nTimeOut);
    return result_1;
}
int xing::ETK_RequestService(char * pszCode, char *pszData){
    int result_1;
    result_1 = m_fpRequestService(get_windid(),pszCode,pszData);
    return result_1;
}

void xing::ETK_ReleaseMessageData(LPARAM lp){
    m_fpReleaseMessageData(lp);
    return ;
}
void xing::ETK_ReleaseRequestData(int nRequestID){

    m_fpReleaseRequestData(nRequestID);
    return ;
}


void xing::SetPacketData( char * psData, int nSize, char * pszSrc, int nType, int nDotPos ){

    //-----------------------------------------------------------------------
        // ���ڿ�
        if( nType == DATA_TYPE_STRING )
        {
            // ���� ����
            // ���� ���ڸ��� ' ' �� ä��

            // ����ũ�Ⱑ �� �����ͺ��� �۴ٸ� �����ʹ� ©���� �ϹǷ� �����߻�
            int nSrcLen = strlen( pszSrc );

            // ���� Space�� ä���
            FillMemory( psData, nSize, ' ' );

            // �տ����� �����͸� �ִ´�.
            // �������Ͱ� ũ�ٸ� �޺κ��� ������.
            CopyMemory( psData, pszSrc, min( nSize, nSrcLen ) );
        }

        //-----------------------------------------------------------------------
        // ����
        else if( nType == DATA_TYPE_LONG )
        {
            // ������ ����
            // ���� ���ڸ��� '0' ���� ä��

            // ����ũ�Ⱑ �� �����ͺ��� �۴ٸ� �����ʹ� ©���� �ϹǷ� �����߻�
            int nSrcLen = strlen( pszSrc );
            Q_ASSERT( nSize >= nSrcLen );

            // ���� 0 ���� ä���
            FillMemory( psData, nSize, '0' );

            // �ڿ������� �����͸� �ִ´�.
            if( nSize >= nSrcLen )
            {
                CopyMemory( psData+nSize-nSrcLen, pszSrc, nSrcLen );
            }
            // �������Ͱ� ũ�ٸ� ���������� �޺κ��� ������.
            else
            {
                CopyMemory( psData, pszSrc, nSize );
            }
        }
        //-----------------------------------------------------------------------
        // �Ǽ� : �Ҽ����� ���� �ʴ´�.
        else if( nType == DATA_TYPE_FLOAT )
        {
            // �Ҽ��� ��ġ�� �������� ����
            // �Ҽ����� ���� ������ �������� ���ڸ��� �Ҽ����� ���ڸ��� 0���� ä��
            int nSrcLen = strlen( pszSrc );
            // ���� 0 ���� ä���
            FillMemory( psData, nSize, '0' );
            // �������Ϳ��� �Ҽ����� ��ġ�� ã�Ƽ�
            // ���������� �������� ���̿� �Ҽ����� ���̸� ���Ѵ�.
            int nSrcIntLen;
            int nSrcDotLen;
            char * psz = strchr ( pszSrc, '.' );
            if( psz == NULL )		// �Ҽ��ΰ� ����.
            {
                nSrcIntLen = strlen( pszSrc );
                nSrcDotLen = 0;
            }
            else					// �Ҽ��ΰ� �ִ�.
            {
                nSrcIntLen = psz - pszSrc;
                nSrcDotLen = strlen( pszSrc ) - nSrcIntLen - 1;
            }
            // �����θ� �ִ´�.
            if( nSize-nDotPos >= nSrcIntLen )
            {
                CopyMemory( psData+nSize-nDotPos-nSrcIntLen, pszSrc, nSrcIntLen );
            }
            else
            {
                // ���������� ������ ���̰� �� �� ��� �������� ���ڸ��� �����ȴ�.
                Q_ASSERT( FALSE );
                CopyMemory( psData, pszSrc, nSize-nDotPos );
            }

            // �Ҽ��θ� �ִµ� ���������� �Ҽ��� ���̰� �� �� ��� �Ҽ����� ���ڸ��� �����ȴ�.
            Q_ASSERT( nDotPos >= nSrcDotLen );
            CopyMemory( psData+nSize-nDotPos, pszSrc + strlen( pszSrc ) - nSrcDotLen, min( nDotPos, nSrcDotLen ) );
        }
        //-----------------------------------------------------------------------
        // �Ǽ� : �Ҽ����� ����
        else if( nType == DATA_TYPE_FLOAT_DOT )
        {
            // �Ҽ��� ��ġ�� �������� ����
            // �Ҽ����� ���� ������ �������� ���ڸ��� �Ҽ����� ���ڸ��� 0���� ä��

            int nSrcLen = strlen( pszSrc );

            // ���� 0 ���� ä���
            FillMemory( psData, nSize, '0' );

            // �������Ϳ��� �Ҽ����� ��ġ�� ã�Ƽ�
            // ���������� �������� ���̿� �Ҽ����� ���̸� ���Ѵ�.
            int nSrcIntLen;
            int nSrcDotLen;
            char * psz = strchr ( pszSrc, '.' );
            if( psz == NULL )		// �Ҽ��ΰ� ����.
            {
                nSrcIntLen = strlen( pszSrc );
                nSrcDotLen = 0;
            }
            else					// �Ҽ��ΰ� �ִ�.
            {
                nSrcIntLen = psz - pszSrc;
                nSrcDotLen = strlen( pszSrc ) - nSrcIntLen - 1;
            }

            // �����θ� �ִ´�.
            if( nSize-nDotPos-1 >= nSrcIntLen )
            {
                CopyMemory( psData+nSize-nDotPos-nSrcIntLen-1, pszSrc, nSrcIntLen );
            }
            else
            {
                // ���������� ������ ���̰� �� �� ��� �������� ���ڸ��� �����ȴ�.
                Q_ASSERT( FALSE );
                CopyMemory( psData, pszSrc, nSize-nDotPos-1 );
            }
            // �Ҽ����� ��´�.
            psData[nSize-nDotPos-1] = '.';
            // �Ҽ��θ� �ִµ� ���������� �Ҽ��� ���̰� �� �� ��� �Ҽ����� ���ڸ��� �����ȴ�.
            Q_ASSERT( nDotPos >= nSrcDotLen );
            CopyMemory( psData+nSize-nDotPos, pszSrc + strlen( pszSrc ) - nSrcDotLen, min( nDotPos, nSrcDotLen ) );
        }
}

int xing::t1452_Request(BOOL bNext){
    t1452InBlock pckInBlock;
    int result_1;
    char szTrNo[] = "t1452";
    memset(&pckInBlock,' ',sizeof(pckInBlock));
    SetPacketData( pckInBlock.gubun    , sizeof( pckInBlock.gubun     ),"0", DATA_TYPE_STRING );	// [string,    1] ����
    SetPacketData( pckInBlock.jnilgubun, sizeof( pckInBlock.jnilgubun ),"1", DATA_TYPE_STRING );	// [string,    1] ���ϱ���
    SetPacketData( pckInBlock.sdiff    , sizeof( pckInBlock.sdiff     ),"", DATA_TYPE_LONG   );	// [long  ,    3] ���۵����
    SetPacketData( pckInBlock.ediff    , sizeof( pckInBlock.ediff     ),"", DATA_TYPE_LONG   );	// [long  ,    3] ��������
    SetPacketData( pckInBlock.jc_num   , sizeof( pckInBlock.jc_num    ),"", DATA_TYPE_LONG   );	// [long  ,   12] �������
    SetPacketData( pckInBlock.sprice   , sizeof( pckInBlock.sprice    ),"", DATA_TYPE_LONG   );	// [long  ,    8] ���۰���
    SetPacketData( pckInBlock.eprice   , sizeof( pckInBlock.eprice    ),"", DATA_TYPE_LONG   );	// [long  ,    8] ���ᰡ��
    SetPacketData( pckInBlock.volume   , sizeof( pckInBlock.volume    ),"", DATA_TYPE_LONG   );	// [long  ,   12] �ŷ���
    SetPacketData( pckInBlock.idx      , sizeof( pckInBlock.idx       ),"", DATA_TYPE_LONG   );	// [long  ,    4] IDX
    result_1= xing::ETK_Request(szTrNo,  // TR ��ȣ
                &pckInBlock,    	// InBlock ������
                sizeof( pckInBlock ), // InBlock ������ ũ��
                bNext,  // ������ȸ ����
                "", // ������ȸ Key
                30 // Timeout(��) : �ش� �ð�(��)���� �����Ͱ� ���� ������ Timeout�� �߻��Ѵ�. XM_TIMEOUT_DATA �޽����� �߻��Ѵ�.
             );
    return result_1;
}
void xing::CSPAT00600_Request(BOOL nNext,CSPAT00600data data){
    CSPAT00600InBlock1	pckInBlock;
    char			szTrNo[]		= "CSPAT00600";
    char			szNextKey[]		= "";

    memset(&pckInBlock,' ',sizeof(pckInBlock));


    SetPacketData( pckInBlock.AcntNo       , sizeof( pckInBlock.AcntNo        ), data.strAcntNo       , DATA_TYPE_STRING );		// ���¹�ȣ
    SetPacketData( pckInBlock.InptPwd      , sizeof( pckInBlock.InptPwd       ), data.strInptPwd      , DATA_TYPE_STRING );		// �Էº�й�ȣ
    SetPacketData( pckInBlock.IsuNo        , sizeof( pckInBlock.IsuNo         ), data.strIsuNo        , DATA_TYPE_STRING );		// �����ȣ
    SetPacketData( pckInBlock.OrdQty       , sizeof( pckInBlock.OrdQty        ), data.strOrdQty       , DATA_TYPE_LONG   );		// �ֹ�����
    SetPacketData( pckInBlock.OrdPrc       , sizeof( pckInBlock.OrdPrc        ), data.strOrdPrc       , DATA_TYPE_FLOAT_DOT, 2 );	// �ֹ���, Header Type�� B �� ��� Data Type�� �Ǽ��� �Ҽ����� �����ؾ� �Ѵ�.
    SetPacketData( pckInBlock.BnsTpCode    , sizeof( pckInBlock.BnsTpCode     ), data.strBnsTpCode    , DATA_TYPE_STRING );		// �Ÿű���
    SetPacketData( pckInBlock.OrdprcPtnCode, sizeof( pckInBlock.OrdprcPtnCode ), data.strOrdprcPtnCode, DATA_TYPE_STRING );		// ȣ�������ڵ�
    SetPacketData( pckInBlock.MgntrnCode   , sizeof( pckInBlock.MgntrnCode    ), data.strMgntrnCode   , DATA_TYPE_STRING );		// �ſ�ŷ��ڵ�
    SetPacketData( pckInBlock.LoanDt       , sizeof( pckInBlock.LoanDt        ), data.strLoanDt       , DATA_TYPE_STRING );		// ������
    SetPacketData( pckInBlock.OrdCndiTpCode, sizeof( pckInBlock.OrdCndiTpCode ), data.strOrdCndiTpCode, DATA_TYPE_STRING ); 		// �ֹ����Ǳ���

    int nRqID = ETK_Request(szTrNo,&pckInBlock,sizeof(pckInBlock),nNext,szNextKey,30);

    if(nRqID<0){
        qDebug()<<"CSPAT00600_Request ����";
    }

}


// it is furntion for Message handler
bool xing::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
   char * wresult;
   char * lresult;
   char cresult;
   char iresult;
   QString results_str;
    MSG* msg = reinterpret_cast<MSG*>(message);
    switch (msg->message) {
    case WM_USER+XM_LOGIN:
        wresult = (char *)msg->wParam;
        results_str = QString::fromLocal8Bit(wresult);
        qDebug()<<"XM_LOGIN"+results_str;
        if(results_str.compare("\"0000\"")){
            qDebug()<<kor("���ӵǾ����ϴ�.");

        }
        break;
     case WM_USER+XM_RECEIVE_DATA:
        cresult = msg->wParam;
        //results_str = QString::fromLocal8Bit(wresult);
        if(cresult == REQUEST_DATA){ //TR��Data���޾������߻� RECV_PACKET ��Memory �ּ�
            LPRECV_PACKET pRpData = (LPRECV_PACKET)msg->lParam;
            if(strcmp(pRpData->szBlockName,NAME_t1452OutBlock)==0){
                func_t1452outblock(pRpData);
            }else if( strcmp( pRpData->szBlockName, NAME_t1452OutBlock1 ) == 0 ){
                func_t1452outblock1(pRpData);
            }else if(strcmp( pRpData->szBlockName, NAME_t1833OutBlock)==0){
                func_t1833outblock(pRpData);
            }else if(strcmp( pRpData->szBlockName, NAME_t1833OutBlock1)==0){
                func_t1833outblock1(pRpData);
            }
        }else if(cresult == MESSAGE_DATA){ //Message���޾������߻� MSG_PACKET ��Memory �ּ�
            LPMSG_PACKET pMsg = (LPMSG_PACKET)msg->lParam;
            //bug config memory----------------------------------------
//            unsigned int src = (unsigned int)&(pMsg->nMsgLength)-2;
//            unsigned int dst = (unsigned int)&(pMsg->nMsgLength);
//            memmove((void *)dst,(void *)src,8);
            //---------------------------------------------------------
            //qDebug()<<QString("XM_RECEIVE_DATA case 2 lParam = %1").arg(lresult);
            ETK_ReleaseMessageData(msg->lParam);

        }else if(cresult == SYSTEM_ERROR_DATA){ //Error���߻� MSG_PACKET ��Memory �ּ�
            LPMSG_PACKET pMsg = (LPMSG_PACKET)msg->lParam;

            ETK_ReleaseMessageData(msg->lParam);
        }else if(cresult == RELEASE_DATA){ //TR�̳��������߻� ������Request ID���ǹ�
            //iresult = msg->lParam;
            ETK_ReleaseRequestData((int)msg->lParam);
            //qDebug()<<QString("XM_RECEIVE_DATA case 4 lParam = %1").arg(iresult);
        }
        break;
    default:
        break;
    }
    return false;
}
void xing::func_t1452outblock(LPRECV_PACKET pRpData){
    unsigned char * pRplpdata = pRpData->lpData;
    LPt1452OutBlock pOutBlock = (LPt1452OutBlock)pRplpdata;
}
void xing::func_t1452outblock1(LPRECV_PACKET pRpData){
    //xing api bug config memory----------------------------------------
       unsigned char * pRplpdata ;
       unsigned int src = (unsigned int)&(pRpData->lpData)-1;
       memcpy(&pRplpdata,(void *)src,4);
    //------------------------------------------------------------------
       LPt1452OutBlock1 pOutBlock = (LPt1452OutBlock1)pRplpdata;
       int	nCount = pRpData->nDataLength / sizeof( t1452OutBlock1 );		// Block Mode �ÿ� ��üũ�� / �ϳ��� Record ũ�� �� ������ ���Ѵ�.
       for( int i=0; i<nCount; i++ )
       {
           //������ ó��
           QString hname = QString::fromLocal8Bit(pOutBlock[i].hname,20);
           QString hprice = QString::fromLocal8Bit(pOutBlock[i].price,8);
           qDebug()<<kor("��� %1: %2 , %3").arg(i).arg(hname).arg(hprice);
       }
}
void xing::func_t1833outblock(LPRECV_PACKET pRpData){
    //xing api bug config memory----------------------------------------
       unsigned char * pRplpdata ;
       unsigned int src = (unsigned int)&(pRpData->lpData)-1;
       memcpy(&pRplpdata,(void *)src,4);
    //------------------------------------------------------------------

}
void xing::func_t1833outblock1(LPRECV_PACKET pRpData){
    //xing api bug config memory----------------------------------------
       unsigned char * pRplpdata ;
       unsigned int src = (unsigned int)&(pRpData->lpData)-1;
       memcpy(&pRplpdata,(void *)src,4);
    //------------------------------------------------------------------


       CSPAT00600data data;
       LPt1833OutBlock1 pOutBlock = (LPt1833OutBlock1)pRplpdata;

       QString str_shcode;
       char * ch_shcode;
       int temp_shcode;
       QByteArray qb_temp[10];

       int price;

       QString temp_serverip_1 = "demo.ebestsec.co.kr";
       QString temp_serverip_2;
       temp_serverip_2 = QString::fromLocal8Bit(serverip);

       QString ju_count;

       int real_price;
       int real_money;
       int total_ordqty;
       QString tpcode = "2";
       QString prcptncode = "00";
       QString mgntrncode = "000";
       QString loandt ="";
       QString ordcnditpcode="0";
       int	nCount = pRpData->nDataLength / sizeof( t1833OutBlock1 );		// Block Mode �ÿ� ��üũ�� / �ϳ��� Record ũ�� �� ������ ���Ѵ�.
       qDebug()<<QString("t1833 time = %1").arg(QTime::currentTime().toString("hh:mm:ss"));
       for( int i=0; i<nCount; i++ )
       {
           //������ ó��
           QString shcode = QString::fromLocal8Bit(pOutBlock[i].shcode,6);
           QString hname = QString::fromLocal8Bit(pOutBlock[i].hname,20);
           QString volume = QString::fromLocal8Bit(pOutBlock[i].volume,10);
           QString price = QString::fromLocal8Bit(pOutBlock[i].close,9);
           QString diff = QString::fromLocal8Bit(pOutBlock[i].diff,6);

           qb_temp[0] = shcode.toLocal8Bit();
           data.strIsuNo = qb_temp[0].data();

           qb_temp[1] = mf->QLInptPwd->text().toLocal8Bit();
           data.strInptPwd = qb_temp[1].data();

           qb_temp[2] = mf->QLLQAcntNo->text().toLocal8Bit();
           data.strAcntNo = qb_temp[2].data();

           //price qty
           real_price = price.toInt();
           real_money = mf->QLaccount->text().toInt();
           total_ordqty = real_money/real_price;
           ju_count.sprintf("%d",total_ordqty);
           qb_temp[3] = ju_count.toLocal8Bit();
           data.strOrdQty = qb_temp[3].data();

           //price
           qb_temp[4] = price.toLocal8Bit();
           data.strOrdPrc = qb_temp[4].data();

           //BnsTpCode
           qb_temp[5] = tpcode.toLocal8Bit();
           data.strBnsTpCode = qb_temp[5].data();

            //OrdprcPtnCode
           qb_temp[6] = prcptncode.toLocal8Bit();
           data.strBnsTpCode = qb_temp[6].data();

            //MgntrnCode
           qb_temp[7] = mgntrncode.toLocal8Bit();
           data.strMgntrnCode = qb_temp[7].data();

           //LoanDt
           qb_temp[8] = loandt.toLocal8Bit();
           data.strLoanDt = qb_temp[8].data();

            //OrdCndiTpCode
           qb_temp[9] = ordcnditpcode.toLocal8Bit();
           data.strOrdCndiTpCode = qb_temp[9].data();




//            //shcode
//           memset(data.strIsuNo,'0',sizeof(data.strIsuNo));
//           if(!QString::compare(temp_serverip_1, temp_serverip_2, Qt::CaseInsensitive)){
//            memset(data.strIsuNo+4,'A',1);
//            memset(data.strIsuNo+5,'+',1);
//           }
//           memcpy(data.strIsuNo+6,pOutBlock[i].shcode,6);
//           //acntno
//           qb_temp = mf->QLLQAcntNo->text().toLocal8Bit();
//           ch_temp = qb_temp.data();
//           length = mf->QLLQAcntNo->text().toLocal8Bit().length();
//           memset(data.strAcntNo,'0',sizeof(data.strAcntNo));
//           memcpy(data.strAcntNo+(sizeof(data.strAcntNo)-length),ch_temp,length);
//           //pw
//           qb_temp = mf->QLInptPwd->text().toLocal8Bit();
//           ch_temp = qb_temp.data();
//           length = mf->QLInptPwd->text().toLocal8Bit().length();
//           memset(data.strInptPwd,'0',sizeof(data.strInptPwd));
//           memcpy(data.strInptPwd+(sizeof(data.strInptPwd)-length),ch_temp,length);





           if(i == 0){
            CSPAT00600_Request(true,data);
           }
           qDebug()<<kor("t1833 ��� (%1): shcode = %2 , hname = %3,price = %4,volume = %5,diff =%6 ")
                     .arg(i).arg(shcode).arg(hname).arg(price).arg(volume).arg(diff);

       }
}

