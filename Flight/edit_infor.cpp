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

edit_infor::edit_infor(QString userID,QString username,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_infor)
    , avatarChanged(false)  // 初始化为false，表示还没有选择新头像
{
    ui->setupUi(this);
    ui->old_name->setText(username);
    this->username=username;
    this->userID=userID;
    
<<<<<<< HEAD
=======
    // 从数据库加载当前的简介和头像
>>>>>>> 424bc0a8b89776bc4a6d5328940fb4156ce50bcf
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法加载用户信息";
    } else {
        QSqlQuery query;
        query.prepare("SELECT jianjie, avatar FROM users WHERE IDCard = ?");
<<<<<<< HEAD
        query.addBindValue(userID); // userID 是身份证号，匹配查询条件
        query.finish();

        if (!query.exec()) {
            qDebug() << "查询用户信息失败：" << query.lastError().text();
            return;
        }

        if (query.next()) {
            // 加载简介
            this->jianjie = query.value(0).toString();
            ui->new_jianjie->setText(this->jianjie);

            // 加载头像（处理 LONGBLOB 的 NULL 和有效数据）
            QVariant avatarVar = query.value(1);
            if (!avatarVar.isNull() && !avatarVar.toByteArray().isEmpty()) {
                QByteArray avatarData = avatarVar.toByteArray();
                qDebug() << "从 LONGBLOB 读取到头像数据，大小：" << avatarData.size() << "字节";
=======
        query.addBindValue(userID);
        if (query.exec() && query.next()) {
            this->jianjie = query.value(0).toString();
            ui->new_jianjie->setText(this->jianjie);
            
            // 加载当前头像到预览（但不标记为已更改）
            QByteArray avatarData = query.value(1).toByteArray();
            if (!avatarData.isEmpty()) {
>>>>>>> 424bc0a8b89776bc4a6d5328940fb4156ce50bcf
                QPixmap pixmap;
                if (pixmap.loadFromData(avatarData)) {
                    this->Avatar = pixmap;
                    ui->label_5->setPixmap(pixmap.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
<<<<<<< HEAD
                } else {
                    qDebug() << "头像数据无效，预览区空白";
                    this->Avatar = QPixmap();
                }
            } else {
                qDebug() << "数据库中 avatar 字段为 NULL 或空数据，预览区空白";
                this->Avatar = QPixmap();
                ui->label_5->setPixmap(QPixmap());  // 预览区空白
            }
        } else {
            qDebug() << "未找到 IDCard = " << userID << " 的用户";
            this->jianjie = "";  // 原始简介为空
            this->Avatar = QPixmap();
            ui->label_5->setPixmap(QPixmap());  // 预览区空白
        }
        query.finish();
    }
=======
                }
            }
        }
    }
    //connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&edit_infor::on_buttonBox_accepted);
