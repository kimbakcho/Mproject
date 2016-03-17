#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <xing.h>
#include <QMainWindow>
#include <QPushButton>
extern xing *x1;

class mainframe : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainframe(QWidget *parent = 0);
    QPushButton *btn1;
    void init();
signals:



public slots:
    void testfuntion();
};

#endif // MAINFRAME_H
