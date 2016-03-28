#ifndef MAINFRAME_H
#define MAINFRAME_H


#include <QMainWindow>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QSettings>
#include "tsearch_push.h"
#include "tsearch_res.h"
#include "tsellfrom1833.h"
#include <QCheckBox>


class mainframe : public QWidget
{
    Q_OBJECT
public:
    explicit mainframe(QWidget *parent = 0);
    QPushButton *btn1;
    QPushButton *btn2;
    QHBoxLayout *hbox1;
    QHBoxLayout *hbox2;
    QVBoxLayout *vbox1;
    QGridLayout *gbox1;
    QLabel *label1;
    Tsearch_push *tpush;
    Tsearch_res *trecv;
    QLabel *QAcntNo;
    QLabel *QInptPwd;
    QLabel *QIsuNo;
    QLabel *QOrdQty;
    QLabel *QOrdPrc;
    QLabel *QBnsTpCode;
    QLabel *QOrdprcPtnCode;
    QLabel *QMgntrnCode;
    QLabel *QOrdCndiTpCode;
    QLineEdit *QLLQAcntNo;
    QLineEdit *QLInptPwd;
    QLineEdit *QLIsuNo;
    QLineEdit *QLOrdQty;
    QLineEdit *QLOrdPrc;
    QLineEdit *QLBnsTpCode;
    QLineEdit *QLOrdprcPtnCode;
    QLineEdit *QLMgntrnCode;
    QLineEdit *QLOrdCndiTpCode;
    QHBoxLayout *QHAcntNo;
    QHBoxLayout *QHInptPwd;
    QHBoxLayout *QHIsuNo;
    QHBoxLayout *QHOrdQty;
    QHBoxLayout *QHOrdPrc;
    QHBoxLayout *QHBnsTpCode;
    QHBoxLayout *QHOrdprcPtnCode;
    QHBoxLayout *QHMgntrnCode;
    QHBoxLayout *QHOrdCndiTpCode;
    QLabel *Qaccount;
    QLineEdit *QLaccount;
    QCheckBox *Qusebuy;
    QLabel *QLusebuy;

    QPushButton *functiontestbtn1;


    TSellfrom1833 *tsf1833;

    QLineEdit *rich_address;
    QLabel *rich_label;


    void init();
signals:



public slots:
    void t1833_request();
    void QLLQAcntNo_change(QString str);
    void QLInptPwd_change(QString str);
    void QLaccount_change(QString str);
    void Qusebuy_change(bool data);
    void functiontestbtn1_push();
};

#endif // MAINFRAME_H
