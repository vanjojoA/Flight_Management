#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "sign_in.h"
#include "deal.h"
#include "userprofile.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void ConnectDatabase(){
    QSqlDatabase dbcon = QSqlDatabase::database();
    if (!dbcon.isOpen()) {
        bool ok = dbcon.open();
        if (ok) {
            qDebug() << "数据库连接成功！";
        } else {
            qDebug() << "数据库连接失败：" << dbcon.lastError().text();
        }
    } else {
        qDebug() << "数据库已连接！";
    }
}
bool checkUserU(QString &username,QString &password){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "请先连接数据库！";
        return false;
    }
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString sql="SELECT Username, PWord FROM users where Username=? AND PWord=?";
    query.prepare(sql);
    query.addBindValue(username);
    query.addBindValue(password);

    bool result = false;
    if (query.exec() && query.next()) {
        result = true;
    }
    query.finish();
    return result;
}
bool checkUserI(QString &ID,QString &password){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "请先连接数据库！";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString sql="SELECT IDCard, PWord FROM users where IDCard=? AND PWord=?";
    query.prepare(sql);
    query.addBindValue(ID);
    query.addBindValue(password);

    bool result = false;
    if (query.exec() && query.next()) {
        result = true;
    }
    query.finish();
    return result;
}
QString GetUserID(QString &input,QString &password){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "请先连接数据库！";
        return QString();
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "请先连接数据库！";
        return QString();
    }
    QSqlQuery query(db);  // 显式指定数据库连接

    query.prepare("SELECT UserID FROM users where Username=? AND PWord=?");
    query.addBindValue(input);
    query.addBindValue(password);
    if(query.exec()&&query.next()){

        QString uid = query.value(0).toString();
        query.finish();
        return uid;
    }
    query.prepare("SELECT UserID FROM users where IDCard=? AND PWord=?");
    query.addBindValue(input);
    query.addBindValue(password);
    if(query.exec()&&query.next()){
        QString uid = query.value(0).toString();
        query.finish();
        return uid;
    }
    query.finish();
    return QString();
}

void MainWindow::on_log_in_clicked()
{
    QString username=ui->Usernamet->text().trimmed();
    QString password=ui->Passwordt->text().trimmed();
    if(username.isEmpty()||password.isEmpty()){
        QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
        return;
    }
    ConnectDatabase();
    QString userid=GetUserID(username,password);
    if(!userid.isEmpty()){
        QMessageBox::information(this,"成功","登录成功");
        Deal*d=new Deal(userid);
        d->setAttribute(Qt::WA_DeleteOnClose);
        d->show();
        this->close();

    }
    else{
        QMessageBox::warning(this, "失败", "用户名或密码错误！");
    }
}
void MainWindow::on_sign_in_clicked()
{
    Sign_in *s=new Sign_in();
    s->setAttribute(Qt::WA_DeleteOnClose);
    s->show();
}
