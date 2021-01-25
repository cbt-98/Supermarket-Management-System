#include "modifywindow.h"
#include "ui_modifywindow.h"

ModifyWindow::ModifyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModifyWindow)
{
    flag = false;
    ui->setupUi(this);

    //把repository.json的数据读取到map容器
    QFile file("repository.json");
    file.open(QIODevice::ReadWrite);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject Obj = doc.object();
    for(auto it1=Obj.begin(); it1!=Obj.end(); it1++)
    {
        QMap<QString, QMap<QString,QString>> commodityMap;
        for(auto it2=it1.value().toObject().begin();it2!=it1.value().toObject().end();it2++)
        {
            QMap<QString,QString> propertyMap;
            propertyMap.insert("price", it2.value().toObject().value("price").toString()) ;
            propertyMap.insert("cost", it2.value().toObject().value("cost").toString()) ;
            propertyMap.insert("num", it2.value().toObject().value("num").toString()) ;
            commodityMap.insert(it2.key(), propertyMap);
        }
        typeMap.insert(it1.key(),commodityMap);
    }
    file.close();

    //更新ui信息
    QStringList list;
    list << "零食" << "衣服" << "玩具" << "电子"
         << "生活" << "烟酒" << "蔬菜" << "肉类"
         << "鞋类" << "饮料" << "文具" << "电器";
    ui->comboBox->addItems(list);

    //更新表格显示
    QString type = ui->comboBox->currentText();
    QTableWidgetItem headerItem;
    QStringList headerText;
    headerText<<"商 品 名" << "库 存" << "进 货 价" << "售 价";
    ui->tableWidget->horizontalHeader()->setStyleSheet
        ("color: rgb(0, 0, 0);font: 12pt \"黑体\";");
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
    int i = 0;
    flag = false;
    for(auto it=typeMap.value(type).begin();it!=typeMap.value(type).end();it++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(it.key()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(it.value().value("num")));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(it.value().value("cost")));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(it.value().value("price")));
        //字体居中
        ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置除了售价列之外为不可修改
        ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,1)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,2)->setFlags(Qt::NoItemFlags);
        i++;
    }
    flag = true;
}

ModifyWindow::~ModifyWindow()
{
    delete ui;
}

void ModifyWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}

void ModifyWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    flag = false;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(typeMap.value(arg1).count());
    int i = 0;
    for(auto it=typeMap.value(arg1).begin();it!=typeMap.value(arg1).end();it++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(it.key()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(it.value().value("num")));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(it.value().value("cost")));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(it.value().value("price")));
        //字体居中
        ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置除了售价列之外为不可修改
        ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,1)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,2)->setFlags(Qt::NoItemFlags);
        i++;
    }
    flag = true;
}

void ModifyWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(flag == true)
    {
        flag = false;
        QString type = ui->comboBox->currentText();
        QString name = ui->tableWidget->item(item->row(),0)->text();
        QString newPrice = QString::number(item->text().toDouble(),'f',2);
        typeMap[type][name]["price"] = newPrice;
        ui->tableWidget->item(item->row(),item->column())->setText(newPrice);
        flag = true;
        qDebug() <<"修改成功";
    }
}

void ModifyWindow::on_pushButton_clicked()
{
    QFile repositoryFile("./repository.json");
    repositoryFile.open(QIODevice::ReadWrite);
    QJsonDocument reDoc;
    QJsonObject typeObj;
    for(auto it1=typeMap.begin(); it1!=typeMap.end(); it1++)
    {
        QJsonObject nameObj;
        for(auto it2=it1->begin(); it2!=it1->end(); it2++)
        {
            QJsonObject propertyObj;
            propertyObj.insert("price", it2.value().value("price"));
            propertyObj.insert("cost", it2.value().value("cost"));
            propertyObj.insert("num", it2.value().value("num"));
            nameObj.insert(it2.key(), propertyObj);
        }
        typeObj.insert(it1.key(),nameObj);
    }
    reDoc.setObject(typeObj);
    repositoryFile.resize(0);
    repositoryFile.write(reDoc.toJson());

    repositoryFile.close();
    QMessageBox *qb = new QMessageBox(this);
    qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
    qb->setText("提交成功！");
    qb->show();
}
