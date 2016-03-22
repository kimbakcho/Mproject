#ifndef TSEARCH_RES_H
#define TSEARCH_RES_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#define PLAY 1
#define STOP 0
class Tsearch_res : public QThread
{
    Q_OBJECT
public:
    explicit Tsearch_res();
    QMutex m_mutex;
    QWaitCondition m_waitcondition;
    void resume();
    bool m_mflag;
    bool m_recvmflag;
    int recv_result;

private:
    void run();

signals:

public slots:
};

#endif // TSEARCH_RES_H
