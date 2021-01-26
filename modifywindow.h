#ifndef MODIFYWINDOW_H
#define MODIFYWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QList>
#include <QMap>
#include <QIcon>
#include <QTableWidgetItem>
namespace Ui {
class ModifyWindow;
}

class ModifyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyWindow(QWidget *parent = nullptr);
    ~ModifyWindow();
    bool flag;  //判断是否执行itemchanged信号
private slots:
    void on_returnBtn_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::ModifyWindow *ui;
    QMap<QString,QMap<QString,QMap<QString,QString>>> typeMap; //存放仓库信息

};

#endif // MODIFYWINDOW_H
