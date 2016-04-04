#include "webwiget.h"
#include "mainframe.h"
#include "xing.h"
extern mainframe *mf;
extern xing *x1;


webwiget::webwiget()
{

   load(QUrl("http://rich-stock.com/"));

    qwf = this->page()->mainFrame();

    connect(this,SIGNAL(loadFinished(bool)),this,SLOT(finishedpage(bool)));
 //   connect(this,SIGNAL(loadProgress(int)),this,SLOT(loadprogressslot(int)));

    findstr1 =kor("매수가");
    findstr2 =kor("손절가");
    findstr3 =kor("1차목표");
    findstr4 =kor("대응");

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
    siteplaycount = 0;
    urllastsite="http://rich-stock.com";
    vipcheck = false;

}
int webwiget::getparser(){
    QNetworkRequest requ;
    requ.setUrl(QUrl("http://rich-stock.com/member/log_in_ok.asp"));
    requ.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    QByteArray postdata_2;
    postdata_2.append("M_ID=vngkgk624&M_Password=super624");
    load(requ,QNetworkAccessManager::PostOperation,postdata_2);
    return 0;
}
void webwiget::autostep(){
    QNetworkRequest requ;
    requ.setUrl(QUrl("http://rich-stock.com/member/log_in_ok.asp"));
    requ.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    QByteArray postdata_2;
    postdata_2.append("M_ID=vngkgk624&M_Password=super624");
    load(requ,QNetworkAccessManager::PostOperation,postdata_2);
}

void webwiget::getparser1(){
    QString tempurl = initurl.arg(mf->rich_address->text());
    load(QUrl(tempurl));
    setVisible(0);
}

