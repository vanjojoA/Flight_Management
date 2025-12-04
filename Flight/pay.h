#ifndef PAY_H
#define PAY_H

#include <QWidget>
#include <QDoubleSpinBox>
namespace Ui {
class Pay;
}

class Pay : public QWidget
{
    Q_OBJECT

public:
    explicit Pay(QWidget *parent = nullptr);
    ~Pay();
    void setUserID(const QString &id);
    void setFixedAmount(double amount);
signals:
    void paymentSuccess();


private slots:
    void on_btn_confirm_clicked();
    void on_btn_cancel_clicked();
    void on_amount_changed(double val);
private:
    Ui::Pay *ui;
    QString currentUserID;
    void resetInterface();
};

#endif // PAY_H
