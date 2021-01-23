#include "goodsinquirywindow.h"
#include "ui_goodsinquirywindow.h"

GoodsInquiryWindow::GoodsInquiryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoodsInquiryWindow)
{
    ui->setupUi(this);
}

GoodsInquiryWindow::~GoodsInquiryWindow()
{
    delete ui;
}

void GoodsInquiryWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}
