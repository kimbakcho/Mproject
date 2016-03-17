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
    //type 1 is hts.ebestsec.co.kr connect 실투자
    //type 0 is demo.ebestsec.co.kr connect 모의투자
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
void xing::SetPacketData( char * psData, int nSize, char * pszSrc, int nType, int nDotPos ){

    //-----------------------------------------------------------------------
        // 문자열
        if( nType == DATA_TYPE_STRING )
        {
            // 왼쪽 정렬
            // 뒤의 빈자리는 ' ' 로 채움

            // 버퍼크기가 원 데이터보다 작다면 데이터는 짤려야 하므로 에러발생
            int nSrcLen = strlen( pszSrc );

            // 먼저 Space를 채우고
            FillMemory( psData, nSize, ' ' );

            // 앞에부터 데이터를 넣는다.
            // 원데이터가 크다면 뒷부분을 버린다.
            CopyMemory( psData, pszSrc, min( nSize, nSrcLen ) );
        }

        //-----------------------------------------------------------------------
        // 정수
        else if( nType == DATA_TYPE_LONG )
        {
            // 오른쪽 정렬
            // 앞의 빈자리는 '0' 으로 채움

            // 버퍼크기가 원 데이터보다 작다면 데이터는 짤려야 하므로 에러발생
            int nSrcLen = strlen( pszSrc );
            Q_ASSERT( nSize >= nSrcLen );

            // 먼저 0 으로 채우고
            FillMemory( psData, nSize, '0' );

            // 뒤에서부터 데이터를 넣는다.
            if( nSize >= nSrcLen )
            {
                CopyMemory( psData+nSize-nSrcLen, pszSrc, nSrcLen );
            }
            // 원데이터가 크다면 원데이터의 뒷부분을 버린다.
            else
            {
                CopyMemory( psData, pszSrc, nSize );
            }
        }

        //-----------------------------------------------------------------------
        // 실수 : 소숫점을 찍지 않는다.
        else if( nType == DATA_TYPE_FLOAT )
        {
            // 소숫점 위치를 기준으로 정렬
            // 소숫점을 찍지 않으며 정수부의 빈자리와 소수부의 빈자리는 0으로 채움

            int nSrcLen = strlen( pszSrc );

            // 먼저 0 으로 채우고
            FillMemory( psData, nSize, '0' );

            // 원데이터에서 소숫점의 위치를 찾아서
            // 원데이터의 정수부의 길이와 소수부의 길이를 구한다.
            int nSrcIntLen;
            int nSrcDotLen;
            char * psz = strchr ( pszSrc, '.' );
            if( psz == NULL )		// 소수부가 없다.
            {
                nSrcIntLen = strlen( pszSrc );
                nSrcDotLen = 0;
            }
            else					// 소수부가 있다.
            {
                nSrcIntLen = psz - pszSrc;
                nSrcDotLen = strlen( pszSrc ) - nSrcIntLen - 1;
            }

            // 정수부를 넣는다.
            if( nSize-nDotPos >= nSrcIntLen )
            {
                CopyMemory( psData+nSize-nDotPos-nSrcIntLen, pszSrc, nSrcIntLen );
            }
            else
            {
                // 원데이터의 정수부 길이가 더 긴 경우 정수부의 뒷자리는 삭제된다.
                Q_ASSERT( FALSE );
                CopyMemory( psData, pszSrc, nSize-nDotPos );
            }

            // 소수부를 넣는데 원데이터의 소수부 길이가 더 긴 경우 소수부의 뒷자리는 삭제된다.
            Q_ASSERT( nDotPos >= nSrcDotLen );
            CopyMemory( psData+nSize-nDotPos, pszSrc + strlen( pszSrc ) - nSrcDotLen, min( nDotPos, nSrcDotLen ) );
        }

        //-----------------------------------------------------------------------
        // 실수 : 소숫점을 포함
        else if( nType == DATA_TYPE_FLOAT_DOT )
        {
            // 소숫점 위치를 기준으로 정렬
            // 소숫점을 찍지 않으며 정수부의 빈자리와 소수부의 빈자리는 0으로 채움

            int nSrcLen = strlen( pszSrc );

            // 먼저 0 으로 채우고
            FillMemory( psData, nSize, '0' );

            // 원데이터에서 소숫점의 위치를 찾아서
            // 원데이터의 정수부의 길이와 소수부의 길이를 구한다.
            int nSrcIntLen;
            int nSrcDotLen;
            char * psz = strchr ( pszSrc, '.' );
            if( psz == NULL )		// 소수부가 없다.
            {
                nSrcIntLen = strlen( pszSrc );
                nSrcDotLen = 0;
            }
            else					// 소수부가 있다.
            {
                nSrcIntLen = psz - pszSrc;
                nSrcDotLen = strlen( pszSrc ) - nSrcIntLen - 1;
            }

            // 정수부를 넣는다.
            if( nSize-nDotPos-1 >= nSrcIntLen )
            {
                CopyMemory( psData+nSize-nDotPos-nSrcIntLen-1, pszSrc, nSrcIntLen );
            }
            else
            {
                // 원데이터의 정수부 길이가 더 긴 경우 정수부의 뒷자리는 삭제된다.
                Q_ASSERT( FALSE );
                CopyMemory( psData, pszSrc, nSize-nDotPos-1 );
            }

            // 소숫점을 찍는다.
            psData[nSize-nDotPos-1] = '.';

            // 소수부를 넣는데 원데이터의 소수부 길이가 더 긴 경우 소수부의 뒷자리는 삭제된다.
            Q_ASSERT( nDotPos >= nSrcDotLen );
            CopyMemory( psData+nSize-nDotPos, pszSrc + strlen( pszSrc ) - nSrcDotLen, min( nDotPos, nSrcDotLen ) );
        }

}


