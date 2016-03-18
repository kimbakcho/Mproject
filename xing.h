#ifndef XING_H
#define XING_H

#include <QWidget>
#include <Windows.h>
#include <QLibrary>
#include <QDebug>
#include "./Packet/t1452.h"
#define kor(str) QString::fromLocal8Bit(str)
//------------------------------------------------------------------------------
// 메시지 정의
// 메시지의 ID값은 Connect시에 설정한 nStartMsgID와 더하여 사용하면 된다.
#define 	XM_DISCONNECT			1		// 서버와의 연결이 끊어졌을 경우 발생
#define 	XM_RECEIVE_DATA			3		// RequestData로 요청한 데이터가 서버로부터 받았을 때 발생
#define 	XM_RECEIVE_REAL_DATA	4		// AdviseData로 요청한 데이터가 서버로부터 받았을 때 발생
#define 	XM_LOGIN				5		// 서버로부터 로그인 결과 받았을때 발생
#define 	XM_LOGOUT				6		// 서버로부터 로그아웃 결과 받았을때 발생
#define		XM_TIMEOUT_DATA			7		// RequestData로 요청한 데이터가 Timeout 이 발생했을때
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Receive Flag
#define		REQUEST_DATA			1
#define		MESSAGE_DATA			2
#define		SYSTEM_ERROR_DATA		3
#define		RELEASE_DATA			4
//------------------------------------------------------------------------------

enum
{
    DATA_TYPE_STRING = 0,		// 문자열
    DATA_TYPE_LONG,				// 정수
    DATA_TYPE_FLOAT,			// 실수
    DATA_TYPE_FLOAT_DOT,		// 실수( 소숫점을 가지고 있음 )
};
// 조회TR 수신 Packet
typedef struct _RECV_PACKET
{
    _RECV_PACKET() { ZeroMemory( this, sizeof(_RECV_PACKET ) ); }

    int					nRqID;						// Request ID
    int					nDataLength;				// 받은 데이터 크기
    int					nTotalDataBufferSize;		// lpData에 할당된 크기
    int					nElapsedTime;				// 전송에서 수신까지 걸린시간(1/1000초)
    int					nDataMode;					// 1:BLOCK MODE, 2:NON-BLOCK MODE
    char				szTrCode	[10+1];			// AP Code
    char				cCont		[1];			// '0' : 다음조회 없음, '1' : 다음조회 있음
    char				szContKey	[18+1];			// 연속키, Data Header가 B 인 경우에만 사용
    char				szUserData	[30+1];			// 사용자 데이터
    char				szBlockName [17];			// Block 명, Block Mode 일때 사용
    unsigned char *     lpData;
} RECV_PACKET, *LPRECV_PACKET;

// 메시지 수신 Packet
typedef struct
{
    int					nRqID;						// Request ID
    int					nIsSystemError;				// 0:일반메시지, 1:System Error 메시지
    char				szMsgCode[5+1];				// 메시지 코드
    int					nMsgLength;					// Message 길이
    unsigned char*		lpszMessageData;			// Message Data
} MSG_PACKET, *LPMSG_PACKET;

// 실시간TR 수신 Packet
typedef struct _REAL_RECV_PACKET
{
    _REAL_RECV_PACKET() { ZeroMemory( this, sizeof( _REAL_RECV_PACKET ) ); }

    char				szTrCode [ 3 + 1];

    int					nKeyLength;
    char				szKeyData[32 + 1];
    char				szRegKey [32 + 1];

    int					nDataLength;
    char*				pszData;
} RECV_REAL_PACKET, *LPRECV_REAL_PACKET;
//------------------------------------------------------------------------------

