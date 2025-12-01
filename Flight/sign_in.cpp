<<<<<<< HEAD
#include "sign_in.h"
#include "ui_sign_in.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

Sign_in::Sign_in(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sign_in)
{
    ui->setupUi(this);
}

Sign_in::~Sign_in()
{
    delete ui;
}

bool checkUsername(QString &username){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法检查用户名！";
        return false;
    }
    QSqlQuery query;
    QString sql="SELECT Username FROM users WHERE Username=?";
    query.prepare(sql);
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << "检查用户名失败：" << query.lastError().text();
        return true;
    }
    if (query.next()) {
        return true;
    } else {
        return false;
    }
}

bool checkUserID(QString &ID){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法检查用户名！";
        return false;
    }
    QSqlQuery query;
    QString sql="SELECT IDCard FROM users WHERE IDCard=?";
    query.prepare(sql);
    query.addBindValue(ID);
    if (!query.exec()) {
        qDebug() << "检查用户ID失败：" << query.lastError().text();
        return true;
    }
    if (query.next()) {
        return true;
    } else {
        return false;
    }
}

void Sign_in::on_Sign_in_Button_clicked()
{
    QString username=ui->Sign_in_UsernameT->text().trimmed();
    QString password=ui->Sign_in_PassWordT->text().trimmed();
    QString passwordA=ui->Sign_in_PassWordAT->text().trimmed();
    QString ID=ui->ID->text().trimmed();
    if(username.isEmpty()||password.isEmpty()){
        QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
        return;
    }
    if(passwordA.isEmpty()){
        QMessageBox::warning(this,"提示","请确认密码");
        return;
    }
    if(passwordA!=password){
        QMessageBox::warning(this,"提示","请确认两次密码是否一致");
        return;
    }
    if(ID.isEmpty()){
        QMessageBox::warning(this,"提示","ID不能为空！");
        return;
    }

    // 连接数据库
    QSqlDatabase dbcon;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        dbcon = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        dbcon = QSqlDatabase::addDatabase("QMYSQL");
        dbcon.setHostName("127.0.0.1");
        dbcon.setPort(3306);
        dbcon.setDatabaseName("flight");
        dbcon.setUserName("root");
        dbcon.setPassword("328168");
    }
    if (!dbcon.isOpen()) {
        bool ok = dbcon.open();
        if (!ok) {
            QMessageBox::critical(this, "错误", "数据库连接失败：" + dbcon.lastError().text());
            return;
        }
    }

    if (checkUsername(username)) {
        QMessageBox::warning(this, "提示", "该用户名已被注册，请更换！");
        return;
    }
    if(checkUserID(ID)){
        QMessageBox::warning(this, "提示", "该ID已被注册，请更换！");
        return;
    }
    QSqlQuery query;
    QString insertSql = "INSERT INTO users (Username, PWord, IDCard) VALUES (?, ?, ?)";
    query.prepare(insertSql);
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(ID);

    if (query.exec()) {
        QMessageBox::information(this, "成功", "注册成功！");
        this->close();
    } else {
        QMessageBox::critical(this, "错误", "注册失败：" + query.lastError().text());
        qDebug() << "插入失败：" << query.lastError().text();
    }
}


void Sign_in::on_Sign_in_Cencel_clicked()
{
    this->close();
}

=======
#include "sign_in.h"
#include "ui_sign_in.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

Sign_in::Sign_in(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sign_in)
{
    ui->setupUi(this);
}

Sign_in::~Sign_in()
{
    delete ui;
}

bool checkUsername(QString &username){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法检查用户名！";
        return false;
    }
    QSqlQuery query;
    QString sql="SELECT Username FROM users WHERE Username=?";
    query.prepare(sql);
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << "检查用户名失败：" << query.lastError().text();
        return true;
    }
    if (query.next()) {
        return true;
    } else {
        return false;
    }
}

bool checkUserID(QString &ID){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法检查用户名！";
        return false;
    }
    QSqlQuery query;
    QString sql="SELECT IDCard FROM users WHERE IDCard=?";
    query.prepare(sql);
    query.addBindValue(ID);
    if (!query.exec()) {
        qDebug() << "检查用户ID失败：" << query.lastError().text();
        return true;
    }
    if (query.next()) {
        return true;
    } else {
        return false;
    }
}

void Sign_in::on_Sign_in_Button_clicked()
{
    QString username=ui->Sign_in_UsernameT->text().trimmed();
    QString password=ui->Sign_in_PassWordT->text().trimmed();
    QString passwordA=ui->Sign_in_PassWordAT->text().trimmed();
    QString ID=ui->ID->text().trimmed();
    if(username.isEmpty()||password.isEmpty()){
        QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
        return;
    }
    if(passwordA.isEmpty()){
        QMessageBox::warning(this,"提示","请确认密码");
        return;
    }
    if(passwordA!=password){
        QMessageBox::warning(this,"提示","请确认两次密码是否一致");
        return;
    }
    if(ID.isEmpty()){
        QMessageBox::warning(this,"提示","ID不能为空！");
        return;
    }

    // 连接数据库
    QSqlDatabase dbcon;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        dbcon = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        dbcon = QSqlDatabase::addDatabase("QMYSQL");
        dbcon.setHostName("127.0.0.1");
        dbcon.setPort(3306);
        dbcon.setDatabaseName("flight");
        dbcon.setUserName("root");
        dbcon.setPassword("328168");
    }
    if (!dbcon.isOpen()) {
        bool ok = dbcon.open();
        if (!ok) {
            QMessageBox::critical(this, "错误", "数据库连接失败：" + dbcon.lastError().text());
            return;
        }
    }

    if (checkUsername(username)) {
        QMessageBox::warning(this, "提示", "该用户名已被注册，请更换！");
        return;
    }
    if(checkUserID(ID)){
        QMessageBox::warning(this, "提示", "该ID已被注册，请更换！");
        return;
    }
    QSqlQuery query;
    QString insertSql = "INSERT INTO users (Username, PWord, IDCard) VALUES (?, ?, ?)";
    query.prepare(insertSql);
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(ID);

    if (query.exec()) {
        QMessageBox::information(this, "成功", "注册成功！");
        this->close();
    } else {
        QMessageBox::critical(this, "错误", "注册失败：" + query.lastError().text());
        qDebug() << "插入失败：" << query.lastError().text();
    }
}


void Sign_in::on_Sign_in_Cencel_clicked()
{
    this->close();
}

>>>>>>> 424bc0a8b89776bc4a6d5328940fb4156ce50bcf
