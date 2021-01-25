#include "goodsinquirywindow.h"
#include "ui_goodsinquirywindow.h"

GoodsInquiryWindow::GoodsInquiryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoodsInquiryWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("序号\t总价\t日期");
    ui->listWidget_2->addItem("序号\t总价\t利润\t日期");
    orderList1 = new QList<QMap<QString,QMap<QString,QString>>>;
    dateList1 = new QList<QString>;
    totalList1 = new QList<QString>;
    orderList2 = new QList<QMap<QString,QMap<QString,QString>>>;
    dateList2 = new QList<QString>;
    totalList2 = new QList<QString>;
    costList = new QList<QString>;

    QFile buyFile("./stocking.json");
    QFile sellFile("./sell.json");
    //读取文件到容器中
    buyFile.open(QIODevice::ReadOnly);
    sellFile.open(QIODevice::ReadOnly);
    QJsonDocument buyDoc = QJsonDocument::fromJson(buyFile.readAll());
    QJsonDocument sellDoc = QJsonDocument::fromJson(sellFile.readAll());
    QJsonObject buyObj = buyDoc.object();
    QJsonObject sellObj = sellDoc.object();
    QJsonArray buyArray = buyObj.value("order").toArray();
    QJsonArray sellArray = sellObj.value("order").toArray();
    for(int i=0;i<buyArray.size();i++)
    {
        QMap<QString, QMap<QString,QString>> map;
        for(auto it=buyArray.at(i).toObject().begin();
                it!=buyArray.at(i).toObject().end();it++)
        {
            if(it.key() == "date")
            {
                dateList1->append(it.value().toString());
            }
            else if(it.key() == "total")
            {
                totalList1->append(it.value().toString());
            }
            else
            {
                QMap<QString, QString> itemMap;
                for(auto it2=it.value().toObject().begin();
                        it2!=it.value().toObject().end();it2++)
                {

                    itemMap.insert(it2.key(),it2.value().toString());
                }
                map.insert(it.key(),itemMap);
            }
        }
        orderList1->append(map);
    }
    for(int i=0;i<sellArray.size();i++)
    {
        QMap<QString, QMap<QString,QString>> map;
        for(auto it=sellArray.at(i).toObject().begin();
                it!=sellArray.at(i).toObject().end();it++)
        {
            if(it.key() == "date")
            {
                dateList2->append(it.value().toString());
            }
            else if(it.key() == "total")
            {
                totalList2->append(it.value().toString());
            }
            else if(it.key() == "profit")
            {
                costList->append(it.value().toString());
            }
            else
            {
                QMap<QString, QString> itemMap;
                for(auto it2=it.value().toObject().begin();
                        it2!=it.value().toObject().end();it2++)
                {

                    itemMap.insert(it2.key(),it2.value().toString());
                }
                map.insert(it.key(),itemMap);
            }
        }
        orderList2->append(map);
    }
    for(int i=0; i<dateList1->size(); i++)
    {
        QString item = QString::number(i+1)+"\t"+totalList1->at(i)+"\t"+dateList1->at(i);
        ui->listWidget->addItem(item);
    }
    for(int i=0; i<dateList2->size(); i++)
    {
        QString item = QString::number(i+1)+"\t"
                        +totalList2->at(i)+"\t"
                        +costList->at(i)+"\t"
                        +dateList2->at(i);
        ui->listWidget_2->addItem(item);
    }
    buyFile.close();
    sellFile.close();
}

GoodsInquiryWindow::~GoodsInquiryWindow()
{
    delete ui;
}

void GoodsInquiryWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}



void GoodsInquiryWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int row = item->listWidget()->currentRow()-1;
    if(row >= 0)
    {
        BuyList *by = new BuyList(this);
        by->addItem("种类\t商品名\t单价\t数量");
        for(auto it=orderList1->at(row).begin();it!=orderList1->at(row).end();it++)
        {
            QString type = it.value().value("种类");
            QString name = it.value().value("商品名");
            QString price = it.value().value("单价") ;
            QString num = it.value().value("数量");
            by->addItem(type+"\t"+name+"\t"+price+"\t"+num);
        }
        by->show();
        by->move ((this->width()-by->width())/2, (this->height()-by->height())/2);
    }
}

void GoodsInquiryWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    int row = item->listWidget()->currentRow()-1;
    if(row >= 0)
    {
        BuyList *by = new BuyList(this);
        by->addItem("种类\t商品名\t单价\t成本\t数量");
        for(auto it=orderList2->at(row).begin();it!=orderList2->at(row).end();it++)
        {
            QString type = it.value().value("种类");
            QString name = it.value().value("商品名");
            QString price = it.value().value("单价") ;
            QString cost = it.value().value("成本") ;
            QString num = it.value().value("数量");
            by->addItem(type+"\t"+name+"\t"+price+"\t"+cost+"\t"+num);
        }
        by->show();
        by->move ((this->width()-by->width())/2, (this->height()-by->height())/2);
    }
}
