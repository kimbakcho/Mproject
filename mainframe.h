#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <xing.h>
#include <QMainWindow>
#include <QPushButton>
#include "xingcom.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
extern xing *x1;
extern xingcom *xcom;
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
    void setlabel1(QString str);
    void init();
signals:



public slots:
    void testfuntion();
};

#endif // MAINFRAME_H
