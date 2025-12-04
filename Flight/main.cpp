#include "MainWindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. 添加 ODBC 数据库驱动
    QSqlDatabase dbcon = QSqlDatabase::addDatabase("QODBC");

    // 2. 设置 ODBC 版本选项
    dbcon.setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3");

    // 3. 使用连接字符串直接连接 (比 DSN 更可靠，不依赖系统配置)
    // 请确保你安装的驱动名称与下方 DRIVER={} 中一致
    // 常见的有 "MySQL ODBC 8.0 Unicode Driver" 或 "MySQL ODBC 8.1 Unicode Driver"
    QString connectionString = "DRIVER={MySQL ODBC 8.0 Unicode Driver};"
                               "SERVER=127.0.0.1;"
                               "PORT=3306;"
                               "DATABASE=flight;"
                               "USER=root;"
                               "PASSWORD=a157621438;"
                               "OPTION=3;";

    dbcon.setDatabaseName(connectionString);

    // 4. 打开数据库
    if (!dbcon.open()) {
        qDebug() << "Error: 数据库连接失败！";
        qDebug() << "错误信息：" << dbcon.lastError().text();
        qDebug() << "请检查：MySQL服务是否开启？ODBC驱动是否安装？密码是否正确？";
    } else {
        qDebug() << "Success: 数据库连接成功 (ODBC Mode)！";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
