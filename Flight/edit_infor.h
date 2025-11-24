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
    void change_name(QString &newname);
    void change_jianjie(QString &jianjie);
private slots:
    void on_buttonBox_accepted();
    void on_pushButton_clicked();

private:
    QString userID;
    QString username;
    Ui::edit_infor *ui;
};

#endif // EDIT_INFOR_H
