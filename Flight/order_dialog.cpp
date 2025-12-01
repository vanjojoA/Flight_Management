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
//检测时间是否冲突
bool OrderDialog::checkTimeConflict(const QString&passengerIDCard,int newTicketId){
    if(passengerIDCard.isEmpty()){
        return false;
    }
    QSqlQuery newTicketQuery;
    newTicketQuery.prepare("SELECT DepartureTime, ArrivalTime FROM tickets WHERE TicketID = ?");
    newTicketQuery.addBindValue(newTicketId);
    if (!newTicketQuery.exec() || !newTicketQuery.next()) {
        qDebug() << "无法获取新票务信息";
        return false;
    }
    QDateTime newDepTime = newTicketQuery.value(0).toDateTime();
    QDateTime newArrTime = newTicketQuery.value(1).toDateTime();
    //获取这个乘客未出行的订单
    QSqlQuery query;
    query.prepare("SELECT t.DepartureTime, t.ArrivalTime, t.TicketNo, t.DepartureCity, t.ArrivalCity, t.TicketType "
                  "FROM orders o "
                  "JOIN tickets t ON o.TicketID = t.TicketID "
                  "WHERE o.PassengerIDCard = ? AND o.OrderStatus IN ('Pending', 'Confirmed', 'Paid') "
                  "AND t.DepartureTime > ?");
    query.addBindValue(passengerIDCard);
    query.addBindValue(QDateTime::currentDateTime());
    if (!query.exec()) {
        qDebug() << "查询乘客订单失败:" << query.lastError().text();
        return false;
    }
    while (query.next()) {
        QDateTime existingDepTime = query.value(0).toDateTime();
        QDateTime existingArrTime = query.value(1).toDateTime();
        QString ticketNo = query.value(2).toString();
        QString depCity = query.value(3).toString();
        QString arrCity = query.value(4).toString();
        QString ticketType = query.value(5).toString();

        // 时间冲突判断逻辑
        bool timeOverlap = (newDepTime < existingArrTime && newArrTime > existingDepTime);

        if (timeOverlap) {
            qDebug() << "检测到时间冲突: 新票" << newDepTime << "-" << newArrTime
                     << "与已有票" << existingDepTime << "-" << existingArrTime << "重叠";
            return true;
        }

        // 检查换乘时间是否足够（最小30分钟）
        int minTransferTime = 30; // 分钟

        // 新票在已有票之后，检查换乘时间
        if (newDepTime > existingArrTime) {
            qint64 transferSeconds = existingArrTime.secsTo(newDepTime);
            if (transferSeconds < minTransferTime * 60) {
                qDebug() << "换乘时间不足:" << transferSeconds / 60 << "分钟";
                return true;
            }
        }

        // 已有票在新票之后，检查换乘时间
        if (existingDepTime > newArrTime) {
            qint64 transferSeconds = newArrTime.secsTo(existingDepTime);
            if (transferSeconds < minTransferTime * 60) {
                qDebug() << "换乘时间不足:" << transferSeconds / 60 << "分钟";
                return true;
            }
        }
    }
    return false;

}
//获取冲突
QString OrderDialog:: getConflictDetails(const QString &passengerIDCard, int newTicketId)
{
    if (passengerIDCard.isEmpty()) {
        return "";
    }

    // 获取新票信息
    QSqlQuery newTicketQuery;
    newTicketQuery.prepare("SELECT DepartureTime, ArrivalTime FROM tickets WHERE TicketID = ?");
    newTicketQuery.addBindValue(newTicketId);

    if (!newTicketQuery.exec() || !newTicketQuery.next()) {
        return "";
    }

    QDateTime newDepTime = newTicketQuery.value(0).toDateTime();
    QDateTime newArrTime = newTicketQuery.value(1).toDateTime();

    // 查找冲突的行程
    QSqlQuery query;
    query.prepare("SELECT t.TicketNo, t.DepartureCity, t.ArrivalCity, "
                  "t.DepartureTime, t.ArrivalTime, t.TicketType, t.Company "
                  "FROM orders o "
                  "JOIN tickets t ON o.TicketID = t.TicketID "
                  "WHERE o.PassengerIDCard = ? AND o.OrderStatus IN ('Pending', 'Confirmed', 'Paid') "
                  "AND t.DepartureTime > ?");

    query.addBindValue(passengerIDCard);
    query.addBindValue(QDateTime::currentDateTime());

    if (!query.exec()) {
        return "";
    }

    while (query.next()) {
        QDateTime existingDepTime = query.value(3).toDateTime();
        QDateTime existingArrTime = query.value(4).toDateTime();

        // 检查时间冲突
        bool timeOverlap = (newDepTime < existingArrTime && newArrTime > existingDepTime);

        // 检查换乘时间
        bool insufficientTransfer = false;
        if (newDepTime > existingArrTime) {
            qint64 transferSeconds = existingArrTime.secsTo(newDepTime);
            insufficientTransfer = (transferSeconds < 30 * 60);
        } else if (existingDepTime > newArrTime) {
            qint64 transferSeconds = newArrTime.secsTo(existingDepTime);
            insufficientTransfer = (transferSeconds < 30 * 60);
        }

        if (timeOverlap || insufficientTransfer) {
            QString ticketType = query.value(5).toString();
            QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");

            return QString("%1 %2\n%3 → %4\n%5 - %6\n运营商：%7")
                .arg(typeName)
                .arg(query.value(0).toString())
                .arg(query.value(1).toString())
                .arg(query.value(2).toString())
                .arg(existingDepTime.toString("MM-dd hh:mm"))
                .arg(existingArrTime.toString("MM-dd hh:mm"))
                .arg(query.value(6).toString());
        }
    }

    return "";
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
    if (passengerID.length() != 18) {
        QMessageBox::warning(this, "提示", "请输入18位身份证号码！");
        ui->lineEdit_id->setFocus();
        ui->lineEdit_id->selectAll();
        return;
    }
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }
    //行程是否冲突
    if (checkTimeConflict(passengerID, ticketId)) {
        QString conflictDetails = getConflictDetails(passengerID, ticketId);

        QString message = QString("检测到行程时间冲突！\n\n乘客：%1 (身份证：%2)\n\n").arg(passengerName).arg(passengerID);

        if (!conflictDetails.isEmpty()) {
            message += QString("冲突的行程：\n%1\n\n").arg(conflictDetails);
        }

        // 获取当前票务信息
        QSqlQuery ticketQuery;
        ticketQuery.prepare("SELECT TicketNo, DepartureCity, ArrivalCity, DepartureTime, ArrivalTime FROM tickets WHERE TicketID = ?");
        ticketQuery.addBindValue(ticketId);

        if (ticketQuery.exec() && ticketQuery.next()) {
            message += QString("您要预订的行程：\n%1 %2\n%3 → %4\n%5 - %6")
                           .arg(ui->label_type->text())
                           .arg(ticketQuery.value(0).toString())
                           .arg(ticketQuery.value(1).toString())
                           .arg(ticketQuery.value(2).toString())
                           .arg(ticketQuery.value(3).toDateTime().toString("MM-dd hh:mm"))
                           .arg(ticketQuery.value(4).toDateTime().toString("MM-dd hh:mm"));
        }

        QMessageBox::warning(this, "行程冲突", message);
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


