#ifndef GOODSINQUIRYWINDOW_H
#define GOODSINQUIRYWINDOW_H

#include <QMainWindow>

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

private:
    Ui::GoodsInquiryWindow *ui;
};

#endif // GOODSINQUIRYWINDOW_H
