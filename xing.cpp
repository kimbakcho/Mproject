#include "xing.h"

xing::xing(QWidget *parent) : QWidget(parent)
{
    htsip = "hts.ebestsec.co.kr";
    demoip = "demo.ebestsec.co.kr";
    serverport = 20001;
    serverip = htsip.toLocal8Bit();


}
bool xing::init()
{
    if (QLibrary::isLibrary("xingAPI.dll")) {
      lib.setFileName("xingAPI.dll");
      lib.load();
      m_fpConnect = (FP_CONNECT)lib.resolve("ETK_Connect");
//      m_fpIsConnected = (FP_ISCONNECTED)lib.resolve("ETK_IsConnected");
//      m_fpDisconnect = (FP_DISCONNECT)lib.resolve("ETK_Disconnect");
//      m_fpLogin = (FP_LOGIN)lib.resolve("ETK_Login");
//      m_fpGetLastError = (FP_GETLASTERROR)lib.resolve("ETK_GetLastError");
//      m_fpGetErrorMessage = (FP_GETERRORMESSAGE)lib.resolve("ETK_GetErrorMessage");
//      m_fpRequest = (FP_REQUEST)lib.resolve("ETK_Request");
//      m_fpAdviseRealData = (FP_ADVISEREALDATA)lib.resolve("ETK_AdviseRealData");
//      m_fpUnadviseRealData = (FP_UNADVISEREALDATA)lib.resolve("ETK_UnadviseRealData");
//      m_fpUnadviseWindow = (FP_UNADVISEWINDOW)lib.resolve("ETK_UnadviseWindow");
//      m_fpReleaseRequestData = (FP_RELEASEREQUESTDATA)lib.resolve("ETK_ReleaseRequestData");
//      m_fpGetAccountListCount = (FP_GETACCOUNTLISTCOUNT)lib.resolve("ETK_GetAccountListCount");
//      m_fpGetAccountList = (FP_GETACCOUNTLIST)lib.resolve("ETK_GetAccountList");
//      m_fpGetCommMedia = (FP_GETCOMMMEDIA)lib.resolve("ETK_GetCommMedia");
//      m_fpGetETKMedia = (FP_GETETKMEDIA)lib.resolve("ETK_GetETKMedia");
//      m_fpGetClientIP = (FP_GETCLIENTIP)lib.resolve("ETK_GetClientIP");
//      m_fpGetServerName = (FP_GETSERVERNAME)lib.resolve("ETK_GetServerName");
//      m_fpSetHeaderInfo = (FP_SETHEADERINFO)lib.resolve("ETK_SetHeaderInfo");
      if (!lib.isLoaded()) {
        qDebug() << lib.errorString();
        return false;
      }
    }
    //set handler
    set_windid((HWND)winId());
    eeconnect();

    return true;
}
void xing::set_windid(HWND data){
    this->xing_winid = data;
}
HWND xing::get_windid(){
    return this->xing_winid;
}
void xing::eeconnect() {
    //type 1 is hts.ebestsec.co.kr connect 실투자
    //type 0 is demo.ebestsec.co.kr connect 모의투자
    m_fpConnect((HWND)winId(),serverip,serverport,WM_USER,10000,-1);

}
// it is furntion for Message handler
bool xing::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    switch (msg->message) {
    case WM_USER+XM_LOGIN:

        break;
    default:
        break;
    }
    return false;

}
