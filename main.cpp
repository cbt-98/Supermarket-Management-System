#include "mainwindow.h"

#include <QApplication>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("超市管理系统");
    QIcon icon(":/image/icon/main.ico");
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
