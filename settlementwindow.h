#ifndef SETTLEMENTWINDOW_H
#define SETTLEMENTWINDOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QIcon>
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

    void on_typeComboBox_currentIndexChanged(const QString &arg1);

    void on_nameComboBox_currentTextChanged(const QString &arg1);

    void on_addBtn_clicked();

    void on_deleteBtn_2_clicked();

    void on_submitBtn_clicked();

private:
    Ui::SettlementWindow *ui;
    QMap<QString,QMap<QString,QMap<QString,QString>>> typeMap; //存放仓库信息
    QList<QList<QString>> shoppingList;     //[类型表，商品名表，售价表，数量表，成本表]
};

#endif // SETTLEMENTWINDOW_H
