#ifndef MAINFRAME_H
#define MAINFRAME_H


#include <QMainWindow>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "tsearch_push.h"
#include "tsearch_res.h"


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
    QLabel *label1;
    Tsearch_push *tpush;
    Tsearch_res *trecv;
    void init();
signals:



public slots:
    void t1833_request();
};

#endif // MAINFRAME_H
