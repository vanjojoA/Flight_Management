
#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>

namespace Ui {
class UserProfile;
}

class UserProfile : public QWidget
{
    Q_OBJECT

public:
    QString userID;
    explicit UserProfile(QWidget *parent = nullptr);
    explicit UserProfile(const QString &username,QWidget *parent = nullptr);
    explicit UserProfile(const QString &userID, QWidget *parent = nullptr);
    ~UserProfile();

public slots:
    void getData(const QString &username);
signals:
    void backRequested(); // 定义返回信号
    void myOrdersRequested();
    void logoutRequested();
private slots:
    void on_btn_back_clicked();
    void on_pushButton_4_clicked(); // 我的订单
    void on_pushButton_8_clicked(); // 注册
    void on_pushButton_7_clicked(); // 登录
    void on_pushButton_9_clicked(); // 注销
    void on_pushButton_10_clicked();//增加乘客

    void on_pushButton_5_clicked();//编辑个人资料

private:
    Ui::UserProfile *ui;
    QString currentUsername;

};

#endif // USERPROFILE_H

