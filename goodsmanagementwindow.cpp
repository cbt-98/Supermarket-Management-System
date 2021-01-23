#include "goodsmanagementwindow.h"
#include "ui_goodsmanagementwindow.h"

GoodsManagementWindow::GoodsManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoodsManagementWindow)
{
    ui->setupUi(this);
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
