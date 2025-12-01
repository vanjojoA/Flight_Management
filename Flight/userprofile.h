#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>
#include"edit_info.h"

namespace Ui {
class UserProfile;
}

class UserProfile : public QWidget
{
    Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = nullptr);
    explicit UserProfile(QString userID, QString username, QWidget *parent = nullptr);
    ~UserProfile();

signals:
    void backRequested();
    void myOrdersRequested();
    void logoutRequested();
    void myFavoritesRequested();
private slots:
    void on_btn_back_clicked();
    void on_pushButton_2_clicked();//收藏
    void on_pushButton_4_clicked(); // 我的订单
    void on_pushButton_8_clicked(); // 注册
    void on_pushButton_7_clicked(); // 登录
    void on_pushButton_9_clicked(); // 注销
    void on_edit_btn_clicked();//编辑个人信息

private:
    Ui::UserProfile *ui;
    QString userID;
    QString username;
};

#endif // USERPROFILE_H
