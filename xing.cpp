#include "xing.h"
#include "mainframe.h"


extern mainframe *mf;


xing::xing(QWidget *parent) : QWidget(parent)
{
    htsip = "hts.ebestsec.co.kr";
    demoip = "demo.ebestsec.co.kr";
    serverport = 20001;
    buy_flag = true;
    hight_value1833_flag = true;
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
    SetPacketData( pckInBlock.jnilgubun, sizeof( pckInBlock.jnilgubun ),"1", DATA_TYPE_STRING );	// [string,    1] 전일구분
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
int xing::t0424_Request(BOOL nNext,t0424InBlockdata data){
    t0424InBlock pckInBlock;
    char			szTrNo[]		= "t0424";
    char			szNextKey[]		= "";
    memset(&pckInBlock,' ',sizeof(pckInBlock));

    SetPacketData( pckInBlock.accno       , sizeof( pckInBlock.accno        ), data.accno       , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.passwd      , sizeof( pckInBlock.passwd       ), data.passwd      , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.prcgb       , sizeof( pckInBlock.prcgb        ), data.prcgb       , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.chegb       , sizeof( pckInBlock.chegb        ), data.chegb       , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.dangb       , sizeof( pckInBlock.dangb        ), data.dangb       , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.charge      , sizeof( pckInBlock.charge       ), data.charge      , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.cts_expcode , sizeof( pckInBlock.cts_expcode  ), data.cts_expcode , DATA_TYPE_STRING );

    int nRqID = ETK_Request(szTrNo,&pckInBlock,sizeof(pckInBlock),nNext,szNextKey,30);
    if(nRqID<0){
        qDebug()<<"t0424_Request 실패";
    }
    return nRqID;
}
int xing::t0425_Request(BOOL nNext,t0425InBlockdata data){
    t0425InBlock pckInBlock;
    char			szTrNo[]		= "t0425";
    char			szNextKey[]		= "";
    memset(&pckInBlock,' ',sizeof(pckInBlock));

    SetPacketData( pckInBlock.accno       , sizeof( pckInBlock.accno        ), data.accno       , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.passwd      , sizeof( pckInBlock.passwd       ), data.passwd      , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.expcode     , sizeof( pckInBlock.expcode      ), data.expcode     , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.chegb       , sizeof( pckInBlock.chegb        ), data.chegb       , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.medosu      , sizeof( pckInBlock.medosu       ), data.medosu      , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.sortgb      , sizeof( pckInBlock.sortgb       ), data.sortgb      , DATA_TYPE_STRING );
    SetPacketData( pckInBlock.cts_ordno   , sizeof( pckInBlock.cts_ordno    ), data.cts_ordno   , DATA_TYPE_STRING );

    int nRqID = ETK_Request(szTrNo,&pckInBlock,sizeof(pckInBlock),nNext,szNextKey,30);
    if(nRqID<0){
        qDebug()<<"t0424_Request 실패";
    }
    return nRqID;
}

int xing::t1101_Request(BOOL nNext,t1101InBlockdata data){
    t1101InBlock pckInBlock;
    char			szTrNo[]		= "t1101";
    char			szNextKey[]		= "";
    memset(&pckInBlock,' ',sizeof(pckInBlock));
    SetPacketData( pckInBlock.shcode       , sizeof( pckInBlock.shcode        ), data.shcode       , DATA_TYPE_STRING );
    int nRqID = ETK_Request(szTrNo,&pckInBlock,sizeof(pckInBlock),nNext,szNextKey,30);
    if(nRqID<0){
        qDebug()<<"t0424_Request 실패";
    }
    return nRqID;

}

int xing::CSPAT00600_Request(BOOL nNext,CSPAT00600data data){
    CSPAT00600InBlock1	pckInBlock;
    char			szTrNo[]		= "CSPAT00600";
    char			szNextKey[]		= "";
    QString price = QString::fromLocal8Bit(data.strOrdPrc);
    QString price1;
    QByteArray qt_byte;
    memset(&pckInBlock,' ',sizeof(pckInBlock));

    int price_int = price.toInt();
    if(price_int<5000){
        price_int = price_int/5;
        price_int = price_int*5;
    }else if(price_int>=5000&&price_int<10000){
        price_int = price_int/10;
        price_int = price_int*10;
    }else if(price_int>=10000&&price_int<50000){
        price_int = price_int/50;
        price_int = price_int*50;
    }else if(price_int>=50000&&price_int<100000){
        price_int = price_int/100;
        price_int = price_int*100;
    }
    price1 = QString("%1").arg(price_int);
    qt_byte = price1.toLocal8Bit();
    data.strOrdPrc = qt_byte.data();


    SetPacketData( pckInBlock.AcntNo       , sizeof( pckInBlock.AcntNo        ), data.strAcntNo       , DATA_TYPE_STRING );		// 계좌번호
    SetPacketData( pckInBlock.InptPwd      , sizeof( pckInBlock.InptPwd       ), data.strInptPwd      , DATA_TYPE_STRING );		// 입력비밀번호
    SetPacketData( pckInBlock.IsuNo        , sizeof( pckInBlock.IsuNo         ), data.strIsuNo        , DATA_TYPE_STRING );		// 종목번호
    SetPacketData( pckInBlock.OrdQty       , sizeof( pckInBlock.OrdQty        ), data.strOrdQty       , DATA_TYPE_LONG   );		// 주문수량
    SetPacketData( pckInBlock.OrdPrc       , sizeof( pckInBlock.OrdPrc        ), data.strOrdPrc       , DATA_TYPE_FLOAT_DOT, 2 );	// 주문가, Header Type이 B 인 경우 Data Type이 실수면 소수점을 포함해야 한다.
    SetPacketData( pckInBlock.BnsTpCode    , sizeof( pckInBlock.BnsTpCode     ), data.strBnsTpCode    , DATA_TYPE_STRING );		// 매매구분
    SetPacketData( pckInBlock.OrdprcPtnCode, sizeof( pckInBlock.OrdprcPtnCode ), data.strOrdprcPtnCode, DATA_TYPE_STRING );		// 호가유형코드
    SetPacketData( pckInBlock.MgntrnCode   , sizeof( pckInBlock.MgntrnCode    ), data.strMgntrnCode   , DATA_TYPE_STRING );		// 신용거래코드
    SetPacketData( pckInBlock.LoanDt       , sizeof( pckInBlock.LoanDt        ), data.strLoanDt       , DATA_TYPE_STRING );		// 대출일
    SetPacketData( pckInBlock.OrdCndiTpCode, sizeof( pckInBlock.OrdCndiTpCode ), data.strOrdCndiTpCode, DATA_TYPE_STRING ); 		// 주문조건구분

    int nRqID = ETK_Request(szTrNo,&pckInBlock,sizeof(pckInBlock),nNext,szNextKey,30);



    if(nRqID<0){
        qDebug()<<"CSPAT00600_Request 실패";
    }
    return nRqID;

}

int xing::CSPAQ13700_Request(BOOL nNext,CSPAQ13700InBlock1data data){
    CSPAQ13700InBlock1	pckInBlock;
    char			szTrNo[]		= "CSPAQ13700";
    char			szNextKey[]		= "";

    memset(&pckInBlock,' ',sizeof(pckInBlock));

    SetPacketData( pckInBlock.RecCnt     , sizeof( pckInBlock.RecCnt      ), "1"           , DATA_TYPE_LONG   );    // [long  ,    5] 레코드갯수
    SetPacketData( pckInBlock.AcntNo     , sizeof( pckInBlock.AcntNo      ), data.AcntNo     , DATA_TYPE_STRING );    // [string,   20] 계좌번호
    SetPacketData( pckInBlock.InptPwd    , sizeof( pckInBlock.InptPwd     ), data.InptPwd    , DATA_TYPE_STRING );    // [string,    8] 입력비밀번호
    SetPacketData( pckInBlock.OrdMktCode , sizeof( pckInBlock.OrdMktCode  ), data.OrdMktCode , DATA_TYPE_STRING );    // [string,    2] 주문시장코드
    SetPacketData( pckInBlock.BnsTpCode  , sizeof( pckInBlock.BnsTpCode   ), data.BnsTpCode  , DATA_TYPE_STRING );    // [string,    1] 매매구분
    SetPacketData( pckInBlock.IsuNo      , sizeof( pckInBlock.IsuNo       ), data.IsuNo      , DATA_TYPE_STRING );    // [string,   12] 종목번호
    SetPacketData( pckInBlock.ExecYn     , sizeof( pckInBlock.ExecYn      ), data.ExecYn     , DATA_TYPE_STRING );    // [string,    1] 체결여부
    SetPacketData( pckInBlock.OrdDt      , sizeof( pckInBlock.OrdDt       ), data.OrdDt      , DATA_TYPE_STRING );    // [string,    8] 주문일
    SetPacketData( pckInBlock.SrtOrdNo2  , sizeof( pckInBlock.SrtOrdNo2   ), data.SrtOrdNo2  , DATA_TYPE_LONG   );    // [long  ,   10] 시작주문번호2
    SetPacketData( pckInBlock.BkseqTpCode, sizeof( pckInBlock.BkseqTpCode ), data.BkseqTpCode, DATA_TYPE_STRING );    // [string,    1] 역순구분
    SetPacketData( pckInBlock.OrdPtnCode , sizeof( pckInBlock.OrdPtnCode  ), data.OrdPtnCode , DATA_TYPE_STRING );    // [string,    2] 주문유형코드

    int nRqID = ETK_Request(szTrNo,&pckInBlock,sizeof(pckInBlock),nNext,szNextKey,30);

    return nRqID;

};

 int xing::CSPAQ12300_Request(BOOL nNext,CSPAQ12300InBlock1data data){
     CSPAQ12300InBlock1	pckInBlock;
     char			szTrNo[]		= "CSPAQ12300";
     char			szNextKey[]		= "";

     memset(&pckInBlock,' ',sizeof(pckInBlock));

     SetPacketData( pckInBlock.RecCnt        , sizeof( pckInBlock.RecCnt         ), "1"              , DATA_TYPE_LONG         );    // [long  ,    5] 레코드갯수
     SetPacketData( pckInBlock.AcntNo        , sizeof( pckInBlock.AcntNo         ), data.AcntNo        , DATA_TYPE_STRING       );    // [string,   20] 계좌번호
     SetPacketData( pckInBlock.Pwd           , sizeof( pckInBlock.Pwd            ), data.Pwd           , DATA_TYPE_STRING       );    // [string,    8] 비밀번호
     SetPacketData( pckInBlock.BalCreTp      , sizeof( pckInBlock.BalCreTp       ), data.BalCreTp      , DATA_TYPE_STRING       );    // [string,    1] 잔고생성구분
     SetPacketData( pckInBlock.CmsnAppTpCode , sizeof( pckInBlock.CmsnAppTpCode  ), data.CmsnAppTpCode , DATA_TYPE_STRING       );    // [string,    1] 수수료적용구분
     SetPacketData( pckInBlock.D2balBaseQryTp, sizeof( pckInBlock.D2balBaseQryTp ), data.D2balBaseQryTp, DATA_TYPE_STRING       );    // [string,    1] D2잔고기준조회구분
     SetPacketData( pckInBlock.UprcTpCode    , sizeof( pckInBlock.UprcTpCode     ), data.UprcTpCode    , DATA_TYPE_STRING       );    // [string,    1] 단가구분

     int nRqID = ETK_Request(szTrNo,&pckInBlock,sizeof(pckInBlock),nNext,szNextKey,30);

     return nRqID;
 }

 int xing::CSPAT00800_Request(BOOL nNext,CSPAT00800InBlock1data data){
     CSPAT00800InBlock1	pckInBlock;
     char			szTrNo[]		= "CSPAT00800";
     char			szNextKey[]		= "";

     memset(&pckInBlock,' ',sizeof(pckInBlock));

     SetPacketData( pckInBlock.OrgOrdNo      , sizeof( pckInBlock.OrgOrdNo       ), data.OrgOrdNo   , DATA_TYPE_STRING         );    // [long  ,    5] 레코드갯수
     SetPacketData( pckInBlock.AcntNo        , sizeof( pckInBlock.AcntNo         ), data.AcntNo     , DATA_TYPE_STRING       );    // [string,   20] 계좌번호
     SetPacketData( pckInBlock.InptPwd       , sizeof( pckInBlock.InptPwd        ), data.InptPwd    , DATA_TYPE_STRING       );    // [string,    8] 비밀번호
     SetPacketData( pckInBlock.IsuNo         , sizeof( pckInBlock.IsuNo          ), data.IsuNo      , DATA_TYPE_STRING       );    // [string,    1] 잔고생성구분
     SetPacketData( pckInBlock.OrdQty        , sizeof( pckInBlock.OrdQty         ), data.OrdQty     , DATA_TYPE_STRING       );    // [string,    1] 수수료적용구분

     int nRqID = ETK_Request(szTrNo,&pckInBlock,sizeof(pckInBlock),nNext,szNextKey,30);

     return nRqID;
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
        if(cresult == REQUEST_DATA){ //TR의Data를받았을때발생 RECV_PACKET 의Memory 주소
            LPRECV_PACKET pRpData = (LPRECV_PACKET)msg->lParam;
            if(strcmp(pRpData->szBlockName,NAME_t1452OutBlock)==0){
                func_t1452outblock(pRpData);
            }else if( strcmp( pRpData->szBlockName, NAME_t1452OutBlock1 ) == 0 ){
                func_t1452outblock1(pRpData);
            }else if(strcmp( pRpData->szBlockName, NAME_t1833OutBlock)==0){
                func_t1833outblock(pRpData);
            }else if(strcmp( pRpData->szBlockName, NAME_t1833OutBlock1)==0){
                func_t1833outblock1(pRpData);
            }else if(strcmp( pRpData->szBlockName, NAME_CSPAT00600OutBlock2)==0){
                func_CSPAT00600OutBlock2(pRpData);
            }else if(strcmp(pRpData->szTrCode,"CSPAQ12300") == 0){
                func_CSPAT12300OutBlock3(pRpData);
            }else if(strcmp(pRpData->szTrCode, "t0424") == 0){
                func_t0424OutBlock1(pRpData);
            }else if(strcmp( pRpData->szBlockName, NAME_t1101OutBlock)==0){
                func_t1101outblock(pRpData);
            }else if(strcmp(pRpData->szTrCode, "t0425") == 0){
                func_t0425OutBlock1(pRpData);
            }

        }else if(cresult == MESSAGE_DATA){ //Message를받았을때발생 MSG_PACKET 의Memory 주소
            LPMSG_PACKET pMsg = (LPMSG_PACKET)msg->lParam;
            //bug config memory----------------------------------------
//            unsigned int src = (unsigned int)&(pMsg->nMsgLength)-2;
//            unsigned int dst = (unsigned int)&(pMsg->nMsgLength);
//            memmove((void *)dst,(void *)src,8);
            //---------------------------------------------------------
            //qDebug()<<QString("XM_RECEIVE_DATA case 2 lParam = %1").arg(lresult);
            ETK_ReleaseMessageData(msg->lParam);

        }else if(cresult == SYSTEM_ERROR_DATA){ //Error가발생 MSG_PACKET 의Memory 주소
            LPMSG_PACKET pMsg = (LPMSG_PACKET)msg->lParam;

            ETK_ReleaseMessageData(msg->lParam);
        }else if(cresult == RELEASE_DATA){ //TR이끝났을때발생 정수로Request ID를의미
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
       int	nCount = pRpData->nDataLength / sizeof( t1452OutBlock1 );		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
       for( int i=0; i<nCount; i++ )
       {
           //데이터 처리
           QString hname = QString::fromLocal8Bit(pOutBlock[i].hname,20);
           QString hprice = QString::fromLocal8Bit(pOutBlock[i].price,8);
           qDebug()<<kor("결과 %1: %2 , %3").arg(i).arg(hname).arg(hprice);
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
       unsigned int src = (unsigned int)&(pRpData->lpData);
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
       int real_volume;
       QString tpcode = "2";
       QString prcptncode = "00";
       QString mgntrncode = "000";
       QString loandt ="";
       QString ordcnditpcode="0";
       int	nCount = pRpData->nDataLength / sizeof( t1833OutBlock1 );		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
       //qDebug()<<QString("t1833 time = %1").arg(QTime::currentTime().toString("hh:mm:ss"));

       for( int i=0; i<nCount; i++ )
       {
           //데이터 처리
           QString shcode = QString::fromLocal8Bit(pOutBlock[i].shcode,6);
           QString hname = QString::fromLocal8Bit(pOutBlock[i].hname,20);
           QString volume = QString::fromLocal8Bit(pOutBlock[i].volume,10);
           QString price = QString::fromLocal8Bit(pOutBlock[i].close,9);
           QString diff = QString::fromLocal8Bit(pOutBlock[i].diff,6);
           if(hight_value1833_flag){
               hight_value1833.insert(shcode,new data_1833());
               qDebug()<<QString("t1833 time = %1").arg(QTime::currentTime().toString("hh:mm:ss"));
               hight_value1833.insert(shcode,new data_1833());
               qDebug()<<kor("t1833  insert 결과 : shcode = %2 , hname = %3,price = %4,volume = %5,diff =%6 ")
                                    .arg(shcode).arg(hname).arg(price).arg(volume).arg(diff);
           }else {
               bool newvalue = hight_value1833.contains(shcode);

               if(!newvalue){
                   qDebug()<<QString("t1833 time = %1").arg(QTime::currentTime().toString("hh:mm:ss"));
                   hight_value1833.insert(shcode,new data_1833());
                   qDebug()<<kor("t1833 retain insert 결과 : shcode = %2 , hname = %3,price = %4,volume = %5,diff =%6 ")
                                        .arg(shcode).arg(hname).arg(price).arg(volume).arg(diff);


                   if(buy_flag&&(mf->Qusebuy->isChecked())){
                       real_volume = volume.toInt();
                       if(real_volume>50000){

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
                           data.strOrdprcPtnCode = qb_temp[6].data();

                            //MgntrnCode
                           qb_temp[7] = mgntrncode.toLocal8Bit();
                           data.strMgntrnCode = qb_temp[7].data();

                           //LoanDt
                           qb_temp[8] = loandt.toLocal8Bit();
                           data.strLoanDt = qb_temp[8].data();

                            //OrdCndiTpCode
                           qb_temp[9] = ordcnditpcode.toLocal8Bit();
                           data.strOrdCndiTpCode = qb_temp[9].data();

                           int result_3 = CSPAT00600_Request(true,data);
                           if(result_3>0){
                               d_1833 = new data_1833();
                               d_1833->shcode = shcode;
                               d_1833->hname = hname;
                               d_1833->volume = volume;
                               d_1833->price = price;
                               d_1833->diff = diff;
                               vector_1833.append(d_1833);
                               buy_flag = false;
                           }
                       }
                   }
               }
           }
//           qDebug()<<kor("t1833 결과 (%1): shcode = %2 , hname = %3,price = %4,volume = %5,diff =%6 ")
//                     .arg(i).arg(shcode).arg(hname).arg(price).arg(volume).arg(diff);

       }
       hight_value1833_flag = false;

//       for(int i=0;i<vector.size();i++){
//           qDebug()<<QString("qvector shcode = %1").arg(vector.at(0)->shcode);
//       }

}

void xing::func_t1101outblock(LPRECV_PACKET pRpData){
    //xing api bug config memory----------------------------------------
       unsigned char * pRplpdata ;
       unsigned int src = (unsigned int)&(pRpData->lpData);
       memcpy(&pRplpdata,(void *)src,4);
    //------------------------------------------------------------------
       LPt1101OutBlock pOutBlock = (LPt1101OutBlock)pRplpdata;
       int	nCount = pRpData->nDataLength / sizeof( t1101OutBlock );		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
       QString hname = QString::fromLocal8Bit(pOutBlock->hname,20);
       QString shcode = QString::fromLocal8Bit(pOutBlock->shcode,6);
       QString price = QString::fromLocal8Bit(pOutBlock->price,8);
       rich_data *data_temp1;
       int price_int = price.toInt();
       int loss_int;
       int obj_int;
       int testvalue;
       testvalue = wk->richdatamap.size();
        data_temp1= wk->richdatamap.value(shcode);
        loss_int = data_temp1->loss.toInt();
        obj_int = data_temp1->obj.toInt();
       if(loss_int>=price_int){
           //손절
            data_temp1->loss_flag=true;
            qDebug()<<kor("결과 loss t1101: shcode = %1,hanme = %2,price = %3").arg(shcode).arg(hname).arg(price);
       }
       if(obj_int<=price_int){
           data_temp1->obj_flag=true;
           qDebug()<<kor("결과 obj t1101: shcode = %1,hanme = %2,price = %3").arg(shcode).arg(hname).arg(price);
       }
       //

}


void xing::func_CSPAT00600OutBlock2(LPRECV_PACKET pRpData){
    //xing api bug config memory----------------------------------------
       unsigned char * pRplpdata ;
       unsigned int src = (unsigned int)&(pRpData->lpData)-1;
       memcpy(&pRplpdata,(void *)src,4);
    //------------------------------------------------------------------
     LPCSPAT00600OutBlock2 pOutBlock = (LPCSPAT00600OutBlock2)pRplpdata;
//     int	nCount = pRpData->nDataLength / sizeof( CSPAT00600OutBlock2 );		// Block Mode 시엔 전체크기 / 하나의 Record 크기 로 갯수를 구한다.
     qDebug()<<QString("CSPAT00600OutBlock2");
}

void xing::func_CSPAT12300OutBlock3(LPRECV_PACKET pRpData){
    //xing api bug config memory----------------------------------------
       unsigned char * pRplpdata ;
       unsigned int src = (unsigned int)&(pRpData->lpData);
       memcpy(&pRplpdata,(void *)src,4);
    //------------------------------------------------------------------
       int	nDataLength  = pRpData->nDataLength;
       LPCSPAQ12300AllOutBlock pAllOutBlock = (LPCSPAQ12300AllOutBlock)pRpData->lpData;
       char szCount[6] = { 0 };
       int nCount;

       nDataLength -= sizeof( CSPAQ12300OutBlock1 );
       nDataLength -= sizeof( CSPAQ12300OutBlock2 );
       nDataLength -= 5;
       CopyMemory( szCount, pAllOutBlock->sCountOutBlock3, 5 );
       nCount = atoi( szCount );
       for( int i=0; i<nCount; i++ )
       {
           QString IsuNo = QString::fromLocal8Bit(pAllOutBlock->outBlock3[i].IsuNo,sizeof(pAllOutBlock->outBlock3[i].IsuNo));
           qDebug()<<QString("func_CSPAT12300OutBlock3 IsuNo = %1").arg(IsuNo);
       }
}
void xing::func_t0424OutBlock1(LPRECV_PACKET pRpData){
    //xing api bug config memory----------------------------------------
       unsigned char * pRplpdata ;
       unsigned int src = (unsigned int)&(pRpData->lpData);
       memcpy(&pRplpdata,(void *)src,4);
    //------------------------------------------------------------------
       int	nDataLength  = pRpData->nDataLength;
       LPtt0424AllOutBlock pAllOutBlock = (LPtt0424AllOutBlock)pRpData->lpData;
       char szCount[6] = { 0 };
       int nCount;
       nDataLength -= sizeof( t0424OutBlock );
       nDataLength -= 5;
       CopyMemory( szCount, pAllOutBlock->sCountOutBlock1, 5 );
       nCount = atoi( szCount );
       for( int i=0; i<nCount; i++ )
       {
           //데이터 처리
           QString expcode = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].expcode,sizeof(pAllOutBlock->OutBlock1[i].expcode));
           QString jangb = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].jangb,sizeof(pAllOutBlock->OutBlock1[i].jangb));
           QString janqty = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].janqty,sizeof(pAllOutBlock->OutBlock1[i].janqty));
           QString mdposqt = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].mdposqt,sizeof(pAllOutBlock->OutBlock1[i].mdposqt));
           QString pamt = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].pamt,sizeof(pAllOutBlock->OutBlock1[i].pamt));
           QString hname = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].hname,sizeof(pAllOutBlock->OutBlock1[i].hname));
           mdposqt.replace(" ","");
           expcode.replace(" ","");
           hname.replace(" ","");
           int mdposqt_int = mdposqt.toInt();


           //qDebug()<<QString("func_t0424OutBlock1 expcode = %1 hname = %2").arg(expcode).arg(hname);

           if(wk->richdatamap.contains(expcode) && (mdposqt_int>0)){


               QByteArray qb_temp[10];
               CSPAT00600data data;
               //QString price = tempdata->price;
               QString tpcode = "1";
               QString prcptncode = "00";
               QString mgntrncode = "000";
               QString loandt ="";
               QString ordcnditpcode = "0";
               rich_data *tempvalue;

               tempvalue = wk->richdatamap.value(expcode);

               qb_temp[0] = tempvalue->shcode.toLocal8Bit();
               data.strIsuNo = qb_temp[0].data();

               qb_temp[1] = mf->QLInptPwd->text().toLocal8Bit();
               data.strInptPwd = qb_temp[1].data();

               qb_temp[2] = mf->QLLQAcntNo->text().toLocal8Bit();
               data.strAcntNo = qb_temp[2].data();

               //price qty
               qb_temp[3] = mdposqt.toLocal8Bit();
               data.strOrdQty = qb_temp[3].data();

               //price
               qb_temp[4] = tempvalue->obj.toLocal8Bit();
               data.strOrdPrc = qb_temp[4].data();



               //BnsTpCode
               qb_temp[5] = tpcode.toLocal8Bit();
               data.strBnsTpCode = qb_temp[5].data();

                //OrdprcPtnCode
               qb_temp[6] = prcptncode.toLocal8Bit();
               data.strOrdprcPtnCode = qb_temp[6].data();

                //MgntrnCode
               qb_temp[7] = mgntrncode.toLocal8Bit();
               data.strMgntrnCode = qb_temp[7].data();

               //LoanDt
               qb_temp[8] = loandt.toLocal8Bit();
               data.strLoanDt = qb_temp[8].data();

                //OrdCndiTpCode
               qb_temp[9] = ordcnditpcode.toLocal8Bit();
               data.strOrdCndiTpCode = qb_temp[9].data();

               if(!tempvalue->loss_flag && mf->Qusebuy->isChecked()){
                    int result_3 = CSPAT00600_Request(true,data);
                    qDebug()<<QString("func_t0424OutBlock1 to CSPAT00600_Request expcode = %1 hname = %2").arg(expcode).arg(hname);
               }else if (tempvalue->loss_flag && mf->Qusebuy->isChecked()){
                   //손절
                  //price
                  qb_temp[4] = tempvalue->loss.toLocal8Bit();
                  data.strOrdPrc = qb_temp[4].data();
                  //시장가 매도
                  prcptncode = "03";
                   //OrdprcPtnCode
                  qb_temp[6] = prcptncode.toLocal8Bit();
                  data.strOrdprcPtnCode = qb_temp[6].data();


                  int result_3 = CSPAT00600_Request(true,data);
               }
           }
       }
}
void xing::func_t0425OutBlock1(LPRECV_PACKET pRpData){
    //xing api bug config memory----------------------------------------
       unsigned char * pRplpdata ;
       unsigned int src = (unsigned int)&(pRpData->lpData);
       memcpy(&pRplpdata,(void *)src,4);
    //------------------------------------------------------------------
    int	nDataLength  = pRpData->nDataLength;
    LPtt0425AllOutBlock pAllOutBlock = (LPtt0425AllOutBlock)pRpData->lpData;
    char szCount[6] = { 0 };
    int nCount;
    nDataLength -= sizeof( t0425OutBlock );
    nDataLength -= 5;
    CopyMemory( szCount, pAllOutBlock->sCountOutBlock1, 5 );
    nCount = atoi( szCount );
    for(int i=0;i<nCount;i++){
        QString expcode = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].expcode,sizeof(pAllOutBlock->OutBlock1[i].expcode));
        QString orgordno = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].orgordno,sizeof(pAllOutBlock->OutBlock1[i].orgordno));
        QString ordno = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].ordno,sizeof(pAllOutBlock->OutBlock1[i].ordno));
        QString ordrem = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].ordrem,sizeof(pAllOutBlock->OutBlock1[i].ordrem));
        QString hogagb = QString::fromLocal8Bit(pAllOutBlock->OutBlock1[i].hogagb,sizeof(pAllOutBlock->OutBlock1[i].hogagb));
        expcode.replace(" ","");
        orgordno.replace(" ","");
        ordrem.replace(" ","");
        if(wk->richdatamap.contains(expcode)){
            rich_data *tempvalue;
            tempvalue = wk->richdatamap.value(expcode);
            QString hname = tempvalue->hname;

            //qDebug()<<QString("t0445 hname : %1").arg(hname);
            if(tempvalue->loss_flag && (hogagb.compare("03")!=0)){
                //매도 취소 주문
                QByteArray qb_temp_loss[10];
                CSPAT00800InBlock1data data_loss;

                qb_temp_loss[0] = ordno.toLocal8Bit();
                data_loss.OrgOrdNo = qb_temp_loss[0].data();

                qb_temp_loss[1] = mf->QLLQAcntNo->text().toLocal8Bit();
                data_loss.AcntNo = qb_temp_loss[1].data();

                qb_temp_loss[2] = mf->QLInptPwd->text().toLocal8Bit();
                data_loss.InptPwd = qb_temp_loss[2].data();

                qb_temp_loss[3] = expcode.toLocal8Bit();
                data_loss.IsuNo = qb_temp_loss[3].data();

                qb_temp_loss[4] = ordrem.toLocal8Bit();
                data_loss.OrdQty = qb_temp_loss[4].data();


                CSPAT00800_Request(true,data_loss);

            }
            if(tempvalue->obj_flag){
                //매수 취소 주문
                QByteArray qb_temp_obj[10];
                CSPAT00800InBlock1data data_obj;

                qb_temp_obj[0] = ordno.toLocal8Bit();
                data_obj.OrgOrdNo = qb_temp_obj[0].data();

                qb_temp_obj[1] = mf->QLLQAcntNo->text().toLocal8Bit();
                data_obj.AcntNo = qb_temp_obj[1].data();

                qb_temp_obj[2] = mf->QLInptPwd->text().toLocal8Bit();
                data_obj.InptPwd = qb_temp_obj[2].data();

                qb_temp_obj[3] = expcode.toLocal8Bit();
                data_obj.IsuNo = qb_temp_obj[3].data();

                qb_temp_obj[4] = ordrem.toLocal8Bit();
                data_obj.OrdQty = qb_temp_obj[4].data();

                CSPAT00800_Request(true,data_obj);
            }
        }
    }
}

