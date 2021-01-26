#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <staffmanagementwindow.h>
#include <goodsmanagementwindow.h>
#include <goodsinquirywindow.h>
#include "modifywindow.h"
#include <QIcon>
namespace Ui {
class adminWindow;
}

class adminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminWindow(QWidget *parent = nullptr);
    ~adminWindow();

private slots:

    void on_staffBtn_clicked();

    void on_returnBtn_clicked();

    void on_goodsBtn_clicked();


    void on_goodsInquiryBtn_clicked();

    void on_goodsInquiryBtn_2_clicked();

private:
    Ui::adminWindow *ui;
};

#endif // ADMINWINDOW_H
