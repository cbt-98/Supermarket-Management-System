#include "settlementwindow.h"
#include "ui_settlementwindow.h"

SettlementWindow::SettlementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettlementWindow)
{
    ui->setupUi(this);

    //初始化shoppingList
    QList<QString> l;
    for(int i=0;i<5;i++)
    {
        shoppingList.append(l);
    }

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
    ui->typeComboBox->addItems(list);

    QList<QString> nameList;
    QString type = ui->typeComboBox->currentText();
    for(auto it=typeMap.value(type).begin();it!=typeMap.value(type).end();it++)
    {
        nameList.append(it.key());
    }
    ui->nameComboBox->clear();
    ui->nameComboBox->addItems(nameList);

    QString name = ui->nameComboBox->currentText();
    ui->priceLabel->setText(typeMap.value(type).value(name).value("price"));

    int max = typeMap.value(type).value(name).value("num").toInt();//存量
    ui->numberSpinBox->setMaximum(max);
    ui->remainLabel->setText(QString("剩 余：%1").arg(max));

    ui->listWidget->addItem("序号\t种类\t商品名\t单价\t数量");
}

SettlementWindow::~SettlementWindow()
{
    delete ui;
}

void SettlementWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}

void SettlementWindow::on_typeComboBox_currentIndexChanged(const QString &arg1)
{
    //更新商品列表
    QList<QString> list;
    ui->nameComboBox->clear();
    for(auto it=typeMap.value(arg1).begin();it!=typeMap.value(arg1).end();it++)
    {
        list.append(it.key());
    }
    ui->nameComboBox->addItems(list);

    //更新价格信息
    QString name = ui->nameComboBox->currentText();
    ui->priceLabel->setText(typeMap.value(arg1).value(name).value("price"));

}

void SettlementWindow::on_nameComboBox_currentTextChanged(const QString &arg1)
{
    QString type = ui->typeComboBox->currentText();
    ui->priceLabel->setText(typeMap.value(type).value(arg1).value("price"));

    int max = typeMap.value(type).value(arg1).value("num").toInt();//存量
    ui->numberSpinBox->setMaximum(max);
    ui->remainLabel->setText(QString("剩 余：%1").arg(max));
}

void SettlementWindow::on_addBtn_clicked()
{
    if(ui->numberSpinBox->text()=="0")
    {
        QMessageBox *qb = new QMessageBox(this);
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("请输入商品名，数量至少为1");
        qb->show();
    }
    else
    {
        //更新总价
        double nowTotal = ui->totalLabel->text().toDouble();
        double d = ui->priceLabel->text().toDouble()*ui->numberSpinBox->text().toInt();
        ui->totalLabel->setText(QString("%1").arg(d+nowTotal));

        //更新列表显示
        QString type, name, price, number, cost;
        type = ui->typeComboBox->currentText();
        name = ui->nameComboBox->currentText();
        price = ui->priceLabel->text();
        number = ui->numberSpinBox->text();
        cost = typeMap.value(type).value(name).value("cost");

        int num = ui->listWidget->count();
        ui->listWidget->addItem(QString::number(num)
                                +"\t"+type+"\t"+name
                                +"\t"+price+"\t"+number);

        //更新容器
        shoppingList[0].append(type);
        shoppingList[1].append(name);
        shoppingList[2].append(price);
        shoppingList[3].append(number);
        shoppingList[4].append(cost);

        int n = typeMap.value(type).value(name).value("num").toInt()-number.toInt();
        typeMap[type][name]["num"] = QString::number(n);

        //更新剩余数量
        ui->numberSpinBox->setMaximum(n);
        ui->remainLabel->setText(QString("剩 余：%1").arg(n));
    }
}

