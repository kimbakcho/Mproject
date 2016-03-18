#include "xing.h"
#include <QChar>

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
    bool result_1 = m_fpLogin(get_windid(),id,pw,aupw,0,0);
    return result_1;
}
// this funtion is request
int xing::ETK_Request(char * pszCode,void *lpData,int nDataSize,BOOL bNext,char * pszNextKey,int nTimeOut){
    int result_1;
    result_1 = m_fpRequest(get_windid(),pszCode,lpData,nDataSize,bNext,pszNextKey,nTimeOut);
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
            //bug config memory----------------------------------------
//            unsigned int src = (unsigned int)&(pRpData->lpData)-1;
//            unsigned int dst = (unsigned int)&(pRpData->lpData);
//            memmove((void *)dst,(void *)src,4);
            //---------------------------------------------------------

            if(strcmp(pRpData->szBlockName,NAME_t1452OutBlock)==0){
               unsigned char * pRplpdata = pRpData->lpData;
               LPt1452OutBlock pOutBlock = (LPt1452OutBlock)pRplpdata;
            }else if( strcmp( pRpData->szBlockName, NAME_t1452OutBlock1 ) == 0 ){
                unsigned char * pRplpdata ;
                unsigned int src = (unsigned int)&(pRpData->lpData)-1;
                memcpy(&pRplpdata,(void *)src,4);
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
