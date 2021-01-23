#ifndef SETTLEMENTWINDOW_H
#define SETTLEMENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class SettlementWindow;
}

class SettlementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettlementWindow(QWidget *parent = nullptr);
    ~SettlementWindow();

private slots:
    void on_returnBtn_clicked();

private:
    Ui::SettlementWindow *ui;
};

#endif // SETTLEMENTWINDOW_H