class xing : public QWidget
{
    Q_OBJECT
public:
    explicit xing(QWidget *parent = 0);
    bool init();
    void set_windid(HWND data);
    HWND get_windid();
    QString htsip;
    QString demoip;
    int serverport;
    bool ETK_Connect(int type);
    bool ETK_Login(QByteArray Qid,QByteArray Qpasswd,QByteArray Qauthpasswd);
    int ETK_Request(char * pszCode,void *lpData,int nDataSize,BOOL bNext,char * pszNextKey,int nTimeOut);
    void ETK_ReleaseMessageData(LPARAM lp);
    void ETK_ReleaseRequestData(int nRequestID);
    void SetPacketData( char * psData, int nSize, char * pszSrc, int nType, int nDotPos = 0);
    int t1452_Request(BOOL bNext);

    QLibrary lib;
    //-------------------------library from Xingapi typedef---------------------------------
    typedef BOOL	(*FP_CONNECT					) ( HWND,char *, int, int, int, int );
    typedef BOOL	(*FP_ISCONNECTED				) ( );
    typedef BOOL	(*FP_DISCONNECT				) ( );
    typedef BOOL	(*FP_LOGIN					) ( HWND,char *,char *,char *, int, BOOL );
    typedef BOOL	(*FP_LOGOUT					) ( HWND );
    typedef int		(*FP_GETLASTERROR			) ( );
    typedef int		(*FP_GETERRORMESSAGE			) ( int, char *, int );

    typedef int		(*FP_REQUEST					) ( HWND, char *, void *, int, BOOL, char *, int );
    typedef void	(*FP_RELEASEREQUESTDATA		) ( int );
    typedef void	(*FP_RELEASEMESSAGEDATA		) ( LPARAM );

    typedef BOOL	(*FP_ADVISEREALDATA			) ( HWND, char *, char *, int );
    typedef BOOL	(*FP_UNADVISEREALDATA		) ( HWND, char *, char *, int );
    typedef BOOL	(*FP_UNADVISEWINDOW			) ( HWND );

    typedef int		(*FP_GETACCOUNTLISTCOUNT		) ( );
    typedef BOOL	(*FP_GETACCOUNTLIST			) ( int, char *, int );
    typedef void	(*FP_GETCOMMMEDIA			) ( char * );
    typedef void	(*FP_GETETKMEDIA				) ( char * );
    typedef void	(*FP_GETCLIENTIP				) ( char * );
    typedef void	(*FP_GETSERVERNAME			) ( char * );
    typedef void	(*FP_SETHEADERINFO			) ( char *, char * );

    FP_CONNECT					m_fpConnect;
    FP_ISCONNECTED				m_fpIsConnected;
    FP_DISCONNECT				m_fpDisconnect;
    FP_LOGIN					m_fpLogin;
    FP_LOGOUT					m_fpLogout;

    FP_GETLASTERROR				m_fpGetLastError;
    FP_GETERRORMESSAGE			m_fpGetErrorMessage;

    FP_REQUEST					m_fpRequest;
    FP_ADVISEREALDATA			m_fpAdviseRealData;
    FP_UNADVISEREALDATA			m_fpUnadviseRealData;
    FP_UNADVISEWINDOW			m_fpUnadviseWindow;
    FP_RELEASEREQUESTDATA		m_fpReleaseRequestData;
    FP_RELEASEMESSAGEDATA		m_fpReleaseMessageData;

    FP_GETACCOUNTLISTCOUNT		m_fpGetAccountListCount;
    FP_GETACCOUNTLIST			m_fpGetAccountList;
    FP_GETCOMMMEDIA				m_fpGetCommMedia;
    FP_GETETKMEDIA				m_fpGetETKMedia;
    FP_GETCLIENTIP				m_fpGetClientIP;
    FP_GETSERVERNAME			m_fpGetServerName;

    FP_SETHEADERINFO			m_fpSetHeaderInfo;
//------------------------------------------------------------------------------
//-------------------------win id---------------------------------
    HWND xing_winid;

private:
    QByteArray serverip;
    bool nativeEvent(const QByteArray & eventType, void * message, long * result);

signals:

public slots:
};

#endif // XING_H
