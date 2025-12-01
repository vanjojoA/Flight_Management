
#include "deal.h"
#include "ui_deal.h"
#include "single_center.h"
#include "order_dialog.h"
#include "userprofile.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QPushButton>
#include <QHeaderView>
#include <QDateTime>
#include <QTableWidgetItem>
#include "mainwindow.h"
#include "userprofile.h"
Deal::Deal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Deal)
{
    ui->setupUi(this);
    currentUserID = "";
    initTable();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->stackedWidget->setCurrentWidget(ui->page_tickets);
}

Deal::Deal(const QString &userID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Deal)
{
    ui->setupUi(this);
    currentUserID = userID;
    initTable();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    searchTickets();

    m_personalCenterPage = new Single_Center(currentUserID, this);
    ui->stackedWidget->addWidget(m_personalCenterPage);
    connect(m_personalCenterPage, &Single_Center::backRequested, this, &Deal::showTicketSearchPage);

    m_userProfilePage = new UserProfile(currentUsername,this);
    m_userProfilePage = new UserProfile(userID,this);
    ui->stackedWidget->addWidget(m_userProfilePage);
    m_userProfilePage->getData(currentUserID);
    connect(m_userProfilePage, &UserProfile::backRequested, this, &Deal::showTicketSearchPage);

    connect(m_userProfilePage, &UserProfile::myOrdersRequested, this, [=](){
        m_personalCenterPage->refreshOrderList();
        ui->stackedWidget->setCurrentWidget(m_personalCenterPage);
    });


    connect(m_userProfilePage, &UserProfile::logoutRequested, this, [=](){
        MainWindow *loginWindow = new MainWindow();
        loginWindow->show();
        this->close();
    });
    ui->stackedWidget->setCurrentWidget(ui->page_tickets);

}

Deal::~Deal()
{
    delete ui;
}

void Deal::initTable()
{
    QStringList headers;
    headers << "类型" << "编号" << "出发地" << "目的地" << "出发时间" 
            << "到达时间" << "价格(元)" << "可用座位" << "公司" << "操作";
    ui->tableWidget_tickets->setHorizontalHeaderLabels(headers);
    ui->tableWidget_tickets->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_tickets->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_tickets->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_tickets->verticalHeader()->setVisible(false);
}

void Deal::searchTickets()
{
    QString from = ui->lineEdit_from->text().trimmed();
    QString to = ui->lineEdit_to->text().trimmed();
    QDate date = ui->dateEdit->date();
    QString type = ui->comboBox_type->currentText();

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接！");
        return;
    }

    QSqlQuery query;
    QString sql = "SELECT TicketID, TicketType, TicketNo, DepartureCity, ArrivalCity, "
                  "DepartureTime, ArrivalTime, Price, AvailableSeats, Company "
                  "FROM tickets WHERE Status = 'Available' AND AvailableSeats > 0";

    if (!from.isEmpty()) {
        sql += " AND DepartureCity LIKE :from";
    }
    if (!to.isEmpty()) {
        sql += " AND ArrivalCity LIKE :to";
    }
    if (date.isValid()) {
        sql += " AND DATE(DepartureTime) = :date";
    }
    if (type != "全部") {
        if (type == "航班") {
            sql += " AND TicketType = 'Flight'";
        }
    }
    sql += " ORDER BY DepartureTime";

    query.prepare(sql);
    if (!from.isEmpty()) {
        query.bindValue(":from", "%" + from + "%");
    }
    if (!to.isEmpty()) {
        query.bindValue(":to", "%" + to + "%");
    }
    if (date.isValid()) {
        query.bindValue(":date", date.toString("yyyy-MM-dd"));
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询失败：" + query.lastError().text());
        return;
    }

    ui->tableWidget_tickets->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->tableWidget_tickets->insertRow(row);

        int ticketId = query.value(0).toInt();
        QString ticketType = query.value(1).toString();
        QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");

        ui->tableWidget_tickets->setItem(row, 0, new QTableWidgetItem(typeName));
        ui->tableWidget_tickets->setItem(row, 1, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_tickets->setItem(row, 2, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_tickets->setItem(row, 3, new QTableWidgetItem(query.value(4).toString()));
        
        QDateTime depTime = query.value(5).toDateTime();
        QDateTime arrTime = query.value(6).toDateTime();
        ui->tableWidget_tickets->setItem(row, 4, new QTableWidgetItem(depTime.toString("yyyy-MM-dd hh:mm")));
        ui->tableWidget_tickets->setItem(row, 5, new QTableWidgetItem(arrTime.toString("yyyy-MM-dd hh:mm")));
        
        ui->tableWidget_tickets->setItem(row, 6, new QTableWidgetItem(QString::number(query.value(7).toDouble(), 'f', 2)));
        ui->tableWidget_tickets->setItem(row, 7, new QTableWidgetItem(query.value(8).toString()));
        ui->tableWidget_tickets->setItem(row, 8, new QTableWidgetItem(query.value(9).toString()));

        // 添加订票按钮
        QPushButton *btnBook = new QPushButton("订票");
        btnBook->setProperty("ticketId", ticketId);
        connect(btnBook, &QPushButton::clicked, this, &Deal::onBookTicket);
        ui->tableWidget_tickets->setCellWidget(row, 9, btnBook);

        row++;
    }
}

void Deal::on_btn_search_clicked()
{
    searchTickets();
}



void Deal::onBookTicket()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }

    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int ticketId = btn->property("ticketId").toInt();
    
    // 获取当前用户ID
    //QSqlQuery query;
    //query.prepare("SELECT UserID FROM users WHERE Username = ?");
    //query.addBindValue(currentUserID);
    //if (!query.exec() || !query.next()) {
    //    QMessageBox::warning(this, "错误", "获取用户信息失败！");
    //    return;
    //}
    int userId = currentUserID.toInt();

    // 打开订单对话框
    OrderDialog *dialog = new OrderDialog(ticketId, userId, this);
    if (dialog->exec() == QDialog::Accepted) {
        refreshTicketList();
        QMessageBox::information(this, "成功", "订票成功！");
    }
    delete dialog;
}

void Deal::refreshTicketList()
{
    searchTickets();
}

void Deal::on_Single_Center_clicked()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    m_userProfilePage->getData(currentUserID);
    ui->stackedWidget->setCurrentWidget(m_userProfilePage);
    // Single_Center *center = new Single_Center(currentUsername, this);
    // center->setAttribute(Qt::WA_DeleteOnClose);
    // center->show();
}

void Deal::on_Deal_2_clicked()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    m_personalCenterPage->refreshOrderList();
    // 这里可以打开行程页面，暂时使用个人中心
    // Single_Center *center = new Single_Center(currentUsername,this);
    // center->setAttribute(Qt::WA_DeleteOnClose);
    // center->show();
    ui->stackedWidget->setCurrentWidget(m_personalCenterPage);

}
void Deal::showTicketSearchPage()
{
    ui->stackedWidget->setCurrentWidget(ui->page_tickets);
}

