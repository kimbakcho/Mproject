#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <xing.h>
#include <QMainWindow>
#include <QPushButton>
#include "xingcom.h"
#include <QHBoxLayout>
extern xing *x1;
extern xingcom *xcom;
class mainframe : public QWidget
{
    Q_OBJECT
public:
    explicit mainframe(QWidget *parent = 0);
    QPushButton *btn1;
    QPushButton *btn2;
    QHBoxLayout hbox;
    void init();
signals:



public slots:
    void testfuntion();
};

#endif // MAINFRAME_H
