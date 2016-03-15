#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QLabel *lbid;
    QLabel *lbpw;
    QLabel *lbaupw;
    QPushButton *pbjoin;
    QLineEdit *leid;
    QLineEdit *lepw;
    QLineEdit *leaupw;
    QHBoxLayout *hbl_1;
    QHBoxLayout *hbl_2;
    QHBoxLayout *hbl_3;
    QVBoxLayout *vbl_1;
};

#endif // MAINWINDOW_H
