#ifndef LOGINWIGET_H
#define LOGINWIGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <windows.h>

#include <QDebug>
#include <xingapi.h>

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
    HWND hWnd1;//library main handler from XINGAPI
    bool nativeEvent(const QByteArray & eventType, void * message, long * result);
private slots:
    void loginfuntion();

};

#endif // LOGINWIGET_H
