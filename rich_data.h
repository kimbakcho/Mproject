#ifndef RICH_DATA_H
#define RICH_DATA_H

#include <QObject>
#include <QString>

class rich_data
{

public:
     rich_data();
     QString hname;
     QString price;
     QString loss;
     QString obj;
     QString shcode;
     bool loss_flag = false;

signals:

public slots:
};

#endif // RICH_DATA_H
