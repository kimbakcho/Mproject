#ifndef LOGINWIGET_H
#define LOGINWIGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <mainframe.h>
#include <QSettings>
#include "xing.h"
#include "xingcom.h"
#define kor(str) QString::fromLocal8Bit(str)
extern xing *x1;
extern mainframe *mf;
extern xingcom *xcom;
class Loginwiget : public QWidget
{
    Q_OBJECT
public:
    explicit Loginwiget(QWidget *parent = 0);
signals:

public slots:

private:
    QLabel *lbid;
    QLabel *lbpw;
    QLabel *lbaupw;
    QPushButton *pbjoin;
    QLineEdit *leid;
    QLineEdit *lepw;
    QLineEdit *leaupw;
    QGridLayout *glay_1;
private slots:
    void loginfuntion();

};

#endif // LOGINWIGET_H
