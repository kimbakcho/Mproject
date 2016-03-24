#ifndef TSELLFROM1833_H
#define TSELLFROM1833_H

#include <QObject>
#include <QThread>
#include <Qdebug>
class TSellfrom1833 : public QThread
{
    Q_OBJECT
public:
    explicit TSellfrom1833();
    bool m_stopflag;
private:
    void run();

signals:

public slots:
};

#endif // TSELLFROM1833_H
