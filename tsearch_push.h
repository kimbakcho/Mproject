#ifndef TSEARCH_PUSH_H
#define TSEARCH_PUSH_H

#include <QObject>
#include <QTime>
#include <QThread>

#include <QDebug>
#include "tsearch_res.h"

#define STOP 0
#define PLAY 1



class Tsearch_push : public QThread
{
    Q_OBJECT
public:
    explicit Tsearch_push(Tsearch_res *recvth_temp);
    bool m_stopflag;
    QTime time;
    QTime play_time;
    QTime play_end_time;
    int time_sec;
    int play_time_sec;
    int play_end_time_sec;
    bool playtime_flag;
    Tsearch_res *recvth;

private:
    void run();

signals:

public slots:
};

#endif // TSEARCH_PUSH_H