void webwiget::finishedpage(bool flag){

    if(mf != NULL){
        vipcheck = mf->Qsitevipcheck->isChecked();
    }
    if(vipcheck){
        findstr1 =kor("[신규 추천 종목]");
        findstr2 =kor("목표가");
        findstr3 =kor("매수");
        findstr4 =kor("비중");
    }
    QString str = this->url().toString();
    int str_result= str.indexOf("&b_url=contents&list_no=");
    int str_result_1 = str.indexOf("&b_url=list&category=freer_1");
    int str_result_2 = str.indexOf("index.asp");
    siteplaycount++;
    urllastsite = str;


    qDebug()<<kor("site = %1").arg(str);
    if(str.compare("about:blank")==0){
        urllastsite = "http://rich-stock.com";
    }

    if(flag && (str_result!= -1) && mf->Quseautostep->isChecked()){
        document = qwf->documentElement();
        QWebElementCollection result_1;
        QWebElementCollection time_result_1;
        QWebElement result_2;
        QWebElement time_result_2;
        QString str_result;
        QString time_str_result;
        QStringList strlist_result;
        int reusult_4[4];
        QStringList pricesplit;
        QString pricetemp;
        QStringList losspricesplit;
        QString losspricetemp;
        QStringList objpricesplit;
        QString objpricetemp;
        result_1 = document.findAll(".re_comment dl dd TEXTAREA");



        for(int i=0;i<result_1.count();i++){
            result_2 = result_1.at(i);

            str_result= result_2.toPlainText();

            reusult_4[0] =str_result.indexOf(findstr1);
            reusult_4[1] =str_result.indexOf(findstr2);
            reusult_4[2] =str_result.indexOf(findstr3);
            reusult_4[3] =str_result.indexOf(findstr4);
            if((reusult_4[0] != -1)&&(reusult_4[1] != -1)&&(reusult_4[2] != -1)&&(reusult_4[3] != -1)){
                if(vipcheck){
                    strlist_result =  str_result.split("\n\n");
                }else {
                    strlist_result =  str_result.split("\t");
                }
                time_result_1 = document.findAll(".re_comment dl dt");
                time_result_2 = time_result_1.at(i);
                time_str_result = time_result_2.toPlainText();
                QStringList time_result_3 = time_str_result.split(" ");

                QString time_result_4 = time_result_3.at(2);
                QString time_result_5 = time_result_4.mid(0,5);
                QStringList time_result_6 = time_result_5.split(":");
                QString reply_timeh = time_result_6.at(0);
                QString reply_timem = time_result_6.at(1);

                QTime reply_time;
                reply_time.setHMS(reply_timeh.toInt(),reply_timem.toInt()+1,3);

                int i_reply_time = QTime(0,0,0).secsTo(reply_time);


                QString hname_temp;
                if(vipcheck){
                    QString temp_result1 = strlist_result.at(1);
                    QStringList temp_result1_list = temp_result1.split(" ");
                    hname_temp = temp_result1_list.at(0);
                    pricetemp = temp_result1_list.at(1);
                }else{
                    hname_temp = strlist_result.at(0);
                }

                QString shcode_temp;
                shcode_temp= shcodemap.value(hname_temp);
                int value_test = richdatamap.size();

                if(!richdatamap.contains(shcode_temp)){
                    rich_data *tempdata = new rich_data();
                    tempdata->hname = hname_temp;
                    if(!vipcheck){
                        pricetemp = strlist_result.at(2);
                        pricesplit = pricetemp.split(kor("원"));
                        tempdata->price = pricesplit.at(0);
                        losspricetemp = strlist_result.at(4);
                        losspricesplit = losspricetemp.split(kor("원"));
                        tempdata->loss = losspricesplit.at(0);
                        objpricetemp = strlist_result.at(6);
                        objpricesplit = objpricetemp.split(kor("원"));
                        tempdata->obj = objpricesplit.at(0);
                    }else {

                        pricesplit = pricetemp.split(kor("원"));
                        tempdata->price = pricesplit.at(0);
                        tempdata->price.replace(",","");
                        double d_price = tempdata->price.toDouble();
                        double d_loss = d_price - (d_price*0.015);
                        int i_loss = (int)d_loss;
                        tempdata->loss = QString("%1").arg(i_loss);
                        double d_obj = d_price + (d_price*0.015);
                        int i_obj = (int)d_obj;
                        tempdata->obj = QString("%1").arg(i_obj);

                    }

                    tempdata->shcode = shcode_temp;


                    get_time = QTime::currentTime();

                    if(vipcheck){
                        qDebug()<<kor("not contain name : %1 price : %2 loos : %3 1ob : %4 shcode = %5 time = %6 ")
                                  .arg(tempdata->hname).arg(tempdata->price).arg(tempdata->loss).arg(tempdata->obj).arg(tempdata->shcode).arg(get_time.toString("hh:mm:ss"));
                        qDebug()<<kor("----------------------------------------");
                    }else{
                        qDebug()<<kor("not contain name : %1 price : %2 loos : %3 1ob : %4 shcode = %5 time = %6 ")
                                  .arg(strlist_result.at(0)).arg(strlist_result.at(2)).arg(strlist_result.at(4)).arg(strlist_result.at(6)).arg(shcode_temp).arg(get_time.toString("hh:mm:ss"));
                        qDebug()<<kor("----------------------------------------");
                    }
                    //매수
                    QByteArray qb_temp[10];
                    CSPAT00600data data;
                    QString price = tempdata->price;
                    QString tpcode = "2";
                    QString prcptncode = "00";
                    QString mgntrncode = "000";
                    QString loandt ="";
                    QString ordcnditpcode = "0";
                    QString ju_count;
                    int real_price;
                    int real_money;
                    int total_ordqty;
                    qb_temp[0] = shcode_temp.toLocal8Bit();
                    data.strIsuNo = qb_temp[0].data();

                    qb_temp[1] = mf->QLInptPwd->text().toLocal8Bit();
                    data.strInptPwd = qb_temp[1].data();

                    qb_temp[2] = mf->QLLQAcntNo->text().toLocal8Bit();
                    data.strAcntNo = qb_temp[2].data();

                    //price qty
                    real_price = price.toInt();
                    real_money = mf->QLaccount->text().toInt();
                    total_ordqty = real_money/real_price;
                    ju_count.sprintf("%d",total_ordqty);
                    qb_temp[3] = ju_count.toLocal8Bit();
                    data.strOrdQty = qb_temp[3].data();

                    //price
                    qb_temp[4] = price.toLocal8Bit();
                    data.strOrdPrc = qb_temp[4].data();

                    //BnsTpCode
                    qb_temp[5] = tpcode.toLocal8Bit();
                    data.strBnsTpCode = qb_temp[5].data();

                     //OrdprcPtnCode
                    qb_temp[6] = prcptncode.toLocal8Bit();
                    data.strOrdprcPtnCode = qb_temp[6].data();

                     //MgntrnCode
                    qb_temp[7] = mgntrncode.toLocal8Bit();
                    data.strMgntrnCode = qb_temp[7].data();

                    //LoanDt
                    qb_temp[8] = loandt.toLocal8Bit();
                    data.strLoanDt = qb_temp[8].data();

                     //OrdCndiTpCode
                    qb_temp[9] = ordcnditpcode.toLocal8Bit();
                    data.strOrdCndiTpCode = qb_temp[9].data();
                    if(mf->Qusebuy->isChecked()){
                        int result_3 = 0;
                        if(i_reply_time>=QTime(0,0,0).secsTo(get_time)){
                            result_3 = x1->CSPAT00600_Request(true,data);
                        }
                        if(result_3){
                            richdatamap.insert(tempdata->shcode,tempdata);
                            QByteArray qt_temp_1;
                            t1101InBlockdata data_1;
                            qt_temp_1 = QString(tempdata->shcode).toLocal8Bit();
                            data_1.shcode = qt_temp_1.data();
                            x1->t1101_Request(true,data_1);
                        }
                    }
                }
            }
        }
        //QString tempur2 = initurl.arg(mf->rich_address->text());
        load(QUrl(str));
    }


    else if(flag && (str_result_1 != -1)&& mf->Quseautostep->isChecked() && !vipcheck){
        QWebElementCollection index_result_1;
        QWebElement index_result_2;
        QString index_result_3;
        QStringList index_result_4;
        int daycompare[3];
        document = qwf->documentElement();
        index_result_1 = document.findAll(".table_board tr td a");
        index_result_2 = index_result_1.at(1);
        index_result_3= index_result_2.toPlainText();
        index_result_3.replace(kor("년"),",");
        index_result_3.replace(kor("월"),",");
        index_result_3.replace(kor("일"),",");
        index_result_3.replace(" ","");
        index_result_3.replace(kor("■"),"");
        index_result_4 = index_result_3.split(",");
        get_date = QDate::currentDate();
        daycompare[0] =2000+((QString)index_result_4.at(0)).toInt();
        daycompare[1] =((QString)index_result_4.at(1)).toInt();
        daycompare[2] =((QString)index_result_4.at(2)).toInt();
        QString link_url = index_result_1.at(1).attribute("href");
        QString link_go = QString("http://rich-stock.com/freer/%1").arg(link_url);

        if((daycompare[0] == get_date.year())&&
                (daycompare[1] == get_date.month()) &&
                (daycompare[2] == get_date.day())){
                load(QUrl(link_go));
        }else{
                load(QUrl("http://rich-stock.com/freer/?p_url=freer_1&B_Name=center&b_dir=talkclub&b_url=list&category=freer_1"));
        }
    }else if(flag && (str_result_2!= -1) && mf->Quseautostep->isChecked() && !vipcheck){
        load(QUrl("http://rich-stock.com/freer/?p_url=freer_1&B_Name=center&b_dir=talkclub&b_url=list&category=freer_1"));
    }else if(flag && (str_result_2!= -1) && mf->Quseautostep->isChecked() && vipcheck){
        QWebElementCollection index_result_1;
        QWebElement index_result_2;
        QString index_result_3;
        QStringList index_result_4;
        int daycompare[3];
        document = qwf->documentElement();
        index_result_1 = document.findAll(".main_board_wrap tr td a");
        index_result_2 = index_result_1.at(0);
        index_result_3= index_result_2.toPlainText();
        index_result_3.replace(kor("년"),",");
        index_result_3.replace(kor("월"),",");
        index_result_3.replace(kor("일"),",");
        index_result_3.replace(" ","");
        index_result_3.replace(kor("■"),"");
        index_result_4 = index_result_3.split(",");
        get_date = QDate::currentDate();
        daycompare[0] =2000+((QString)index_result_4.at(0)).toInt();
        daycompare[1] =((QString)index_result_4.at(1)).toInt();
        daycompare[2] =((QString)index_result_4.at(2)).toInt();
        QString link_url = index_result_1.at(0).attribute("href");
        QStringList link_url_value = link_url.split("&");
        QString result_link_url = link_url_value.at(5);
        QString link_go = QString("http://rich-stock.com/freer/?dir_in=&p_url=freer_1&B_Name=center&b_dir=talkclub&category=freer_1&search=&searchstring=&b_url=contents&%1").arg(result_link_url);

        if((daycompare[0] == get_date.year())&&
                (daycompare[1] == get_date.month()) &&
                (daycompare[2] == get_date.day())){
                load(QUrl(link_go));
        }else{
                load(QUrl("http://rich-stock.com/index.asp"));
        }
    }else if(!flag) {
        load(QUrl(str));
    }
}


