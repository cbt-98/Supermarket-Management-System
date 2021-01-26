#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    passwordFile = new QFile("./passwd.json");
    QFile repositoryFile("repository.json");
    //创建仓库商品存量表
    if(!repositoryFile.exists())
    {
        repositoryFile.open(QIODevice::ReadWrite);
        QJsonDocument doc;
        QJsonObject commodityObj;   //保存一类商品的对象
        QJsonObject typeObj;        //保存商品种类的对象
        QStringList list;
        list << "零食" << "衣服" << "玩具" << "电子"
             << "生活" << "烟酒" << "蔬菜" << "肉类"
             << "鞋类" << "饮料" << "文具" << "电器";
        for(int i=0; i<list.size(); i++)
        {
            typeObj.insert(list.at(i), commodityObj);
        }
        doc.setObject(typeObj);
        repositoryFile.write(doc.toJson());
        repositoryFile.close();
    }
    if(!passwordFile->exists())
    {
        QMessageBox *mb = new QMessageBox;
        QIcon icon(":/image/icon/tip.ico");
        mb->setWindowIcon(icon);
        mb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        mb->setWindowTitle("提 示");
        mb->setText("检测到您第一次使用，点击管理员登录创建管理员账户\r\n默认账户：admin 默认密码：123456");
        mb->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(!passwordFile->exists())
    {
        //创建json文件
        passwordFile->open(QIODevice::ReadWrite);
        QJsonObject passwdObj;
        QJsonArray adminArray;
        QJsonArray staffArray;
        QJsonObject adminObj;
        QJsonDocument doc;

        //注册一个管理员账户
        if(ui->accountEdit->text()=="")
        {
            adminObj.insert("account", "admin");
        }
        else
        {
            adminObj.insert("account", ui->accountEdit->text());
        }
        if(ui->pwEdit->text()=="")
        {
            adminObj.insert("passwd", "123456");
        }
        else
        {
            adminObj.insert("passwd", ui->pwEdit->text());
        }

        //写入文件
        adminArray.insert(0,adminObj);
        passwdObj.insert("admin", adminArray);
        passwdObj.insert("staff", staffArray);
        doc.setObject(passwdObj);
        QByteArray data = doc.toJson();
        passwordFile->write(data);
        passwordFile->close();

        QMessageBox *mb = new QMessageBox;
        QIcon icon(":/image/icon/tip.ico");
        mb->setWindowIcon(icon);
        mb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        mb->setWindowTitle("提 示");
        mb->setText("创建成功！");
        mb->show();

    }
    else
    {
        passwordFile->open(QIODevice::ReadWrite);
        QJsonDocument doc(QJsonDocument::fromJson(passwordFile->readAll()));
        QJsonObject obj = doc.object();
        QJsonArray array = obj.value("admin").toArray();
        for(int i=0; i<array.size();i++)
        {
            if(array.at(i).toObject().value("account") == ui->accountEdit->text())
            {
                if(array.at(i).toObject().value("passwd") == ui->pwEdit->text())
                {
                    //用户名和密码匹配跳转页面
                    adminWindow *aw = new adminWindow(this);
                    aw->show();
                    this->hide();
                    passwordFile->close();
                    break;
                }
                else
                {
                    QMessageBox *mb = new QMessageBox;
                    mb->setText("密码错误！");
                    QIcon icon(":/image/icon/tip.ico");
                    mb->setWindowIcon(icon);
                    mb->setWindowTitle("提 示");
                    mb->show();
                    passwordFile->close();
                    break;
                }
            }
            if(i == array.size()-1)
            {
                QMessageBox *mb = new QMessageBox;
                QIcon icon(":/image/icon/tip.ico");
                mb->setWindowIcon(icon);
                mb->setText("用户不存在！");
                mb->setWindowTitle("提 示");
                mb->show();
                passwordFile->close();
            }
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    passwordFile->open(QIODevice::ReadWrite);
    QJsonDocument doc(QJsonDocument::fromJson(passwordFile->readAll()));
    QJsonObject obj = doc.object();
    QJsonArray array = obj.value("staff").toArray();
    if(array.count()==0)
    {
        QMessageBox *mb = new QMessageBox;
        QIcon icon(":/image/icon/tip.ico");
        mb->setWindowIcon(icon);
        mb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
        mb->setWindowTitle("提 示");
        mb->setText("用户不存在！");
        mb->show();
        passwordFile->close();
    }
    for(int i=0; i<array.size();i++)
    {
        if(array.at(i).toObject().value("account") == ui->accountEdit->text())
        {
            if(array.at(i).toObject().value("passwd") == ui->pwEdit->text())
            {
                //用户名和密码匹配跳转页面
                StaffWindow *sw = new StaffWindow(this);
                sw->show();
                this->hide();
                passwordFile->close();
                break;
            }
            else
            {
                QMessageBox *mb = new QMessageBox;
                mb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
                QIcon icon(":/image/icon/tip.ico");
                mb->setWindowIcon(icon);
                mb->setWindowTitle("提 示");
                mb->setText("密码错误！");
                mb->show();
                passwordFile->close();
                break;
            }
        }
        if(i == array.size()-1)
        {
            QMessageBox *mb = new QMessageBox;
            QIcon icon(":/image/icon/tip.ico");
            mb->setWindowIcon(icon);
            mb->setStyleSheet( "font: 12pt \"黑体\"; color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
            mb->setWindowTitle("提 示");
            mb->setText("用户不存在！");
            mb->show();
            passwordFile->close();
        }
    }
}
