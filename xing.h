#ifndef XING_H
#define XING_H

#include <QWidget>
#include <Windows.h>
#include <QLibrary>
#include <QDebug>
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



    QLibrary lib;
    //-------------------------library from Xingapi typedef---------------------------------
    typedef BOOL	(*FP_CONNECT					) ( HWND,char *, int, int, int, int );
    typedef BOOL	(*FP_ISCONNECTED				) ( );
    typedef BOOL	(*FP_DISCONNECT				) ( );
    typedef BOOL	(*FP_LOGIN					) ( HWND,char *,char *,char *, int, BOOL );
    typedef BOOL	(*FP_LOGOUT					) ( HWND );
    typedef int		(*FP_GETLASTERROR			) ( );
    typedef int		(*FP_GETERRORMESSAGE			) ( int, char *, int );

    typedef int		(*FP_REQUEST					) ( HWND, char *, long *, int, BOOL, char *, int );
    typedef void	(*FP_RELEASEREQUESTDATA		) ( int );
    typedef void	(*FP_RELEASEMESSAGEDATA		) ( char * );

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
