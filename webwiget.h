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
#include <QFile>
#include <QTextStream>

#define kor(str) QString::fromLocal8Bit(str)

class webwiget : public QWebView
{
    Q_OBJECT
public:
    explicit webwiget();
    QWebFrame *qwf;
    QWebElement document;
    int getparser();
    QStringList result_2;
    QString findstr1;
    QString findstr2;
    QString findstr3;
    QString findstr4;
    QMap<QString,rich_data *> richdatamap;
    QMap<QString,QString> shcodemap;
    QTime get_time;
    QFile *file;
    QString filename;
    QString initurl;

signals:

public slots:
    void finishedpage(bool flag);
};

#endif // WEBWIGET_H
