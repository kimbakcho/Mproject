#include "mainframe.h"

mainframe::mainframe(QWidget *parent) : QMainWindow(parent)
{
    btn1 = new QPushButton(this);
    btn1->setText("push");
    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(testfuntion()));
}
void mainframe::testfuntion(){
    x1->t1452_Request(true);
}

void mainframe::init(){

}
