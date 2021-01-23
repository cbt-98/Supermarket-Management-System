#include "staffwindow.h"
#include "ui_staffwindow.h"

StaffWindow::StaffWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StaffWindow)
{
    ui->setupUi(this);
}

StaffWindow::~StaffWindow()
{
    delete ui;
}

void StaffWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}

void StaffWindow::on_goodsBtn_clicked()
{
    GoodsInquiryWindow *giw = new GoodsInquiryWindow(this);
    giw->show();
    this->hide();
}

void StaffWindow::on_staffBtn_clicked()
{
    SettlementWindow *slw = new SettlementWindow(this);
    slw->show();
    this->hide();
}
