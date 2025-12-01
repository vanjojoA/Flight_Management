#include "single_center.h"
#include "ui_single_center.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QHeaderView>
#include <QDateTime>
#include <QTableWidgetItem>

Single_Center::Single_Center(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Single_Center)
{
    ui->setupUi(this);
    currentUsername = "";
    initTable();
}

Single_Center::Single_Center(const QString &username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Single_Center)
{
    ui->setupUi(this);
    currentUsername = username;
    initTable();
    loadOrders();
    connect(ui->btn_refresh, &QPushButton::clicked, this, &Single_Center::refreshOrderList);
    connect(ui->btn_back, &QPushButton::clicked, this, &Single_Center::on_btn_back_clicked);
}

Single_Center::~Single_Center()
{
    delete ui;
}
void Single_Center::on_btn_back_clicked()
{
    emit backRequested(); // 发出"返回请求"信号
}
void Single_Center::initTable()
{
    ui->tableWidget_orders->setColumnCount(9);
    QStringList headers;
    headers << "订单号" << "票务类型" << "路线" << "出发时间" << "到达时间" 
            << "数量" << "总价(元)" << "状态" << "操作";
    ui->tableWidget_orders->setHorizontalHeaderLabels(headers);
    ui->tableWidget_orders->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_orders->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_orders->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_orders->verticalHeader()->setVisible(false);
}

int Single_Center::getUserId()
{
    if (currentUsername.isEmpty()) {
        return -1;
    }
    bool ok;
    int userId = currentUsername.toInt(&ok);
    if (ok && userId > 0) {
        return userId;
    }
    return -1;
}

void Single_Center::loadOrders()
{
    int userId = getUserId();
    if (userId == -1) {
        QMessageBox::warning(this, "错误", "获取用户信息失败！");
        return;
    }

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT o.OrderID, o.OrderNo, o.OrderStatus, o.TicketCount, o.TotalPrice, "
                  "o.OrderTime, t.TicketType, t.DepartureCity, t.ArrivalCity, "
                  "t.DepartureTime, t.ArrivalTime "
                  "FROM orders o "
                  "JOIN tickets t ON o.TicketID = t.TicketID "
                  "WHERE o.UserID = ? "
                  "ORDER BY o.OrderTime DESC");
    query.addBindValue(userId);

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询订单失败：" + query.lastError().text());
        return;
    }
    ui->tableWidget_orders->setRowCount(0);
    int row = 0;
    while (query.next()) {
        ui->tableWidget_orders->insertRow(row);

        int orderId = query.value(0).toInt();
        QString orderNo = query.value(1).toString();
        QString status = query.value(2).toString();
        int count = query.value(3).toInt();
        double totalPrice = query.value(4).toDouble();
        QString ticketType = query.value(6).toString();
        QString route = query.value(7).toString() + " → " + query.value(8).toString();
        QDateTime depTime = query.value(9).toDateTime();
        QDateTime arrTime = query.value(10).toDateTime();

        QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");
        QString statusName = status == "Paid" ? "已支付" : (status == "Cancelled" ? "已取消" : "待支付");
        QString statusName;
        //判断订单是否过期，是否支付
        if (status == "Paid") {
            if (arrTime < QDateTime::currentDateTime()) {
                statusName = "已过期";
            } else {
                statusName = "已支付";
            }
        } else if (status == "Cancelled") {
            statusName = "已取消";
        } else {
            if (depTime < QDateTime::currentDateTime()) {
                statusName = "已过期";
            } else {
                statusName = "待支付";
            }
        }

        ui->tableWidget_orders->setItem(row, 0, new QTableWidgetItem(orderNo));
        ui->tableWidget_orders->setItem(row, 1, new QTableWidgetItem(typeName));
        ui->tableWidget_orders->setItem(row, 2, new QTableWidgetItem(route));
        ui->tableWidget_orders->setItem(row, 3, new QTableWidgetItem(depTime.toString("yyyy-MM-dd hh:mm")));
        ui->tableWidget_orders->setItem(row, 4, new QTableWidgetItem(arrTime.toString("yyyy-MM-dd hh:mm")));
        ui->tableWidget_orders->setItem(row, 5, new QTableWidgetItem(QString::number(count)));
        ui->tableWidget_orders->setItem(row, 6, new QTableWidgetItem(QString::number(totalPrice, 'f', 2)));
        ui->tableWidget_orders->setItem(row, 7, new QTableWidgetItem(statusName));

        // 添加取消订单按钮（只有已支付的订单可以取消）
        if (status == "Paid") {
        if (status == "Paid"&&arrTime > QDateTime::currentDateTime()) {
            QPushButton *btnCancel = new QPushButton("取消订单");
            btnCancel->setProperty("orderId", orderId);
            connect(btnCancel, &QPushButton::clicked, this, &Single_Center::onCancelOrder);
            ui->tableWidget_orders->setCellWidget(row, 8, btnCancel);
        } else {
        }  else if(status=="Paid"&&arrTime<QDateTime::currentDateTime()){
            QPushButton *btndelete=new QPushButton("删除订单");
            btndelete->setProperty("orderId",orderId);
            connect(btndelete,&QPushButton::clicked,this,&Single_Center::onDeleteOrder);
            ui->tableWidget_orders->setCellWidget(row,8,btndelete);
        }else {
            ui->tableWidget_orders->setItem(row, 8, new QTableWidgetItem("-"));
        }

        row++;
    }
}

