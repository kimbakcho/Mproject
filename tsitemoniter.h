#ifndef TSITEMONITER_H
#define TSITEMONITER_H

#include <QObject>
#include <QThread>

class tsitemoniter : public QThread
{
    Q_OBJECT
public:
    explicit tsitemoniter();
    bool m_stopflag;
    QString urlsite;
    int tempsitecount;
    int sleeptime;
    QString cycletime;

private:
    void run();

signals:
    void loadurl();

public slots:
};

#endif // TSITEMONITER_H
