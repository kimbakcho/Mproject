#include "xingapi.h"

Xingapi::Xingapi()
{

}
Xingapi::init(){
    if (QLibrary::isLibrary("xingAPI.dll")) {
      QLibrary lib("xingAPI.dll");
      m_fpConnect = (FP_CONNECT)lib.resolve("ETK_Connect");
      m_fpIsConnected = (FP_ISCONNECTED)GetProcAddress(m_hModule, "ETK_IsConnected");
      m_fpLogin = (FP_LOGIN)lib.resolve("ETK_Login");
      if (!lib.isLoaded()) {
        qDebug() << lib.errorString();
      }
    }

}

Xingapi::set_windid(HWND data){
    this->xing_winid = data;
}

