#include "goodsmanagementwindow.h"
#include "ui_goodsmanagementwindow.h"
#include <QDebug>
GoodsManagementWindow::GoodsManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoodsManagementWindow)
{
    ui->setupUi(this);

    //初始化成员
    typeList = new QList<QString>;
    nameList = new QList<QString>;
    priceList = new QList<QString>;
    numberList = new QList<QString>;
    file = new QFile("stocking.json");

    //设置ui上组件
    QStringList list;
    list << "零食" << "衣服" << "玩具" << "电子"
         << "生活" << "烟酒" << "蔬菜" << "肉类"
         << "鞋类" << "饮料" << "文具" << "电器";
    ui->comboBox->addItems(list);
    ui->listWidget->addItem("序号\t种类\t商品名\t单价\t数量");
    ui->totalLabel->setText(QString::number(0));
}

GoodsManagementWindow::~GoodsManagementWindow()
{
    delete ui;
}

void GoodsManagementWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}

void GoodsManagementWindow::on_addBtn_clicked()
{
    if(ui->nameEdit->text()==""||ui->numberSpinBox->text()=="0")
    {
        QMessageBox *qb = new QMessageBox(this);
        qb->setWindowTitle("提 示");
        QIcon icon(":/image/icon/tip.ico");
        qb->setWindowIcon(icon);
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("请输入商品名，数量至少为1");
        qb->show();
    }
    else
    {
        //在容器中追加
        typeList->append(ui->comboBox->currentText());
        nameList->append(ui->nameEdit->text());
        priceList->append(ui->priceSpinBox->text());
        numberList->append(ui->numberSpinBox->text());

        //更新listwedget
        ui->listWidget->addItem(QString::number(ui->listWidget->count())+"\t"
                                +ui->comboBox->currentText()+"\t"
                                +ui->nameEdit->text()+"\t"
                                +ui->priceSpinBox->text()+"\t"
                                +ui->numberSpinBox->text());

        //更新总价
        int total = ui->totalLabel->text().toInt()
                    +ui->priceSpinBox->value()
                    *ui->numberSpinBox->value();
        ui->totalLabel->setText(QString::number(total));
    }
}



void GoodsManagementWindow::on_deleteBtn_clicked()
{
    if(ui->deleteEdit->text()!="")
    {
        int num = ui->deleteEdit->text().toInt();
        if(num < ui->listWidget->count())
        {
            //获取删除物品总价
            double n = priceList->at(num-1).toDouble()*numberList->at(num-1).toInt();
            double newTotal = ui->totalLabel->text().toDouble()-n;
            ui->totalLabel->setText(QString("%1").arg(newTotal));
            //删除容器中对应值
            typeList->removeAt(num-1);
            nameList->removeAt(num-1);
            priceList->removeAt(num-1);
            numberList->removeAt(num-1);

            //更新listwidget
            ui->listWidget->clear();
            ui->listWidget->addItem("序号\t种类\t商品名\t单价\t数量");
            for(int i=0; i<typeList->size(); i++)
            {
                ui->listWidget->addItem(QString::number(ui->listWidget->count())+"\t"
                                        +typeList->at(i)+"\t"
                                        +nameList->at(i)+"\t"
                                        +priceList->at(i)+"\t"
                                        +numberList->at(i));
            }
        }
        else
        {
            QMessageBox *mb = new QMessageBox(this);
            QIcon icon(":/image/icon/tip.ico");
            mb->setWindowIcon(icon);
            mb->setWindowTitle("提 示");
            mb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
            mb->setText("没有该选项");
            mb->show();
        }
    }
    else
    {
        QMessageBox *qb = new QMessageBox(this);
        qb->setWindowTitle("提 示");
        QIcon icon(":/image/icon/tip.ico");
        qb->setWindowIcon(icon);
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("请输入行号");
        qb->show();
    }
}

void GoodsManagementWindow::on_submitBtn_clicked()
{
    if(ui->listWidget->count()==1)
    {
        QMessageBox *qb = new QMessageBox(this);
        QIcon icon(":/image/icon/tip.ico");
        qb->setWindowIcon(icon);
        qb->setWindowTitle("提 示");
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("订单为空");
        qb->show();
    }
    else
    {
        //获取提交时间
        QString date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd");

        file->open(QIODevice::ReadWrite);
        QJsonDocument doc;
        QJsonObject object;     //保存账单对象
        QJsonArray orderArray;  //保存账单数组
        QJsonObject orderObj;   //每个账单对象

        //如果文件存在就先读出保存
        doc = QJsonDocument::fromJson(file->readAll());
        object = doc.object();
        orderArray = object.value("order").toArray();

        for(int i=0; i<typeList->size(); i++)
        {
            QJsonObject itemObj;    //每个条目的对象
            itemObj.insert("种类", typeList->at(i));
            itemObj.insert("商品名", nameList->at(i));
            itemObj.insert("单价", priceList->at(i));
            itemObj.insert("数量", numberList->at(i));
            orderObj.insert(QString::number(i), itemObj);
        }
        orderObj.insert("total", ui->totalLabel->text());
        orderObj.insert("date", date);
        orderArray.append(orderObj);
        object["order"] = orderArray;
        doc.setObject(object);
        file->resize(0);
        file->write(doc.toJson());
        file->flush();
        file->close();

        //更新仓库数量
        QFile repositoryFile("repository.json");
        repositoryFile.open(QIODevice::ReadWrite);
        QJsonDocument rDoc = QJsonDocument::fromJson(repositoryFile.readAll());
        QJsonObject rObj = rDoc.object();
        for(int i=0; i<typeList->size(); i++)
        {
            QString type = typeList->at(i);
            QString name = nameList->at(i);
            QString price = priceList->at(i);
            QString number = numberList->at(i);

            QJsonObject typeObj = rObj.value(type).toObject();          //某一类商品的对象
            QJsonObject commodityObj = typeObj.value(name).toObject();  //某一个商品对象                          //某个商品的对象
            if(commodityObj.isEmpty())
            {
                commodityObj.insert("price", price);
                commodityObj.insert("num", number);
                commodityObj.insert("cost", price);
                typeObj.insert(name,commodityObj);
            }
            else
            {
                int num = commodityObj.value("num").toString().toInt(); //原来存量
                int newNum = num+number.toInt();
                commodityObj["num"] = QString::number(newNum);
                typeObj[name] = commodityObj;
            }
            rObj[type] = typeObj;
        }
        rDoc.setObject(rObj);
        repositoryFile.resize(0);
        repositoryFile.write(rDoc.toJson());
        repositoryFile.close();

        //更新界面
        ui->listWidget->clear();
        ui->listWidget->addItem("序号\t种类\t商品名\t单价\t数量");
        ui->totalLabel->setText(QString::number(0));
        QMessageBox *mb = new QMessageBox(this);
        mb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        QIcon icon(":/image/icon/tip.ico");
        mb->setWindowIcon(icon);
        mb->setWindowTitle("提 示");
        mb->setText("提交成功");
        mb->setStyleSheet("color:rgb(0,0,0)");
        mb->show();
    }
}