>>>>>>> 424bc0a8b89776bc4a6d5328940fb4156ce50bcf
}
void edit_infor:: on_buttonBox_accepted(){
    QString newUsername = ui->new_name->text().trimmed();
    QString newjianjie=ui->new_jianjie->text().trimmed();
    emit change_name(this->username,newUsername);
    emit change_jianjie(this->jianjie,newjianjie);
    this->close();
}
void edit_infor::accept()
{
    QString newUsername = ui->new_name->text().trimmed();
<<<<<<< HEAD
    QString newJianjie = ui->new_jianjie->text().trimmed();

    // 2. 检查数据库连接
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未连接，无法修改记录！";
        QMessageBox::warning(this, "警告", "数据库未连接！");
        return;
    }

    // 3. 查询 UserID（通过 IDCard 确认用户）
    QSqlQuery query(db);
    query.prepare("SELECT UserID FROM users WHERE IDCard = ?");
    query.addBindValue(this->userID);  // 用已有 userID（身份证号）查询
    query.finish();

    if (!query.exec() || !query.next()) {
        qDebug() << "无法找到用户，IDCard = " << this->userID << "，错误：" << query.lastError().text();
        QMessageBox::warning(this, "警告", "无法找到用户信息！");
        return;
    }
    int actualUserID = query.value(0).toInt();
    query.finish();

    // 4. 处理头像数据（仅当用户选择新头像时生成字节数组）
    QByteArray avatarData;
    bool needUpdateAvatar = false;
    if (this->avatarChanged && !this->Avatar.isNull()) {
        QBuffer buffer(&avatarData);
        if (buffer.open(QIODevice::WriteOnly)) {
            bool saveOk = this->Avatar.save(&buffer, "PNG", 80);
            buffer.close();
            if (saveOk && !avatarData.isEmpty()) {
                qDebug() << "头像转换成功，字节大小：" << avatarData.size() << "字节";
                needUpdateAvatar = true;
            } else {
                qDebug() << "头像转换失败，放弃保存头像";
                this->avatarChanged = false;
            }
        } else {
            qDebug() << "缓冲区打开失败，放弃保存头像";
            this->avatarChanged = false;
        }
    }

    // 5. 构建 SQL 语句（仅更新有变化的字段，兼容无需输入用户名）
    QString sql = "UPDATE users SET ";
    QList<QVariant> bindValues;
    bool hasChanged = false;

    // 用户名：为空则不更新（保留原始值），不为空且不同则更新
    if (!newUsername.isEmpty() && newUsername != this->username) {
        sql += "username=?, ";
        bindValues.append(newUsername);
        hasChanged = true;
        qDebug() << "用户名变更：" << this->username << " → " << newUsername;
    }

    // 简介：与原始值不同则更新（允许为空）
    if (newJianjie != this->jianjie) {
        sql += "jianjie=?, ";
        bindValues.append(newJianjie);
        hasChanged = true;
        qDebug() << "简介变更：" << this->jianjie << " → " << newJianjie;
    }

    // 头像：用户选择了新头像则更新
    if (needUpdateAvatar) {
        sql += "avatar=?, ";
        bindValues.append(avatarData);
        hasChanged = true;
        qDebug() << "头像变更：更新为新选择的图片";
    }

    // 6. 检查是否有字段需要更新
    if (!hasChanged) {
        QMessageBox::information(this, "提示", "未修改任何信息（新值与旧值一致）！");
        return;
    }

    // 7. 完善 SQL 语句（移除末尾逗号，添加 WHERE 条件）
    sql.chop(2);  // 移除最后一个 ", "
    sql += " WHERE UserID=?";
    bindValues.append(actualUserID);  // 绑定 UserID
    qDebug() << "执行 SQL：" << sql;

    // 8. 执行更新
    query.prepare(sql);
    // 绑定所有参数
    for (int i = 0; i < bindValues.size(); ++i) {
        query.addBindValue(bindValues.at(i));
    }

    query.finish();
    if (!query.exec()) {
        qDebug() << "修改记录失败：" << query.lastError().text() << "，SQL：" << sql;
        QMessageBox::warning(this, "警告", "执行 SQL 失败：" + query.lastError().text());
        return;
    }

    // 9. 处理更新结果
    if (query.numRowsAffected() > 0) {
        qDebug() << "成功修改" << query.numRowsAffected() << "条记录，UserID=" << actualUserID;
        // 仅当字段变更时才发送信号（信号参数为引用，与头文件一致）
        if (!newUsername.isEmpty() && newUsername != this->username) {
            emit change_name(this->username, newUsername);
        }
        if (newJianjie != this->jianjie) {
            emit change_jianjie(this->jianjie, newJianjie);
        }
        if (needUpdateAvatar) {
            emit change_avatar(this->Avatar);
        }
        QMessageBox::information(this, "成功", "用户信息修改成功！");
        QDialog::accept();
    } else {
        qDebug() << "未找到匹配的记录，修改失败";
        QMessageBox::warning(this, "警告", "未找到匹配的用户记录，修改失败！");
=======
    QString newjianjie = ui->new_jianjie->text().trimmed();

    if (newUsername.isEmpty()) {
        return;
    }
    QSqlQuery query;
    QString sql;
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "数据库未连接，无法修改记录！";
        return;
    }
    query.prepare("SELECT UserID FROM users WHERE IDCard = ?");
    query.addBindValue(this->userID);
    if (!query.exec() || !query.next()) {
        qDebug() << "无法找到用户，IDCard = " << this->userID;
        QMessageBox::warning(this, "警告", "无法找到用户信息");
        return;
    }
    QString actualUserID = query.value(0).toString();
    QByteArray avatarData;
    // 只有用户选择了新头像时才保存（使用avatarChanged标志）
    qDebug() << "accept()中检查头像，avatarChanged=" << this->avatarChanged << "，this->Avatar.isNull()=" << this->Avatar.isNull() << "，尺寸：" << this->Avatar.width() << "x" << this->Avatar.height();
    if (this->avatarChanged && !this->Avatar.isNull()) {
        QBuffer buffer(&avatarData);
        buffer.open(QIODevice::WriteOnly);
        this->Avatar.save(&buffer, "PNG");
        qDebug() << "准备保存新头像，大小：" << avatarData.size() << "字节，Avatar尺寸：" << this->Avatar.width() << "x" << this->Avatar.height();
    } else {
        qDebug() << "用户未选择新头像，不更新头像字段（保持数据库中的旧头像）";
    }
    if (this->avatarChanged && !this->Avatar.isNull()) {
        sql = "UPDATE users SET username=?, jianjie=?, avatar=? WHERE UserID=?";
        query.prepare(sql);
        query.addBindValue(newUsername);
        query.addBindValue(newjianjie);
        query.addBindValue(avatarData);
        query.addBindValue(actualUserID);
        qDebug() << "更新用户信息（包含头像），UserID=" << actualUserID;
    } else {
        sql = "UPDATE users SET username=?, jianjie=? WHERE UserID=?";
        query.prepare(sql);
        query.addBindValue(newUsername);
        query.addBindValue(newjianjie);
        query.addBindValue(actualUserID);
        qDebug() << "更新用户信息（不包含头像），UserID=" << actualUserID;
    }

    if (!query.exec()) {
        qDebug() << "修改记录失败：" << query.lastError().text();
        qDebug() << "执行的 SQL：" << sql;
        QMessageBox::warning(this, "警告", "执行sql失败");
        return;
    }
    if (query.numRowsAffected() > 0) {
        qDebug() << "成功修改" << query.numRowsAffected() << "条记录，UserID=" << actualUserID;
        emit change_name(this->username, newUsername);
        emit change_jianjie(this->jianjie,newjianjie);
        if (this->avatarChanged && !this->Avatar.isNull()) {
            emit change_avatar(this->Avatar);
        }
        QDialog::accept();
    } else {
        qDebug() << "未找到匹配的记录（或新值与旧值一致），无修改";
        QMessageBox::warning(this, "警告", "未找到匹配的记录（或新值与旧值一致），无修改");
>>>>>>> 424bc0a8b89776bc4a6d5328940fb4156ce50bcf
        return;
    }
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
    QPixmap image(filePath);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("无效图片"), tr("无法加载所选文件。"));
        return;
    }
    QPixmap scaledPixmap = image.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_5->setPixmap(scaledPixmap);
    this->Avatar = scaledPixmap;
    this->avatarChanged = true;
    qDebug() << "选择新头像，更新this->Avatar，尺寸：" << this->Avatar.width() << "x" << this->Avatar.height() << "，avatarChanged=true";
    emit change_avatar(scaledPixmap);
}

