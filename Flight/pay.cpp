#include "pay.h"
#include "ui_pay.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPixmap>
Pay::Pay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pay)
{
    ui->setupUi(this);
    ui->label_alipay_img->setPixmap(QPixmap(":/pay_imag/alipay.jpg"));
    ui->label_wechat_img->setPixmap(QPixmap(":/pay_imag/wechat.jpg"));

    connect(ui->spinBox_amount, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &Pay::on_amount_changed);

    ui->label_amount->setText("¥ 0.00");


}

Pay::~Pay()
{
    delete ui;
}
void Pay::setUserID(const QString &id)
{
    this->currentUserID = id;
    resetInterface(); // 每次设置用户时重置界面
}
void Pay::setFixedAmount(double amount)
{
    ui->spinBox_amount->setValue(amount);
    ui->spinBox_amount->setEnabled(false); // 订单支付时禁止修改金额
}
void Pay::on_amount_changed(double val)
{
    // 当 spinBox 数值改变时，实时更新 label_amount 文本框
    ui->label_amount->setText(QString("¥ %1").arg(QString::number(val, 'f', 2)));
}
void Pay::on_btn_confirm_clicked()
{
    double amount = ui->spinBox_amount->value();

    if (amount <= 0) {
        QMessageBox::warning(this, "提示", "请输入有效的充值金额！");
        return;
    }

    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "错误", "未获取到用户信息，无法充值！");
        return;
    }

    // 更新数据库余额
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }

    QSqlQuery query;
    db.transaction();

    // 更新 users 表中的 Balance 字段
    query.prepare("UPDATE users SET Balance = Balance + ? WHERE UserID = ?");
    query.addBindValue(amount);
    query.addBindValue(currentUserID);

    if (query.exec()) {
        db.commit();
        QMessageBox::information(this, "成功", QString("充值成功！\n已充值: %1 元").arg(amount));

        // 发送成功信号
        emit paymentSuccess();

        // 关闭窗口
        this->close();
    } else {
        db.rollback();
        QMessageBox::critical(this, "失败", "充值失败：" + query.lastError().text());
    }
}

void Pay::on_btn_cancel_clicked()
{
    resetInterface();
    QMessageBox::information(this, "取消",QString("本次充值已取消"));

}

void Pay::resetInterface()
{
    // 恢复金额为 0
    ui->spinBox_amount->setEnabled(true); // 恢复可编辑
    ui->spinBox_amount->setValue(0.00);
    ui->label_amount->setText("¥ 0.00");
}
