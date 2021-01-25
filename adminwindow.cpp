#include "adminwindow.h"
#include "ui_adminwindow.h"
adminWindow::adminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminWindow)
{
    ui->setupUi(this);
}

adminWindow::~adminWindow()
{
    delete ui;
}


void adminWindow::on_staffBtn_clicked()
{
    StaffManagementWindow *smw = new StaffManagementWindow(this);
    smw->show();
    this->hide();
}

void adminWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}

void adminWindow::on_goodsBtn_clicked()
{
    GoodsManagementWindow *gmw = new GoodsManagementWindow(this);
    gmw->show();
    this->hide();
}


void adminWindow::on_goodsInquiryBtn_clicked()
{
    GoodsInquiryWindow *giw = new GoodsInquiryWindow(this);
    giw->show();
    this->hide();
}

void adminWindow::on_goodsInquiryBtn_2_clicked()
{
    ModifyWindow *mw = new ModifyWindow(this);
    mw->show();
    this->hide();
}