int xing::t1452_Request(BOOL bNext){
    t1452InBlock pckInBlock;
    int result_1;
    char szTrNo[] = "t1452";
    memset(&pckInBlock,' ',sizeof(pckInBlock));
    SetPacketData( pckInBlock.gubun    , sizeof( pckInBlock.gubun     ),"0", DATA_TYPE_STRING );	// [string,    1] 구분
    SetPacketData( pckInBlock.jnilgubun, sizeof( pckInBlock.jnilgubun ),"0", DATA_TYPE_STRING );	// [string,    1] 전일구분
    SetPacketData( pckInBlock.sdiff    , sizeof( pckInBlock.sdiff     ),"", DATA_TYPE_LONG   );	// [long  ,    3] 시작등락율
    SetPacketData( pckInBlock.ediff    , sizeof( pckInBlock.ediff     ),"", DATA_TYPE_LONG   );	// [long  ,    3] 종료등락율
    SetPacketData( pckInBlock.jc_num   , sizeof( pckInBlock.jc_num    ),"", DATA_TYPE_LONG   );	// [long  ,   12] 대상제외
    SetPacketData( pckInBlock.sprice   , sizeof( pckInBlock.sprice    ),"", DATA_TYPE_LONG   );	// [long  ,    8] 시작가격
    SetPacketData( pckInBlock.eprice   , sizeof( pckInBlock.eprice    ),"", DATA_TYPE_LONG   );	// [long  ,    8] 종료가격
    SetPacketData( pckInBlock.volume   , sizeof( pckInBlock.volume    ),"", DATA_TYPE_LONG   );	// [long  ,   12] 거래량
    SetPacketData( pckInBlock.idx      , sizeof( pckInBlock.idx       ),"", DATA_TYPE_LONG   );	// [long  ,    4] IDX
    result_1= xing::ETK_Request(szTrNo,  // TR 번호
                &pckInBlock,    	// InBlock 데이터
                sizeof( pckInBlock ), // InBlock 데이터 크기
                bNext,  // 다음조회 여부
                "", // 다음조회 Key
                30 // Timeout(초) : 해당 시간(초)동안 데이터가 오지 않으면 Timeout에 발생한다. XM_TIMEOUT_DATA 메시지가 발생한다.
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
            qDebug()<<kor("접속되었습니다.");

        }
        break;
     case WM_USER+XM_RECEIVE_DATA:
        cresult = msg->wParam;
        //results_str = QString::fromLocal8Bit(wresult);
        if(cresult == 1){ //TR의Data를받았을때발생 RECV_PACKET 의Memory 주소

        }else if(cresult == 2){ //Message를받았을때발생 MSG_PACKET 의Memory 주소
            lresult = (char *)msg->lParam;
            qDebug()<<QString("XM_RECEIVE_DATA case 2 lParam = %1").arg(lresult);
        }else if(cresult == 3){ //Error가발생 MSG_PACKET 의Memory 주소

        }else if(cresult == 4){ //TR이끝났을때발생 정수로Request ID를의미
            iresult = msg->lParam;
            qDebug()<<QString("XM_RECEIVE_DATA case 4 lParam = %1").arg(iresult);
        }
        break;
    default:
        break;
    }
    return false;
}
