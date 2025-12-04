#include "order_dialog.h"
#include "ui_order_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>

OrderDialog::~OrderDialog()
{
    delete ui;
}

OrderDialog::OrderDialog(int ticketId, int userId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OrderDialog)
    , ticketId(ticketId)
    , userId(userId)
    , ticketPrice(0.0)
    , userBalance(0.0)
{
    ui->setupUi(this);
    setWindowTitle("填写订单信息");
    setModal(true);
    loadTicketInfo();
    loadUserBalance();
    ui->spinBox_count->setMinimum(1);
    ui->spinBox_count->setMaximum(10);
    ui->spinBox_count->setValue(1);
}

void OrderDialog::loadTicketInfo()
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT flight_id, flight_number, departure_city, arrival_city, departure_time, "
                  "arrival_time, price, departure_airport, arrival_airport, airline_company "
                  "FROM flight_Info WHERE flight_id = ?");
    query.addBindValue(ticketId);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "错误", "获取票务信息失败！");
        reject();
        return;
    }


    //暂时保留此处类型，默认为航班
    QString typeName ="航班";
    // QString ticketType = query.value(0).toString();
    // QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");

    ui->label_type->setText(typeName);
    ui->label_ticketNo->setText(query.value(1).toString());
    ui->label_route->setText(query.value(2).toString() + " → " + query.value(3).toString());

    QDateTime depTime = query.value(4).toDateTime();
    QDateTime arrTime = query.value(5).toDateTime();
    ui->label_departure->setText(depTime.toString("yyyy-MM-dd hh:mm"));
    ui->label_arrival->setText(arrTime.toString("yyyy-MM-dd hh:mm"));

    ticketPrice = query.value(6).toDouble();
    ui->label_price->setText(QString::number(ticketPrice, 'f', 2) + " 元");

    //预留修改可用座位
    ui->label_available->setText(QString::number(/*query.value(7).toInt()*/200) + " 张");
    ui->label_company->setText(query.value(9).toString());

    //预留修改可用座位
    ui->spinBox_count->setMaximum(/*query.value(7).toInt()*/200);
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
    if(ui->label_balance){
        if(userBalance<total){
            ui->label_balance->setStyleSheet("color: red; font-weight: bold;");
        }else{
            ui->label_balance->setStyleSheet("color: green; font-weight: bold;");
        }
    }
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
    //检测金额是否超出余额
    loadUserBalance();
    double TotalCost=ticketPrice*count;
    if(TotalCost>userBalance){
        QMessageBox::critical(this, "支付失败",
                              QString("您的余额不足！\n当前余额: ¥%1\n订单金额: ¥%2\n请先充值。")
                                  .arg(QString::number(userBalance, 'f', 2))
                                  .arg(QString::number(TotalCost, 'f', 2)));
        return;
    }
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

        QString message = QString("检测到行程时间冲突！\n\n乘客：%1 (身份证：%2)\n\n").arg(passengerName,passengerID);

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
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery checkQuery(db);
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
    db.transaction();

    try {
        // 插入订单
        QSqlQuery insertQuery(db);
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
            db.rollback();
            QMessageBox::critical(this, "错误", "创建订单失败：" + insertQuery.lastError().text());
            return;
        }

        // 更新票务可用座位数
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE tickets SET AvailableSeats = AvailableSeats - ? WHERE TicketID = ?");
        updateQuery.addBindValue(count);
        updateQuery.addBindValue(ticketId);

        if (!updateQuery.exec()) {
            db.rollback();
            QMessageBox::critical(this, "错误", "更新座位失败：" + updateQuery.lastError().text());
            return;
        }

        QSqlQuery deductQuery(db);
        deductQuery.prepare("UPDATE users SET Balance = Balance - ? WHERE UserID = ?");
        deductQuery.addBindValue(TotalCost);
        deductQuery.addBindValue(userId);
        if (!deductQuery.exec()) {
            throw deductQuery.lastError(); // 抛出异常触发回滚
        }

        // 提交事务
        db.commit();
        QMessageBox::information(this, "成功", QString("订单创建成功！\n订单号：%1").arg(orderNo));
        accept();
    } catch (...) {
        db.rollback();
        QMessageBox::critical(this, "错误", "订票过程中发生错误！");
    }
}

void OrderDialog::on_btn_cancel_clicked()
{
    reject();
}
void OrderDialog::loadUserBalance()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return;

    QSqlQuery query;
    query.prepare("SELECT Balance FROM users WHERE UserID = ?");
    query.addBindValue(userId);

    if (query.exec() && query.next()) {
        userBalance = query.value(0).toDouble();
        if (ui->label_balance) {
            ui->label_balance->setText(QString("当前余额: ¥ %1").arg(QString::number(userBalance, 'f', 2)));
            double currentTotal = ticketPrice * ui->spinBox_count->value();
            if (userBalance < currentTotal) {
                ui->label_balance->setStyleSheet("color: red; font-weight: bold;");
            } else {
                ui->label_balance->setStyleSheet("color: green; font-weight: bold;");
            }
        }
    } else {
        qDebug() << "查询余额失败:" << query.lastError().text();
    }
}
