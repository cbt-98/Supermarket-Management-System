#ifndef STAFFWINDOW_H
#define STAFFWINDOW_H

#include <QMainWindow>
#include <goodsinquirywindow.h>
#include <settlementwindow.h>
#include <QIcon>
namespace Ui {
class StaffWindow;
}

class StaffWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StaffWindow(QWidget *parent = nullptr);
    ~StaffWindow();

private slots:
    void on_returnBtn_clicked();

    void on_goodsBtn_clicked();

    void on_staffBtn_clicked();

private:
    Ui::StaffWindow *ui;
};

#endif // STAFFWINDOW_H
