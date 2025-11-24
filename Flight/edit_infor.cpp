#include "edit_infor.h"
#include "ui_edit_infor.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QBuffer>
edit_infor::edit_infor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_infor)
{
    ui->setupUi(this);
}

edit_infor::edit_infor(QString userID,QString username,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_infor)
{
    ui->setupUi(this);
    ui->old_name->setText(username);
    this->username=username;
    this->userID=userID;
    //connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&edit_infor::on_buttonBox_accepted);
}
void edit_infor:: on_buttonBox_accepted(){
    QString newUsername = ui->new_name->text().trimmed();
    QString newjianjie=ui->new_jianjie->text().trimmed();
    emit change_name(newUsername);
    emit change_jianjie(newjianjie);
    this->close();
}
void edit_infor::accept()
{
    QString newUsername = ui->new_name->text().trimmed();
    QString newjianjie = ui->new_jianjie->text().trimmed();

    if (newUsername.isEmpty()) {
        QMessageBox::warning(this, "警告", "新用户名不能为空！");
        return;
    }
    QSqlQuery query;
    QString sql;
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法修改记录！";
        return;
    }
    sql="update users set username=?,jianjie=? where IDCard=?";
    query.prepare(sql);
    query.addBindValue(newUsername);
    query.addBindValue(newjianjie);
    query.addBindValue(this->userID);
    if (!query.exec()) {
        qDebug() << "修改记录失败：" << query.lastError().text();
        qDebug() << "执行的 SQL：" << sql;
        QMessageBox::warning(this,"警告","执行sql失败");
        return ;
    }
    if (query.numRowsAffected() > 0) {
        qDebug() << "成功修改" << query.numRowsAffected() << "条记录";
        QDialog::accept();
    } else {
        qDebug() << "未找到匹配的记录（或新值与旧值一致），无修改";
        QMessageBox::warning(this,"警告","未找到匹配的记录（或新值与旧值一致），无修改");
        return ;
    }
    emit change_name(newUsername);
    emit change_jianjie(newjianjie);
    QDialog::accept();
}
edit_infor::~edit_infor()
{
    delete ui;
}

void edit_infor::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("选择头像"),QString(),tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (filePath.isEmpty()) {
        return;
    }

    QImage image(filePath);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("无效图片"), tr("无法加载所选文件。"));
        return;
    }
}

