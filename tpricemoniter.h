#ifndef TPRICEMONITER_H
#define TPRICEMONITER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QDebug>
#include <QString>

class tpricemoniter : public QThread
{
    Q_OBJECT
public:
    explicit tpricemoniter();
    bool m_stopflag;
    QList<QString> mapkeylist;



private:
    void run();



signals:

public slots:
};

#endif // TPRICEMONITER_H
