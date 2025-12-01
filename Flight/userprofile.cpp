#include "userprofile.h"
#include "ui_userprofile.h"
#include "sign_in.h"
#include <QMessageBox>
#include"edit_info.h"

UserProfile::UserProfile(QString userID, QString username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);

    // 初始化成员变量
    this->userID = userID;
    this->username = username;

    // 初始化界面显示
    ui->label_username->setText(username);
}
UserProfile::UserProfile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    connect(ui->btn_back, &QPushButton::clicked, this, &UserProfile::on_btn_back_clicked);
}

UserProfile::~UserProfile()
{
    delete ui;
}
void UserProfile::on_btn_back_clicked()
{
    emit backRequested();
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
    QMessageBox msgBox(QMessageBox::Question, "取消登录", "确定要退出登录吗？",
                       QMessageBox::Yes | QMessageBox::No, this);

    msgBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: white;"
        "}"
        "QLabel {"
        "    color: black; "
        "}"
        "QPushButton {"
        "    min-width: 80px; "
        "   color:black;"
        "   background-color:white;"
        "   border: 1px solid black; "
        "}"
        );
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        emit logoutRequested();
    }
}
void UserProfile::on_pushButton_9_clicked()
{
    QMessageBox msgBox(QMessageBox::Question, "注销", "确定要注销吗？",
                       QMessageBox::Yes | QMessageBox::No, this);

    msgBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: white;"
        "}"
        "QLabel {"
        "    color: black; "
        "}"
        "QPushButton {"
        "    min-width: 80px;"
        "   color:black;"
        "   background-color:white; "
        "   border: 1px solid black;"
        "}"
        );
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        emit logoutRequested();
    }
}
void UserProfile::on_edit_btn_clicked(){
    edit_info* editDlg=new edit_info(this->userID,this->username,this);
    connect(editDlg, &edit_info::change_name, this, [=](QString newName){
        ui->label_username->setText(newName); // 更新界面标签
        this->username = newName;             // 更新本地成员变量
    });
    connect(editDlg, &edit_info::change_jianjie, this, [=](QString newJianjie){
        ui->label_jianjie->setText(newJianjie); // 假设你有显示简介的 label
    });
    editDlg->exec();
    delete editDlg;
}
void UserProfile::on_pushButton_2_clicked(){
    emit myFavoritesRequested();
}
