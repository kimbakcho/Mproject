#ifndef XING_H
#define XING_H

#include <QWidget>
#include <Windows.h>
#include <QLibrary>
#include <QDebug>
#include "./Packet/t1452.h"
#define kor(str) QString::fromLocal8Bit(str)
//------------------------------------------------------------------------------
// �޽��� ����
// �޽����� ID���� Connect�ÿ� ������ nStartMsgID�� ���Ͽ� ����ϸ� �ȴ�.
#define 	XM_DISCONNECT			1		// �������� ������ �������� ��� �߻�
#define 	XM_RECEIVE_DATA			3		// RequestData�� ��û�� �����Ͱ� �����κ��� �޾��� �� �߻�
#define 	XM_RECEIVE_REAL_DATA	4		// AdviseData�� ��û�� �����Ͱ� �����κ��� �޾��� �� �߻�
#define 	XM_LOGIN				5		// �����κ��� �α��� ��� �޾����� �߻�
#define 	XM_LOGOUT				6		// �����κ��� �α׾ƿ� ��� �޾����� �߻�
#define		XM_TIMEOUT_DATA			7		// RequestData�� ��û�� �����Ͱ� Timeout �� �߻�������
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
    DATA_TYPE_STRING = 0,		// ���ڿ�
    DATA_TYPE_LONG,				// ����
    DATA_TYPE_FLOAT,			// �Ǽ�
    DATA_TYPE_FLOAT_DOT,		// �Ǽ�( �Ҽ����� ������ ���� )
};
// ��ȸTR ���� Packet
typedef struct _RECV_PACKET
{
    _RECV_PACKET() { ZeroMemory( this, sizeof(_RECV_PACKET ) ); }

    int					nRqID;						// Request ID
    int					nDataLength;				// ���� ������ ũ��
    int					nTotalDataBufferSize;		// lpData�� �Ҵ�� ũ��
    int					nElapsedTime;				// ���ۿ��� ���ű��� �ɸ��ð�(1/1000��)
    int					nDataMode;					// 1:BLOCK MODE, 2:NON-BLOCK MODE
    char				szTrCode	[10+1];			// AP Code
    char				cCont		[1];			// '0' : ������ȸ ����, '1' : ������ȸ ����
    char				szContKey	[18+1];			// ����Ű, Data Header�� B �� ��쿡�� ���
    char				szUserData	[30+1];			// ����� ������
    char				szBlockName [17];			// Block ��, Block Mode �϶� ���
    unsigned char *     lpData;
} RECV_PACKET, *LPRECV_PACKET;

// �޽��� ���� Packet
typedef struct
{
    int					nRqID;						// Request ID
    int					nIsSystemError;				// 0:�Ϲݸ޽���, 1:System Error �޽���
    char				szMsgCode[5+1];				// �޽��� �ڵ�
    int					nMsgLength;					// Message ����
    unsigned char*		lpszMessageData;			// Message Data
} MSG_PACKET, *LPMSG_PACKET;

// �ǽð�TR ���� Packet
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
