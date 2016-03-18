#include "xingcom.h"

xingcom::xingcom(QObject *parent) : QObject(parent)
{
    if (QLibrary::isLibrary("XA_Session.dll")) {
      lib.setFileName("XA_Session.dll");
      lib.load();
      m_connectserver = (COM_ConnectServer)lib.resolve("ConnectServer");

      if (!lib.isLoaded()) {
        qDebug() << lib.errorString();

      }


    }
}

