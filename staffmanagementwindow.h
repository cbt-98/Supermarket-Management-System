#ifndef STAFFMANAGEMENTWINDOW_H
#define STAFFMANAGEMENTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QSize>
namespace Ui {
class StaffManagementWindow;
}

class StaffManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StaffManagementWindow(QWidget *parent = nullptr);
    ~StaffManagementWindow();

private slots:
    void on_returnBtn_clicked();

    void on_addBtn_clicked();

    void on_deleteBtn_clicked();

private:
    Ui::StaffManagementWindow *ui;
    QFile *file;
};

#endif // STAFFMANAGEMENTWINDOW_H
