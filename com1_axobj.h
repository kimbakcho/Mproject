#ifndef COM1_AXOBJ_H
#define COM1_AXOBJ_H

#include <QObject>
#include <QAxObject>
#include <QDebug>
#include <QMetaMethod>
#include <QAxBase>
#include <QAxWidget>
class com1_axobj : public QAxObject
{
    Q_OBJECT
public:
    explicit com1_axobj();
    void connectNotify(const QMetaMethod & signal);
    bool event(QEvent * e);
    bool doVerb(const QString & verb);

};

#endif // COM1_AXOBJ_H
