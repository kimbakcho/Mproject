#ifndef XING_H
#define XING_H

#include <QWidget>
#include <Windows.h>
#include <QLibrary>
#include <QDebug>
#include <QTime>
#include "./Packet/t1452.h"
#include "./packet/CSPAT00600.h"
#include "./packet/cspaq13700.h"
#include <QVector>
#include "data_1833.h"
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

#define NAME_t1833     "t1833"

// �⺻�Է�
typedef struct _t1833InBlock
{
    char    dummy               [   1];    char    _dummy               ;    // [string,    1] Dummy                           StartPos 0, Length 1
} t1833InBlock, *LPt1833InBlock;
#define NAME_t1833InBlock     "t1833InBlock"

// ���
typedef struct _t1833OutBlock
{
    char    JongCnt             [   4];    char    _JongCnt             ;    // [long  ,    4] �˻������                      StartPos 0, Length 4
} t1833OutBlock, *LPt1833OutBlock;
#define NAME_t1833OutBlock     "t1833OutBlock"

// ���1
typedef struct _t1833OutBlock1
{
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] �����ڵ�                        StartPos 0, Length 6
    char    hname               [  20];    char    _hname               ;    // [string,   20] �����                          StartPos 7, Length 20
    char    sign                [   1];    char    _sign                ;    // [string,    1] ���ϴ�񱸺�                    StartPos 28, Length 1
    char    signcnt             [   3];    char    _signcnt             ;    // [long  ,    3] ���Ӻ���                        StartPos 30, Length 3
    char    close               [   9];    char    _close               ;    // [long  ,    9] ���簡                          StartPos 34, Length 9
    char    change              [   9];    char    _change              ;    // [long  ,    9] ���ϴ��                        StartPos 44, Length 9
    char    diff                [   6];    char    _diff                ;    // [float ,  6.2] �����                          StartPos 54, Length 6
    char    volume              [  10];    char    _volume              ;    // [long  ,   10] �ŷ���                          StartPos 61, Length 10
} t1833OutBlock1, *LPt1833OutBlock1;
#define NAME_t1833OutBlock1     "t1833OutBlock1"

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _CSPAT00600data{
    char    *strAcntNo              ;    // [string,   20] ���¹�ȣ                        StartPos 5, Length 20
    char    *strInptPwd             ;    // [string,    8] �Էº�й�ȣ                    StartPos 25, Length 8
    char    *strIsuNo               ;    // [string,   12] �����ȣ                        StartPos 33, Length 12
    char    *strOrdQty              ;    // [long  ,   16] �ֹ�����                        StartPos 45, Length 16
    char    *strOrdPrc              ;    // [double, 13.2] �ֹ���                          StartPos 61, Length 13
    char    *strBnsTpCode           ;    // [string,    1] �Ÿű���                        StartPos 74, Length 1
    char    *strOrdprcPtnCode       ;    // [string,    2] ȣ�������ڵ�                    StartPos 75, Length 2
    char    *strMgntrnCode          ;    // [string,    3] �ſ�ŷ��ڵ�                    StartPos 83, Length 3
    char    *strLoanDt              ;    // [string,    8] ������                          StartPos 86, Length 8
    char    *strOrdCndiTpCode       ;    // [string,    1] �ֹ����Ǳ���                    StartPos 97, Length 1
}CSPAT00600data;

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
    data_1833 *d_1833;
    QVector<data_1833 *> vector_1833;
    bool buy_flag;

    bool ETK_Connect(int type);
    bool ETK_Login(QByteArray Qid,QByteArray Qpasswd,QByteArray Qauthpasswd);
    int ETK_Request(char * pszCode,void *lpData,int nDataSize,BOOL bNext,char * pszNextKey,int nTimeOut);
    int ETK_RequestService(char * pszCode, char *pszData);
    void ETK_ReleaseMessageData(LPARAM lp);
    void ETK_ReleaseRequestData(int nRequestID);
    void SetPacketData( char * psData, int nSize, char * pszSrc, int nType, int nDotPos = 0);
    int t1452_Request(BOOL bNext);
    void func_t1452outblock(LPRECV_PACKET pRpData);
    void func_t1452outblock1(LPRECV_PACKET pRpData);

    void func_t1833outblock(LPRECV_PACKET pRpData);
    void func_t1833outblock1(LPRECV_PACKET pRpData);

    void func_CSPAT00600OutBlock2(LPRECV_PACKET pRpData);

    int CSPAT00600_Request(BOOL nNext,CSPAT00600data data);

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
    typedef int		(*FP_REQUESTSERVICE			) ( HWND, char *, char *);

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
    FP_REQUESTSERVICE			m_fpRequestService;
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
