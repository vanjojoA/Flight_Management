#include "order_dialog.h"
#include "ui_order_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>

OrderDialog::OrderDialog(int ticketId, int userId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OrderDialog)
    , ticketId(ticketId)
    , userId(userId)
    , ticketPrice(0.0)
{
    ui->setupUi(this);
    setWindowTitle("填写订单信息");
    setModal(true);
    
    loadTicketInfo();
    ui->spinBox_count->setMinimum(1);
    ui->spinBox_count->setMaximum(10);
    ui->spinBox_count->setValue(1);
    
    connect(ui->spinBox_count, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &OrderDialog::on_spinBox_count_valueChanged);
}

OrderDialog::~OrderDialog()
{
    delete ui;
}

void OrderDialog::loadTicketInfo()
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT TicketType, TicketNo, DepartureCity, ArrivalCity, "
                  "DepartureTime, ArrivalTime, Price, AvailableSeats, Company "
                  "FROM tickets WHERE TicketID = ?");
    query.addBindValue(ticketId);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "错误", "获取票务信息失败！");
        reject();
        return;
    }

    QString ticketType = query.value(0).toString();
    QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");
    
    ui->label_type->setText(typeName);
    ui->label_ticketNo->setText(query.value(1).toString());
    ui->label_route->setText(query.value(2).toString() + " → " + query.value(3).toString());
    
    QDateTime depTime = query.value(4).toDateTime();
    QDateTime arrTime = query.value(5).toDateTime();
    ui->label_departure->setText(depTime.toString("yyyy-MM-dd hh:mm"));
    ui->label_arrival->setText(arrTime.toString("yyyy-MM-dd hh:mm"));
    
    ticketPrice = query.value(6).toDouble();
    ui->label_price->setText(QString::number(ticketPrice, 'f', 2) + " 元");
    ui->label_available->setText(QString::number(query.value(7).toInt()) + " 张");
    ui->label_company->setText(query.value(8).toString());
    
    ui->spinBox_count->setMaximum(query.value(7).toInt());
    calculateTotal();
}

void OrderDialog::on_spinBox_count_valueChanged(int count)
{
    Q_UNUSED(count);
    calculateTotal();
}

void OrderDialog::calculateTotal()
{
    int count = ui->spinBox_count->value();
    double total = ticketPrice * count;
    ui->label_total->setText(QString::number(total, 'f', 2) + " 元");
}

void OrderDialog::on_btn_confirm_clicked()
{
    QString passengerName = ui->lineEdit_name->text().trimmed();
    QString passengerID = ui->lineEdit_id->text().trimmed();
    QString contactPhone = ui->lineEdit_phone->text().trimmed();
    int count = ui->spinBox_count->value();

    if (passengerName.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入乘客姓名！");
        return;
    }
    if (contactPhone.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入联系电话！");
        return;
    }

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }

    // 检查可用座位数
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT AvailableSeats FROM tickets WHERE TicketID = ?");
    checkQuery.addBindValue(ticketId);
    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::warning(this, "错误", "检查座位失败！");
        return;
    }
    int availableSeats = checkQuery.value(0).toInt();
    if (availableSeats < count) {
        QMessageBox::warning(this, "提示", QString("可用座位不足！当前可用：%1 张").arg(availableSeats));
        return;
    }

    // 生成订单号
    QString orderNo = "ORD" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + 
                      QString::number(QRandomGenerator::global()->bounded(1000000), 10).rightJustified(6, '0');

    // 开始事务
    QSqlDatabase::database().transaction();

    try {
        // 插入订单
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO orders (UserID, TicketID, OrderNo, PassengerName, "
                           "PassengerIDCard, ContactPhone, TicketCount, TotalPrice, OrderStatus) "
                           "VALUES (?, ?, ?, ?, ?, ?, ?, ?, 'Paid')");
        insertQuery.addBindValue(userId);
        insertQuery.addBindValue(ticketId);
        insertQuery.addBindValue(orderNo);
        insertQuery.addBindValue(passengerName);
        insertQuery.addBindValue(passengerID);
        insertQuery.addBindValue(contactPhone);
        insertQuery.addBindValue(count);
        insertQuery.addBindValue(ticketPrice * count);

        if (!insertQuery.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "错误", "创建订单失败：" + insertQuery.lastError().text());
            return;
        }

        // 更新票务可用座位数
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE tickets SET AvailableSeats = AvailableSeats - ? WHERE TicketID = ?");
        updateQuery.addBindValue(count);
        updateQuery.addBindValue(ticketId);

        if (!updateQuery.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "错误", "更新座位失败：" + updateQuery.lastError().text());
            return;
        }

        // 提交事务
        QSqlDatabase::database().commit();
        QMessageBox::information(this, "成功", QString("订单创建成功！\n订单号：%1").arg(orderNo));
        accept();
    } catch (...) {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "错误", "订票过程中发生错误！");
    }
}

void OrderDialog::on_btn_cancel_clicked()
{
    reject();
}

