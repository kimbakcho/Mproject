#ifndef MAINFRAME_H
#define MAINFRAME_H

#define RICH "rich"
#define DAUM "daum"

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
#include "trichquery_push.h"
#include <QComboBox>



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
    trichquery_push *rich_th;

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
    QPushButton *functiontestbtn2;


    TSellfrom1833 *tsf1833;

    QLineEdit *rich_address;
    QLabel *rich_label;

    QLabel *QLuseautostep;
    QCheckBox *Quseautostep;

    QLabel *Qsitepushlabel;
    QPushButton *Qsitepushbutton;

    QLabel *Qsitecycletime;
    QLineEdit *QLEsitecycletime;

    QLabel *Qsitevip;
    QCheckBox *Qsitevipcheck;




    void init();
signals:



public slots:
    void t1833_request();
    void QLLQAcntNo_change(QString str);
    void QLInptPwd_change(QString str);
    void QLaccount_change(QString str);
    void Qusebuy_change(bool data);
    void Quseautostep_change(bool data);
    void functiontestbtn1_push();
    void functiontestbtn2_push();
    void sitepushbtnslot();
    void QLEcycletime_change(QString str);
    void Qvipcheck_change(bool data);

};

#endif // MAINFRAME_H
