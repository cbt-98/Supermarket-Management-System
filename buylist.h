#ifndef BUYLIST_H
#define BUYLIST_H

#include <QWidget>

namespace Ui {
class BuyList;
}

class BuyList : public QWidget
{
    Q_OBJECT

public:
    explicit BuyList(QWidget *parent = nullptr);
    ~BuyList();
    void addItem(QString item);
private slots:
    void on_pushButton_clicked();

private:
    Ui::BuyList *ui;

};

#endif // BUYLIST_H
