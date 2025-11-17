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
    QString sql="select Username from Users where Username=?";
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

void Sign_in::on_Sign_in_Button_clicked()
{
    QString username=ui->Sign_in_UsernameT->text().trimmed();
    QString password=ui->Sign_in_PassWordT->text().trimmed();
    QString passwordA=ui->Sign_in_PassWordAT->text().trimmed();
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

    if (checkUsername(username)) {
        QMessageBox::warning(this, "提示", "该用户名已被注册，请更换！");
        return;
    }
    QSqlQuery query;
    QString insertSql = "INSERT INTO users (Username, PWord) VALUES (?, ?)";
    query.prepare(insertSql);
    query.addBindValue(username);
    query.addBindValue(password);

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

