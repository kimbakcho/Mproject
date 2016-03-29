#ifndef TRICHQUERY_PUSH_H
#define TRICHQUERY_PUSH_H

#include <QObject>
#include <QTime>
#include <QThread>
#include <QDebug>

class trichquery_push : public QThread
{
    Q_OBJECT
public:

    explicit trichquery_push();
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
    void palyonsignal();

public slots:
};

#endif // TRICHQUERY_PUSH_H
