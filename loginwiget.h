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
#include <gherder.h>
#include <mainframe.h>
#include <QSettings>
#define kor(str) QString::fromLocal8Bit(str)
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
