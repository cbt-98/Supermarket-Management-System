#ifndef GOODSMANAGEMENTWINDOW_H
#define GOODSMANAGEMENTWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDateTime>
#include <QIcon>

namespace Ui {
class GoodsManagementWindow;
}

/*
stocking.json格式：
{
   账单:
   [
        账单1:{
            总价:xxx
            1:{种类，商品名，单价，数量}
            2:{种类，商品名，单价，数量}
        }
        账单2:{
            总价:xxx
            1:{种类，商品名，单价，数量}
            2:{种类，商品名，单价，数量}
        }
    ]
}
*/

class GoodsManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GoodsManagementWindow(QWidget *parent = nullptr);
    ~GoodsManagementWindow();

private slots:
    void on_returnBtn_clicked();

    void on_addBtn_clicked();



    void on_deleteBtn_clicked();

    void on_submitBtn_clicked();

private:
    Ui::GoodsManagementWindow *ui;
    QList<QString> *typeList;
    QList<QString> *nameList;
    QList<QString> *priceList;
    QList<QString> *numberList;
    QFile *file;
};

#endif // GOODSMANAGEMENTWINDOW_H
