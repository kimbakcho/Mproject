#include "mainwindow.h"
#include "loginwiget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Loginwiget w1;
    w1.show();

    return a.exec();
}
