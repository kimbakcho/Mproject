#ifndef TJANGO_TH_H
#define TJANGO_TH_H

#include <QObject>
#include <QTime>
#include <QThread>
#include <QDebug>


class tjango_th : public QThread
{
    Q_OBJECT

public:
    tjango_th();
    bool m_stopflag;
    QTime time;
    QTime play_time;
    QTime play_end_time;
    int time_sec;
    int play_time_sec;
    int play_end_time_sec;
    bool playtime_flag;
private:
    void run();

signals:


public slots:
};

#endif // TJANGO_TH_H
