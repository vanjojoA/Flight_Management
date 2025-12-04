#include "edit_infor.h"
#include "ui_edit_infor.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QBuffer>
#include <QPixmap>
#include <QIODevice>

edit_infor::edit_infor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_infor)
{
    ui->setupUi(this);
}

edit_infor::edit_infor(QString userID, QString username, QWidget *parent)
    : QDialog(parent)
    , userID(userID)
    , username(username)
    , avatarChanged(false)
    , ui(new Ui::edit_infor)
{
    ui->setupUi(this);


    ui->old_name->setText(username);

    qDebug() << "edit_infor 初始化 - UserID:" << userID << " 传入的Username:" << username;

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未连接";
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT Username, jianjie, avatar FROM users WHERE UserID = ?");

    query.addBindValue(userID.toInt());

    if (query.exec()) {
        if (query.next()) {
            QString dbUsername = query.value(0).toString();
            if (!dbUsername.isEmpty()) {
                ui->old_name->setText(dbUsername);
                this->username = dbUsername;
            }
            this->jianjie = query.value(1).toString();
            ui->new_jianjie->setText(this->jianjie);

            QVariant avatarVar = query.value(2);
            if (!avatarVar.isNull() && !avatarVar.toByteArray().isEmpty()) {
                QPixmap pixmap;
                if (pixmap.loadFromData(avatarVar.toByteArray())) {
                    this->Avatar = pixmap;
                    ui->label_5->setPixmap(pixmap.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
            } else {
                ui->label_5->setText("暂无头像");
            }
        }
        query.finish();
    } else {
        qDebug() << "SQL查询失败:" << query.lastError().text();
        query.finish();
    }
}

edit_infor::~edit_infor()
{
    delete ui;
}

void edit_infor::on_pushButton_clicked()
{
    // 打开文件对话框选择图片
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择头像"), QString(), tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (filePath.isEmpty()) {
        return;
    }

    QPixmap image(filePath);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("无效图片"), tr("无法加载所选文件。"));
        return;
    }

    // 缩放图片，避免数据库存储过大的原始图片
    QPixmap scaledPixmap = image.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 更新预览和成员变量
    ui->label_5->setPixmap(scaledPixmap.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->Avatar = scaledPixmap;
    this->avatarChanged = true;
}


void edit_infor::accept()
{
    QString newUsername = ui->new_name->text().trimmed();
    QString newJianjie = ui->new_jianjie->text().trimmed();

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, "警告", "数据库未连接！");
        return;
    }

    QSqlQuery query(db);
    int actualUserID = -1;

    bool isInt;
    int idVal = this->userID.toInt(&isInt);
    if (isInt) {
        query.prepare("SELECT UserID FROM users WHERE UserID = ?");
        query.addBindValue(idVal);
        if (query.exec() && query.next()) {
            actualUserID = query.value(0).toInt();
        }
    }
    query.finish(); // 显式关闭

    if (actualUserID == -1) {
        query.prepare("SELECT UserID FROM users WHERE IDCard = ? OR Username = ?");
        query.addBindValue(this->userID);
        query.addBindValue(this->userID);
        if (query.exec() && query.next()) {
            actualUserID = query.value(0).toInt();
        }
        query.finish(); // 显式关闭
    }


    if (actualUserID == -1) {
        QMessageBox::warning(this, "错误", "无法找到该用户的数据库记录");
        return;
    }

    QSqlQuery updateQuery(db);

    // 准备头像数据
    QByteArray avatarData;
    bool needUpdateAvatar = false;
    if (this->avatarChanged && !this->Avatar.isNull()) {
        QBuffer buffer(&avatarData);
        if (buffer.open(QIODevice::WriteOnly)) {
            this->Avatar.save(&buffer, "PNG");
            needUpdateAvatar = !avatarData.isEmpty();
        }
    }

    QString sql = "UPDATE users SET ";
    QList<QVariant> bindValues;
    bool hasChanged = false;

    if (!newUsername.isEmpty() && newUsername != this->username) {
        sql += "Username=?, ";
        bindValues.append(newUsername);
        hasChanged = true;
    }
    if (newJianjie != this->jianjie) {
        sql += "jianjie=?, ";
        bindValues.append(newJianjie);
        hasChanged = true;
    }
    if (needUpdateAvatar) {
        sql += "avatar=?, ";
        bindValues.append(avatarData);
        hasChanged = true;
    }

    if (!hasChanged) {
        QDialog::accept();
        return;
    }

    sql.chop(2);
    sql += " WHERE UserID=?";
    bindValues.append(actualUserID);

    updateQuery.prepare(sql);
    for (const auto &val : bindValues) {
        updateQuery.addBindValue(val);
    }

    if (!updateQuery.exec()) {
        qDebug() << "Update Error:" << updateQuery.lastError().text();
        QMessageBox::warning(this, "警告", "更新失败：" + updateQuery.lastError().text());
        updateQuery.finish(); // 【修改点2】失败时也要 finish
        return;
    }

    // 发送信号更新界面
    if (!newUsername.isEmpty() && newUsername != this->username) {
        emit change_name(this->username, newUsername);
    }
    if (newJianjie != this->jianjie) {
        emit change_jianjie(this->jianjie, newJianjie);
    }
    if (needUpdateAvatar) {
        emit change_avatar(this->Avatar);
    }

    updateQuery.finish();
    QMessageBox::information(this, "成功", "用户信息修改成功！");
    QDialog::accept();
}
