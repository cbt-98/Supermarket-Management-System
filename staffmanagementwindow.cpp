#include "staffmanagementwindow.h"
#include "ui_staffmanagementwindow.h"

StaffManagementWindow::StaffManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StaffManagementWindow)
{
    ui->setupUi(this);

    //设置listwidget
    ui->listWidget->addItem("序号\t账户名\t密码");
    file = new QFile("./passwd.json");
    file->open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file->readAll());
    QJsonArray array = doc.object().value("staff").toArray();
    for(int i=0; i<array.size(); i++)
    {
        QString item = array.at(i).toObject().value("account").toString()+"\t"+
                array.at(i).toObject().value("passwd").toString();
        ui->listWidget->addItem(QString("%1\t").arg(i+1)+item);
    }
    file->close();
}

StaffManagementWindow::~StaffManagementWindow()
{
    delete ui;
}

void StaffManagementWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}



void StaffManagementWindow::on_addBtn_clicked()
{
    //添加账户是否存在判断

    //在json中添加账户
    if(ui->accountEdit->text()==""||ui->passwdEdit->text()=="")
    {
        QMessageBox *qb = new QMessageBox(this);
        qb->setWindowTitle("提 示");
        QIcon icon(":/image/icon/tip.ico");
        qb->setWindowIcon(icon);
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("账户名或密码不能为空");
        qb->show();
    }
    else
    {
        file->open(QIODevice::ReadWrite);
        QJsonDocument doc = QJsonDocument::fromJson(file->readAll());
        QJsonObject object = doc.object();
        QJsonArray array = object.value("staff").toArray();
        QJsonObject newObj;
        newObj.insert("account",ui->accountEdit->text());
        newObj.insert("passwd",ui->passwdEdit->text());
        array.append(newObj);
        object["staff"] = array;
        doc.setObject(object);
        file->resize(0);
        file->write(doc.toJson());
        file->flush();
        file->close();

        //刷新listwidget
        ui->listWidget->addItem(QString("%1\t").arg(ui->listWidget->count())
                                +ui->accountEdit->text()+"\t"
                                +ui->passwdEdit->text());
        QMessageBox *qb = new QMessageBox(this);
        qb->setWindowTitle("提 示");
        QIcon icon(":/image/icon/tip.ico");
        qb->setWindowIcon(icon);
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("添加成功");
        qb->show();
    }
}

void StaffManagementWindow::on_deleteBtn_clicked()
{
    if(ui->deleteEdit->text()=="")
    {
        QMessageBox *qb = new QMessageBox(this);
        QIcon icon(":/image/icon/tip.ico");
        qb->setWindowIcon(icon);
        qb->setWindowTitle("提 示");
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("请输入行号");
        qb->show();
    }
    else
    {
        QMessageBox *qb = new QMessageBox(this);
        QIcon icon(":/image/icon/tip.ico");
        qb->setWindowIcon(icon);
        qb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        qb->setText("确认删除该账户吗？");
        qb->setStandardButtons(QMessageBox::No|QMessageBox::Yes);

        if(qb->exec()==QMessageBox::No)
        {
            return;
        }
        else
        {
            int num = ui->deleteEdit->text().toInt();

            //在json中删除对应的账户
            file->open(QIODevice::ReadWrite);
            QJsonDocument doc = QJsonDocument::fromJson(file->readAll());
            QJsonObject object = doc.object();
            QJsonArray array = object.value("staff").toArray();
            array.removeAt(num-1);
            object["staff"] = array;
            doc.setObject(object);
            file->resize(0);
            file->write(doc.toJson());
            file->flush();
            file->close();

            //刷新listwidget
            ui->listWidget->clear();
            ui->listWidget->addItem("序号\t账户名\t密码");
            for(int i=0; i<array.size(); i++)
            {
                QString item = array.at(i).toObject().value("account").toString()+"\t"+
                        array.at(i).toObject().value("passwd").toString();
                ui->listWidget->addItem(QString("%1\t").arg(i+1)+item);
            }
        }
    }
}