void webwiget::loadprogressslot(int progress){
      qDebug()<<QString("load progress = %1").arg(progress);
      QString str = this->url().toString();
      int str_result= str.indexOf("&b_url=contents&list_no=");
      int str_result_1 = str.indexOf("&b_url=list&category=freer_1");
      int str_result_2 = str.indexOf("index.asp");
      bool flag= false;

      if(progress>75){
          flag = true;
          qDebug()<<kor("site = %1").arg(str);
      }

      if(flag && (str_result!= -1) && mf->Quseautostep->isChecked()){
          document = qwf->documentElement();
          QWebElementCollection result_1;
          QWebElement result_2;
          QString str_result;
          QStringList strlist_result;
          int reusult_4[4];
          QStringList pricesplit;
          QString pricetemp;
          QStringList losspricesplit;
          QString losspricetemp;
          QStringList objpricesplit;
          QString objpricetemp;
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
                      pricetemp = strlist_result.at(2);
                      pricesplit = pricetemp.split(kor("원"));
                      tempdata->price = pricesplit.at(0);
                      losspricetemp = strlist_result.at(4);
                      losspricesplit = losspricetemp.split(kor("원"));
                      tempdata->loss = losspricesplit.at(0);
                      objpricetemp = strlist_result.at(6);
                      objpricesplit = objpricetemp.split(kor("원"));
                      tempdata->obj = objpricesplit.at(0);

                      QString shcode_temp;
                      shcode_temp= shcodemap.value(tempdata->hname);
                      tempdata->shcode = shcode_temp;


                      get_time = QTime::currentTime();
                      qDebug()<<kor("not contain name : %1 price : %2 loos : %3 1ob : %4 shcode = %5 time = %6 ")
                                .arg(strlist_result.at(0)).arg(strlist_result.at(2)).arg(strlist_result.at(4)).arg(strlist_result.at(6)).arg(shcode_temp).arg(get_time.toString("hh:mm:ss"));
                      qDebug()<<kor("----------------------------------------");
                      //매
                      QByteArray qb_temp[10];
                      CSPAT00600data data;
                      QString price = tempdata->price;
                      QString tpcode = "2";
                      QString prcptncode = "00";
                      QString mgntrncode = "000";
                      QString loandt ="";
                      QString ordcnditpcode = "0";
                      QString ju_count;
                      int real_price;
                      int real_money;
                      int total_ordqty;
                      qb_temp[0] = shcode_temp.toLocal8Bit();
                      data.strIsuNo = qb_temp[0].data();

                      qb_temp[1] = mf->QLInptPwd->text().toLocal8Bit();
                      data.strInptPwd = qb_temp[1].data();

                      qb_temp[2] = mf->QLLQAcntNo->text().toLocal8Bit();
                      data.strAcntNo = qb_temp[2].data();

                      //price qty
                      real_price = price.toInt();
                      real_money = mf->QLaccount->text().toInt();
                      total_ordqty = real_money/real_price;
                      ju_count.sprintf("%d",total_ordqty);
                      qb_temp[3] = ju_count.toLocal8Bit();
                      data.strOrdQty = qb_temp[3].data();

                      //price
                      qb_temp[4] = price.toLocal8Bit();
                      data.strOrdPrc = qb_temp[4].data();

                      //BnsTpCode
                      qb_temp[5] = tpcode.toLocal8Bit();
                      data.strBnsTpCode = qb_temp[5].data();

                       //OrdprcPtnCode
                      qb_temp[6] = prcptncode.toLocal8Bit();
                      data.strOrdprcPtnCode = qb_temp[6].data();

                       //MgntrnCode
                      qb_temp[7] = mgntrncode.toLocal8Bit();
                      data.strMgntrnCode = qb_temp[7].data();

                      //LoanDt
                      qb_temp[8] = loandt.toLocal8Bit();
                      data.strLoanDt = qb_temp[8].data();

                       //OrdCndiTpCode
                      qb_temp[9] = ordcnditpcode.toLocal8Bit();
                      data.strOrdCndiTpCode = qb_temp[9].data();
                      if(mf->Qusebuy->isChecked()){
                          int result_3 = x1->CSPAT00600_Request(true,data);
                          if(result_3){
                              richdatamap.insert(tempdata->shcode,tempdata);
                              QByteArray qt_temp_1;
                              t1101InBlockdata data_1;
                              qt_temp_1 = QString(tempdata->shcode).toLocal8Bit();
                              data_1.shcode = qt_temp_1.data();
                              x1->t1101_Request(true,data_1);
                          }
                      }
                  }
              }
          }
          //QString tempur2 = initurl.arg(mf->rich_address->text());
          load(QUrl(str_result));
      }


      else if(flag && (str_result_1 != -1)&& mf->Quseautostep->isChecked()){
          QWebElementCollection index_result_1;
          QWebElement index_result_2;
          QString index_result_3;
          QStringList index_result_4;
          int daycompare[3];
          document = qwf->documentElement();
          index_result_1 = document.findAll(".table_board tr td a");
          index_result_2 = index_result_1.at(1);
          index_result_3= index_result_2.toPlainText();
          index_result_3.replace(kor("년"),",");
          index_result_3.replace(kor("월"),",");
          index_result_3.replace(kor("일"),",");
          index_result_3.replace(" ","");
          index_result_3.replace(kor("■"),"");
          index_result_4 = index_result_3.split(",");
          get_date = QDate::currentDate();
          daycompare[0] =2000+((QString)index_result_4.at(0)).toInt();
          daycompare[1] =((QString)index_result_4.at(1)).toInt();
          daycompare[2] =((QString)index_result_4.at(2)).toInt();
          QString link_url = index_result_1.at(1).attribute("href");
          QString link_go = QString("http://rich-stock.com/freer/%1").arg(link_url);

          if((daycompare[0] == get_date.year())&&
                  (daycompare[1] == get_date.month()) &&
                  (daycompare[2] == get_date.day())){
                  load(QUrl(link_go));
          }else{
                  load(QUrl("http://rich-stock.com/freer/?p_url=freer_1&B_Name=center&b_dir=talkclub&b_url=list&category=freer_1"));
          }
      }else if(flag && (str_result_2!= -1) && mf->Quseautostep->isChecked()){
          load(QUrl("http://rich-stock.com/freer/?p_url=freer_1&B_Name=center&b_dir=talkclub&b_url=list&category=freer_1"));
      }else if(!flag) {

      }
}
void webwiget::tsitemoniterslot(){
    if(!(urllastsite.compare("")<0)){
         load(QUrl(urllastsite));
    }

}