void SettlementWindow::on_deleteBtn_2_clicked()
{
    if(ui->deleteEdit_2->text()!="")
    {
        int n = ui->deleteEdit_2->text().toInt();
        if(n < ui->listWidget->count())
        {
            //更新总价
            double d = shoppingList[2][n-1].toDouble()*shoppingList[3][n-1].toInt();
            double newTotal = ui->totalLabel->text().toDouble()-d;
            ui->totalLabel->setText(QString("%1").arg(newTotal));

            //更新map容器

            int newNum = typeMap.value(shoppingList[0][n-1])
                                .value(shoppingList[1][n-1])
                                .value("num").toInt()
                         +shoppingList[3][n-1].toInt();

            typeMap[shoppingList[0][n-1]]
                    [shoppingList[1][n-1]]
                    ["num"] = QString::number(newNum);

            //更新列表容器
            shoppingList[0].removeAt(n-1);
            shoppingList[1].removeAt(n-1);
            shoppingList[2].removeAt(n-1);
            shoppingList[3].removeAt(n-1);
            shoppingList[4].removeAt(n-1);

            //更新列表显示
            ui->listWidget->clear();
            ui->listWidget->addItem("序号\t种类\t商品名\t单价\t数量");
            for(int i=0;i<shoppingList[0].count();i++)
            {
                QString type, name, price, number;
                type = shoppingList[0][i];
                name = shoppingList[1][i];
                price = shoppingList[2][i];
                number = shoppingList[3][i];

                int num = ui->listWidget->count();
                ui->listWidget->addItem(QString::number(num)
                                        +"\t"+type+"\t"+name
                                        +"\t"+price+"\t"+number);
            }
            //更新剩余数量
            int max = typeMap.value(ui->typeComboBox->currentText())
                            .value(ui->nameComboBox->currentText())
                            .value("num").toInt();
            ui->numberSpinBox->setMaximum(max);
            ui->remainLabel->setText(QString("剩 余：%1").arg(max));

        }
        else
        {
            QMessageBox *mb = new QMessageBox(this);
            mb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
            mb->setText("没有该选项");
            mb->show();
        }
    }
    else
    {
        QMessageBox *qb = new QMessageBox(this);
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("请输入行号");
        qb->show();
    }
}

void SettlementWindow::on_submitBtn_clicked()
{
    if(ui->listWidget->count()==1)
    {
        QMessageBox *qb = new QMessageBox(this);
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("购物单为空");
        qb->show();
    }
    else
    {
        double totalCost=0;
        //计算利润
        for(int i=0;i<shoppingList.at(0).count();i++)
        {
            totalCost += shoppingList.at(3).at(i).toDouble()*shoppingList.at(4).at(i).toDouble();
        }
        QString profit = QString::number(ui->totalLabel->text().toDouble()-totalCost,'f',2);

        //获取提交时间
        QString date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd");

        QFile repositoryFile("./repository.json");
        QFile sellFile("./sell.json");
        //写到销售表
        QJsonDocument doc;
        QJsonObject object;     //保存账单对象
        QJsonArray orderArray;  //保存账单数组
        QJsonObject orderObj;   //每个账单对象

        sellFile.open(QIODevice::ReadWrite);
        doc = QJsonDocument::fromJson(sellFile.readAll());
        object = doc.object();
        orderArray = object.value("order").toArray();

        for(int i=0; i<shoppingList[0].size(); i++)
        {
            QJsonObject itemObj;    //每个条目的对象
            itemObj.insert("种类", shoppingList[0].at(i));
            itemObj.insert("商品名", shoppingList[1].at(i));
            itemObj.insert("单价", shoppingList[2].at(i));
            itemObj.insert("数量", shoppingList[3].at(i));
            itemObj.insert("成本", shoppingList[4].at(i));
            orderObj.insert(QString::number(i), itemObj);
        }
        orderObj.insert("total", ui->totalLabel->text());
        orderObj.insert("profit", profit);
        orderObj.insert("date", date);
        orderArray.append(orderObj);
        object["order"] = orderArray;
        doc.setObject(object);
        sellFile.resize(0);
        sellFile.write(doc.toJson());
        sellFile.flush();
        sellFile.close();

        //写到仓库文件中
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

        //清空列表
        ui->listWidget->clear();
        ui->listWidget->addItem("序号\t种类\t商品名\t单价\t数量");
        ui->totalLabel->setText(QString::number(0));

        QMessageBox *qb = new QMessageBox(this);
        qb->setText("提交成功！");
        qb->show();
    }
}
