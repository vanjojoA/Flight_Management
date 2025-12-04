#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>
#include"pay.h"
namespace Ui {
class UserProfile;
}

class UserProfile : public QWidget
{
    Q_OBJECT

public:
    QString userID;
    QString username;
    explicit UserProfile(QWidget *parent = nullptr);
    explicit UserProfile(const QString &userID, QWidget *parent = nullptr);
    ~UserProfile();

public slots:
    void getData(const QString &userID);

signals:
    void backRequested();
    void myOrdersRequested();
    void logoutRequested();
    void myFavoritesRequested();

private slots:
    void on_btn_back_clicked();
    void on_pushButton_4_clicked(); // 我的订单
    void on_pushButton_8_clicked(); // 注册
    void on_pushButton_7_clicked(); // 登录
    void on_pushButton_9_clicked(); // 注销
    void on_pushButton_10_clicked();//增加乘客
    void on_pushButton_5_clicked();//编辑个人资料
    void on_btn_favorites_clicked();//收藏
    void on_btn_recharge_clicked();//充值

private:
    Ui::UserProfile *ui;
    QString currentUsername;
    Pay* payWindow=nullptr;
};

#endif // USERPROFILE_H
