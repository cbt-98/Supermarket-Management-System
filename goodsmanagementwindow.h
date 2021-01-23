#ifndef GOODSMANAGEMENTWINDOW_H
#define GOODSMANAGEMENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class GoodsManagementWindow;
}

class GoodsManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GoodsManagementWindow(QWidget *parent = nullptr);
    ~GoodsManagementWindow();

private slots:
    void on_returnBtn_clicked();

private:
    Ui::GoodsManagementWindow *ui;
};

#endif // GOODSMANAGEMENTWINDOW_H
