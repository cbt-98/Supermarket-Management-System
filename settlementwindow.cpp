#include "settlementwindow.h"
#include "ui_settlementwindow.h"

SettlementWindow::SettlementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettlementWindow)
{
    ui->setupUi(this);
}

SettlementWindow::~SettlementWindow()
{
    delete ui;
}

void SettlementWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}
