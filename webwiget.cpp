#include "webwiget.h"
#include "mainframe.h"
extern mainframe *mf;

webwiget::webwiget()
{

    load(QUrl("http://rich-stock.com/"));
    qwf = this->page()->mainFrame();
    connect(this,SIGNAL(loadFinished(bool)),this,SLOT(finishedpage(bool)));
    findstr1 =kor("매수가");
    findstr2 =kor("손절가");
    findstr3 =kor("1차목표");
    findstr4 =kor("대응");

    initurl = "http://rich-stock.com/freer/?p_url=freer_1&B_Name=center&b_dir=talkclub&category=freer_1&b_url=contents&list_no=%1";


    file = new QFile();
    filename = "C:\\shcodedata.txt";
    file->setFileName(filename);
    file->open(QIODevice::ReadOnly);
    QStringList shcode_result;
    QTextStream read(file);
    while(!read.atEnd()){
        QString temp = read.readLine();
        shcode_result = temp.split(",");
        shcodemap.insert(shcode_result.at(0),shcode_result.at(1));
    }


}
int webwiget::getparser(){

    QNetworkAccessManager *network = new QNetworkAccessManager();
    QNetworkRequest requ;
    requ.setUrl(QUrl("http://rich-stock.com/member/log_in_ok.asp"));
    QByteArray postdata_2;
    load(requ,QNetworkAccessManager::PostOperation,postdata_2);
    //QString tempurl = initurl.arg(mf->rich_address->text());
    //load(QUrl(tempurl));
    //setVisible(0);
    return 0;

}
void webwiget::finishedpage(bool flag){
    QString str = this->url().toString();
    int str_result= str.indexOf("category=freer_1");

    if(flag && (str_result!= -1)){
        document = qwf->documentElement();
        QWebElementCollection result_1;
        QWebElement result_2;
        QString str_result;
        QStringList strlist_result;
        int reusult_4[4];
        result_1 = document.findAll(".re_comment dl dd TEXTAREA");

        for(int i=0;i<result_1.count();i++){
            result_2 = result_1.at(i);
            str_result= result_2.toPlainText();
            reusult_4[0] =str_result.indexOf(findstr1);
            reusult_4[1] =str_result.indexOf(findstr2);
            reusult_4[2] =str_result.indexOf(findstr3);
            reusult_4[3] =str_result.indexOf(findstr4);
            if((reusult_4[0] != -1)&&(reusult_4[1] != -1)&&(reusult_4[2] != -1)&&(reusult_4[3] != -1)){
                strlist_result =  str_result.split("\t");
                QString hname_temp = strlist_result.at(0);

                if(!richdatamap.contains(hname_temp)){
                    rich_data *tempdata = new rich_data();
                    tempdata->hname = strlist_result.at(0);
                    tempdata->price = strlist_result.at(2);
                    tempdata->loss = strlist_result.at(4);
                    tempdata->obj = strlist_result.at(6);
                    richdatamap.insert(strlist_result.at(0),tempdata);
                    QString shcode_temp;
                    shcode_temp= shcodemap.value(tempdata->hname);
                    get_time = QTime::currentTime();
                    qDebug()<<kor("not contain name : %1 price : %2 loos : %3 1ob : %4 shcode = %5 time = %6 ")
                              .arg(strlist_result.at(0)).arg(strlist_result.at(2)).arg(strlist_result.at(4)).arg(strlist_result.at(6)).arg(shcode_temp).arg(get_time.toString("hh:mm:ss"));
                    qDebug()<<kor("----------------------------------------");
                }
        }
        QString tempur2 = initurl.arg(mf->rich_address->text());
        load(QUrl(tempur2));
        }
    }
}

