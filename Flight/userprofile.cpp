#include "userprofile.h"
#include "ui_userprofile.h"
#include "sign_in.h"
#include "edit_infor.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
UserProfile::UserProfile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    connect(ui->btn_back, &QPushButton::clicked, this, &UserProfile::on_btn_back_clicked);
}
UserProfile::UserProfile(const QString &userID,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    this->userID=userID;
    connect(ui->btn_back, &QPushButton::clicked, this, &UserProfile::on_btn_back_clicked);
}
UserProfile::~UserProfile()
{
    delete ui;
}
void UserProfile::on_btn_back_clicked()
{
    emit backRequested(); // 发送信号通知主窗口切换回去
}
void UserProfile::on_pushButton_4_clicked()
{
    emit myOrdersRequested();
}
void UserProfile::on_pushButton_8_clicked()
{
    Sign_in *s = new Sign_in();
    s->show();
}
void UserProfile::on_pushButton_7_clicked()
{
    emit logoutRequested();
}
void UserProfile::on_pushButton_9_clicked()
{
    int ret = QMessageBox::question(this, "注销", "确定要退出登录吗？",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        emit logoutRequested();
    }
}

void UserProfile::on_pushButton_5_clicked()
{
    edit_infor *e=new edit_infor(ui->txt_UserAccount->text(),ui->txt_Username->text(),this);
    connect(e,&edit_infor::change_name,this,[this](QString name){
        ui->txt_Username->setText(name);
    });
    connect(e,&edit_infor::change_jianjie,this,[this](QString jianjie){
        ui->txt_jianjie->setText(jianjie);
    });
    connect(e, &QDialog::finished, this, [this]{
        this->show();
        // 或者调用 getData(userID) 重新加载数据库信息
    });
    this->hide();
    e->exec();
}
void UserProfile::getData(const QString &userID)
{
    qDebug() << "getData called with userID:" << userID;
    if (userID.isEmpty()) {
        qDebug() << "UserID is empty!";
        return;
    }
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        qDebug() << "数据库未连接！";
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT Username, IDCard, jianjie FROM users WHERE UserID = ?");
    query.addBindValue(userID);
    if (query.exec() && query.next()) {
        QString username = query.value(0).toString();
        QString idCard = query.value(1).toString();
        QString jianjie = query.value(2).toString();
        ui->txt_Username->setText(username);
        ui->txt_UserAccount->setText(idCard);
        ui->txt_jianjie->setText(jianjie);
    } else {
        QString errorMsg = query.lastError().text();
        if (errorMsg.isEmpty()) {
            errorMsg = "无法找到该用户信息，UserID可能不存在";
        }
        qDebug() << "查询用户信息失败：" << errorMsg;
        qDebug() << "UserID = " << userID;
        QMessageBox::warning(this, "错误", "查询用户信息失败：\n" + errorMsg);
    }
}
