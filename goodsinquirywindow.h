#ifndef GOODSINQUIRYWINDOW_H
#define GOODSINQUIRYWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "buylist.h"
#include <QListWidgetItem>
#include <QDebug>
namespace Ui {
class GoodsInquiryWindow;
}

class GoodsInquiryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GoodsInquiryWindow(QWidget *parent = nullptr);
    ~GoodsInquiryWindow();

private slots:
    void on_returnBtn_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

private:
    //保存采购表的容器
    Ui::GoodsInquiryWindow *ui;
    QList<QMap<QString,QMap<QString,QString>>> *orderList1;
    QList<QString> *dateList1;
    QList<QString> *totalList1;

    //保存销售表的容器
    QList<QMap<QString,QMap<QString,QString>>> *orderList2;
    QList<QString> *dateList2;
    QList<QString> *totalList2;
    QList<QString> *costList;
;};

#endif // GOODSINQUIRYWINDOW_H