void Single_Center::refreshOrderList()
{
    loadOrders();
}

void Single_Center::onCancelOrder()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int orderId = btn->property("orderId").toInt();

    int ret = QMessageBox::question(this, "确认", "确定要取消这个订单吗？", 
                                     QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        return;
    }

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }

    // 获取订单信息
    QSqlQuery orderQuery;
    orderQuery.prepare("SELECT TicketID, TicketCount FROM orders WHERE OrderID = ?");
    orderQuery.addBindValue(orderId);
    if (!orderQuery.exec() || !orderQuery.next()) {
        QMessageBox::warning(this, "错误", "获取订单信息失败！");
        return;
    }
    int ticketId = orderQuery.value(0).toInt();
    int ticketCount = orderQuery.value(1).toInt();

    // 开始事务
    QSqlDatabase::database().transaction();

    try {
        // 更新订单状态
        QSqlQuery updateOrderQuery;
        updateOrderQuery.prepare("UPDATE orders SET OrderStatus = 'Cancelled' WHERE OrderID = ?");
        updateOrderQuery.addBindValue(orderId);
        if (!updateOrderQuery.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "错误", "取消订单失败：" + updateOrderQuery.lastError().text());
            return;
        }

        // 恢复座位数
        QSqlQuery updateTicketQuery;
        updateTicketQuery.prepare("UPDATE tickets SET AvailableSeats = AvailableSeats + ? WHERE TicketID = ?");
        updateTicketQuery.addBindValue(ticketCount);
        updateTicketQuery.addBindValue(ticketId);
        if (!updateTicketQuery.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "错误", "恢复座位失败：" + updateTicketQuery.lastError().text());
            return;
        }

        // 提交事务
        QSqlDatabase::database().commit();
        QMessageBox::information(this, "成功", "订单已取消！");
        QMessageBox::information(this, "成功", "订单已取消！订单金额已按原路返回！");
        refreshOrderList();
    } catch (...) {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "错误", "取消订单过程中发生错误！");
    }
}
//删除按钮
void Single_Center::onDeleteOrder()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int orderId = btn->property("orderId").toInt();

    int ret = QMessageBox::question(this, "确认", "确定要删除这个订单吗？",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        return;
    }

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }

    // 获取订单信息
    QSqlQuery orderQuery;
    orderQuery.prepare("SELECT TicketID, TicketCount FROM orders WHERE OrderID = ?");
    orderQuery.addBindValue(orderId);
    if (!orderQuery.exec() || !orderQuery.next()) {
        QMessageBox::warning(this, "错误", "获取订单信息失败！");
        return;
    }
    int ticketId = orderQuery.value(0).toInt();
    int ticketCount = orderQuery.value(1).toInt();

    // 开始事务
    QSqlDatabase::database().transaction();

    try {
        // 更新订单状态
        QSqlQuery updateOrderQuery;
        updateOrderQuery.prepare("UPDATE orders SET OrderStatus = 'Cancelled' WHERE OrderID = ?");
        updateOrderQuery.addBindValue(orderId);
        if (!updateOrderQuery.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "错误", "删除订单失败：" + updateOrderQuery.lastError().text());
            return;
        }


        // 提交事务
        QSqlDatabase::database().commit();
        QMessageBox::information(this, "成功", "订单已删除！");
        refreshOrderList();
    } catch (...) {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "错误", "删除订单过程中发生错误！");
    }
}

void Single_Center::onViewOrder()
{
    // 可以在这里添加查看订单详情的功能
}

