#include "goodsmanagementwindow.h"
#include "ui_goodsmanagementwindow.h"

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



void GoodsManagementWindow::on_deleteBtn_clicked()
{
    //删除容器中对应值
    int num = ui->deleteEdit->text().toInt();
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

void GoodsManagementWindow::on_submitBtn_clicked()
{
    file->open(QIODevice::ReadWrite);
    QJsonDocument doc;
    QJsonObject object;     //保存账单对象
    QJsonArray orderArray;  //保存账单数组
    QJsonObject orderObj;   //每个账单对象

    //如果文件存在就先读出保存
    if(file->exists())
    {
        doc = QJsonDocument::fromJson(file->readAll());
        object = doc.object();
        orderArray = object.value("order").toArray();
    }

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
    orderArray.append(orderObj);
    object["order"] = orderArray;
    doc.setObject(object);
    file->resize(0);
    file->write(doc.toJson());
    file->flush();
    file->close();

    //更新界面
    ui->listWidget->clear();
    ui->listWidget->addItem("序号\t种类\t商品名\t单价\t数量");
    QMessageBox *mb = new QMessageBox(this);
    mb->setText("提交成功");
    mb->setStyleSheet("color:rgb(0,0,0)");
    mb->show();
}
