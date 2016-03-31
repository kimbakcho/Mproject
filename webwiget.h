#ifndef WEBWIGET_H
#define WEBWIGET_H

#include <QWidget>
#include <QWebView>
#include <QtWebKit>
#include <QWebFrame>
#include <QUrl>
#include <QWebElement>
#include <QStringList>
#include <QDebug>
#include <QWebElementCollection>
#include <QWebElement>
#include <QMap>
#include <rich_data.h>
#include <QTime>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include "./packet/CSPAT00600.h"


#define kor(str) QString::fromLocal8Bit(str)

class webwiget : public QWebView
{
    Q_OBJECT
public:
    explicit webwiget();
    QWebFrame *qwf;
    QWebElement document;
    int getparser();
    void getparser1();

    QStringList result_2;
    QString findstr1;
    QString findstr2;
    QString findstr3;
    QString findstr4;
    QMap<QString,rich_data *> richdatamap;
    QMap<QString,QString> shcodemap;
    QTime get_time;
    QDate get_date;
    QFile *file;
    QString filename;
    QString initurl;
    QString urllastsite;
    int siteplaycount;

signals:

public slots:
    void finishedpage(bool flag);
    void autostep();
    void loadprogressslot(int progress);
    void tsitemoniterslot();

};

#endif // WEBWIGET_H
