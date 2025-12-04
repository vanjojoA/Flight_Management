#include "userprofile.h"
#include "ui_userprofile.h"
#include "sign_in.h"
#include "edit_infor.h"
#include "passenger.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>

UserProfile::UserProfile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    connect(ui->btn_back, &QPushButton::clicked, this, &UserProfile::on_btn_back_clicked);
}


UserProfile::UserProfile(const QString &userID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);

    this->userID = userID;
    connect(ui->btn_back, &QPushButton::clicked, this, &UserProfile::on_btn_back_clicked);
    if (!this->userID.isEmpty()) {
        getData(this->userID);
    }
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

void UserProfile::on_pushButton_10_clicked(){
    passenger*s=new passenger(currentUsername);
    s->show();
}

void UserProfile::on_pushButton_5_clicked()
{
    edit_infor *e = new edit_infor(this->userID, ui->txt_Username->text(), this);

    connect(e, &edit_infor::change_name, this, [this](QString old, QString name){
        if (name == ""){
            ui->txt_Username->setText(old);
            this->currentUsername = name;
        } else {
            ui->txt_Username->setText(name);
            this->currentUsername = old;
        }
    });

    connect(e, &edit_infor::change_jianjie, this, [this](QString old, QString jianjie){
        if (jianjie == ""){
            ui->txt_jianjie->setText(old);
        } else {
            ui->txt_jianjie->setText(jianjie);
        }
    });

    connect(e, &edit_infor::change_avatar, this, [this](QPixmap pixmap){
        ui->label_2->setPixmap(pixmap);
    });

    connect(e, &QDialog::finished, this, [this]{
        this->show();
        if (!this->userID.isEmpty()) {
            getData(this->userID);
        }
    });
    this->hide();
    e->exec();
}


void UserProfile::getData(const QString &userID)
{
    qDebug() << "getData called with userID:" << userID;
    if (userID.isEmpty()) return;

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return;

    QSqlQuery query(db);
    query.setForwardOnly(true);

    query.prepare("SELECT Username, IDCard, jianjie, avatar, Balance FROM users WHERE UserID = ?");
    query.addBindValue(userID.toInt());

    if (query.exec()) {
        if (query.next()) {
            QString username = query.value(0).toString();
            QString idCard = query.value(1).toString();
            QString jianjie = query.value(2).toString();
            QByteArray avatarData = query.value(3).toByteArray();
            double balance = query.value(4).toDouble();
            ui->txt_Username->setText(username);
            this->currentUsername = username;
            ui->txt_UserAccount->setText(idCard);
            ui->txt_jianjie->setText(jianjie);
            ui->txt_yu->setText(QString::number(balance, 'f', 2));
            if (!avatarData.isEmpty()) {
                QPixmap pixmap;
                if (pixmap.loadFromData(avatarData)) {
                    ui->label_2->setPixmap(pixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                } else {
                    ui->label_2->clear();
                }
            } else {
                ui->label_2->clear();
            }
        }
        query.finish(); // 成功时关闭
    } else {
        qDebug() << "getData Error:" << query.lastError().text();
        query.finish();
    }
}
void UserProfile::on_btn_favorites_clicked()
{
    emit myFavoritesRequested();
}

void UserProfile::on_btn_recharge_clicked(){
    if (payWindow == nullptr) {
        payWindow = new Pay();

        // 当支付成功时，刷新个人中心数据
        connect(payWindow, &Pay::paymentSuccess, this, [this](){
            if (!this->userID.isEmpty()) {
                this->getData(this->userID); // 刷新余额显示
            }
        });

        connect(payWindow, &QWidget::destroyed, this, [=](){ payWindow = nullptr; });
    }
    payWindow->setUserID(this->userID);

    payWindow->show();
    payWindow->raise();
    payWindow->activateWindow();
}
