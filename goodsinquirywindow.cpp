#include "goodsinquirywindow.h"
#include "ui_goodsinquirywindow.h"

GoodsInquiryWindow::GoodsInquiryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoodsInquiryWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("序号\t总价\t\t日期");
    ui->listWidget_2->addItem("序号\t总价\t\t日期");
    orderList1 = new QList<QMap<QString,QString>>;
    dateList1 = new QList<QString>;
    totalList1 = new QList<QString>;
    orderList2 = new QList<QMap<QString,QString>>;
    dateList2 = new QList<QString>;
    totalList2 = new QList<QString>;

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
        QMap<QString, QString> map;
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
                map.insert(it.key(),it.value().toString());
            }
        }
        orderList1->append(map);
    }
    for(int i=0;i<sellArray.size();i++)
    {
        QMap<QString, QString> map;
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
            else
            {
                map.insert(it.key(),it.value().toString());
            }
        }
        orderList2->append(map);
    }
    for(int i=0; i<dateList1->size(); i++)
    {
        QString item = QString::number(i+1)+"\t"+totalList1->at(i)+"\t\t"+dateList1->at(i);
        ui->listWidget->addItem(item);
    }
    for(int i=0; i<dateList2->size(); i++)
    {
        QString item = QString::number(i+1)+"\t"+totalList2->at(i)+"\t\t"+dateList2->at(i);
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
