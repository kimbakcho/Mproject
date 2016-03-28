#include "webwiget.h"

webwiget::webwiget()
{
    load(QUrl("http://rich-stock.com/"));

}
int webwiget::getparser(){
    qwf = this->page()->mainFrame();
    document = qwf->documentElement();
    QWebElementCollection result_1;
    QWebElement result_2;

    result_1 = document.findAll("div.recomment");
    for(int i=0;i<result_1.count();i++){
        result_2 = result_1.at(i);
        qDebug()<<QString("names %1").arg(result_2.attribute("id"));

    }
    return 0;

}

