#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maininterface.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "sign_in.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainInterface* a=new MainInterface();
    a->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void ConnectDatabase(){
    QSqlDatabase dbcon;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        dbcon = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        dbcon = QSqlDatabase::addDatabase("QMYSQL");
        dbcon.setHostName("127.0.0.1");
        dbcon.setPort(3306);
        dbcon.setDatabaseName("Flight");
        dbcon.setUserName("root");
        dbcon.setPassword("@WUyh0601");
    }
    if (!dbcon.isOpen()) {
        bool ok = dbcon.open();
        if (ok) {
            qDebug() << "数据库连接成功!";
        } else {
            qDebug() << "数据库连接失败：" << dbcon.lastError().text();
        }
    } else {
        qDebug() << "数据库已连接!";
    }
}
bool checkUser(QString &username,QString &password){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "请先连接数据库!";
        return false;
    }
    QSqlQuery query;
    QString sql="SELECT Username, PWord FROM users where Username=? AND PWord=?";
    query.prepare(sql);
    query.addBindValue(username);
    query.addBindValue(password);
    if (!query.exec()) {
        qDebug() << "查询失败:" << query.lastError().text();
        return false;
    }
    return query.next();
}
void MainWindow::on_log_in_clicked()
{
    QString username=ui->Usernamet->text().trimmed();
    QString password=ui->Passwordt->text().trimmed();
    if(username.isEmpty()||password.isEmpty()){
        QMessageBox::warning(this, "提示", "用户名或密码不能为空!");
        return;
    }
    ConnectDatabase();
    bool ok=checkUser(username,password);
    if(ok){
        QMessageBox::information(this, "成功", "登录成功!");
    }
    else{
        QMessageBox::warning(this, "失败", "用户名或密码错误!");
    }
}
void MainWindow::on_sign_in_clicked()
{
    Sign_in *s=new Sign_in();
    s->setAttribute(Qt::WA_DeleteOnClose);
    s->show();
}

