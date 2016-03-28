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
class webwiget : public QWebView
{
    Q_OBJECT
public:
    explicit webwiget();
    QWebFrame *qwf;
    QWebElement document;
    int getparser();
    QStringList result_2;

signals:

public slots:
};

#endif // WEBWIGET_H
