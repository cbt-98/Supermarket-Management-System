#include "buylist.h"
#include "ui_buylist.h"

BuyList::BuyList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyList)
{
    ui->setupUi(this);
}

BuyList::~BuyList()
{
    delete ui;
}

void BuyList::addItem(QString item)
{
    ui->listWidget->addItem(item);
}

void BuyList::on_pushButton_clicked()
{
    this->close();
}
