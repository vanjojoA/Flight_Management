#ifndef EDIT_INFOR_H
#define EDIT_INFOR_H

#include <QDialog>

namespace Ui {
class edit_infor;
}

class edit_infor : public QDialog
{
    Q_OBJECT

public:
    explicit edit_infor(QWidget *parent = nullptr);
    explicit edit_infor(QString userID,QString username,QWidget*parent=nullptr);
    ~edit_infor();
    virtual void accept() override;
signals:
    void change_name(QString &oldname,QString &newname);
    void change_jianjie(QString &oldjianjie,QString &jianjie);
    void change_avatar(const QPixmap &pixmap);
private slots:
    void on_buttonBox_accepted();
    void on_pushButton_clicked();

private:
    QString userID;
    QString username;
    QPixmap Avatar;
    QString jianjie;
    bool avatarChanged;  // 标记用户是否选择了新头像
    Ui::edit_infor *ui;
};

#endif // EDIT_INFOR_H
