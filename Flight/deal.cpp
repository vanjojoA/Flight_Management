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

    //initDatabase();
    // searchTickets();
    // testFlightInfoQuery();
    m_personalCenterPage = new Single_Center(currentUserID, this);
    ui->stackedWidget->addWidget(m_personalCenterPage);
    connect(m_personalCenterPage, &Single_Center::backRequested, this, &Deal::showTicketSearchPage);

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
    searchTickets();
}

Deal::~Deal()
{
    delete ui;
}

//预留flightdb
// void Deal::initDatabase(){
//     QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
//     db.setDatabaseName("flight");
//     db.setHostName("127.0.0.1");
//     db.setPort(3306);

//     if(!db.open()){
//         QMessageBox::critical(this,"数据库错误","连接失败" +db.lastError().text());
//     }
//     else
//         qDebug<<"数据库连接成功！";
// }


void Deal::initTable()
{
    QStringList headers;
    headers << "编号" << "出发地" << "目的地" << "出发时间"
            << "到达时间" << "价格(元)" << "可用座位" << "公司" << "操作";
    ui->tableWidget_tickets->setColumnCount(headers.size());
    ui->tableWidget_tickets->setHorizontalHeaderLabels(headers);
    ui->tableWidget_tickets->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 关键列手动调整宽度（避免文字截断）
    ui->tableWidget_tickets->setColumnWidth(3, 150);  // 出发时间
    ui->tableWidget_tickets->setColumnWidth(4, 150);  // 到达时间
    ui->tableWidget_tickets->setColumnWidth(8, 80);  // 操作列

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

    // 检查数据库连接（保持不变）
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid()) {
        QMessageBox::warning(this, "错误", "数据库连接未初始化！");
        return;
    }
    if (!db.isOpen()) {
        if (!db.open()) {
            QMessageBox::warning(this, "错误", "数据库连接失败：" + db.lastError().text());
            return;
        }
    }

    QString startTime = date.toString("yyyy-MM-dd 00:00:00");

    QString sql = "SELECT flight_id, flight_number, departure_city, arrival_city, departure_time, arrival_time, "  // 简化：查询所有字段，无需手动列写
                  "price, departure_airport, arrival_airport, airline_company "
                  "FROM flight_info WHERE status = 'On Time' "
                  "AND departure_time >= :start_time ";
                  /*"AND AvailableSeats > 0 "*/

    // 动态添加条件（保持不变，但确保空格正确）
    if (!from.isEmpty()) {
        sql += "AND departure_city LIKE :from ";
    }
    if (!to.isEmpty()) {
        sql += "AND arrival_city LIKE :to ";
    }
    sql += "ORDER BY departure_time ASC";


    QSqlQuery query(db);
    query.setForwardOnly(true);  // 优化性能，避免结果集缓存问题
    query.setNumericalPrecisionPolicy(QSql::LowPrecisionInt32);

    if (!query.prepare(sql)) {
        QMessageBox::critical(this, "查询错误", "SQL 预处理失败：" + query.lastError().text());
        return;
    }

    // 3. 关键修复：绑定参数时显式指定参数类型（ODBC 驱动兼容）
    query.bindValue(":start_time", startTime);
    if (!from.isEmpty()) {
        query.bindValue(":from", "%" + from + "%");
    }
    if (!to.isEmpty()) {
        query.bindValue(":to", "%" + to + "%");
    }


    // 调试输出（验证参数格式）
    qDebug() << "执行SQL：" << sql;
    qDebug() << "时间参数：" << startTime;
    qDebug() << "查询参数：" << query.boundValues();


    // 5. 执行查询（添加错误详情调试）
    if (!query.exec()) {
        QMessageBox::critical(this, "查询错误",
            "SQL执行失败：" + query.lastError().text() + "\n"
            "原生错误码：" + query.lastError().nativeErrorCode() + "\n"
            "预处理后的SQL：" + query.lastQuery());
        return;
    }

    query.seek(-1);
    ui->tableWidget_tickets->setRowCount(0);
    int row = 0;

    while (query.next()) {
        ui->tableWidget_tickets->insertRow(row);

        int ticketId = query.value("flight_id").toInt();
        QString testSeatNumber="200";


        // 设置表格数据（列索引与表头对应）
        ui->tableWidget_tickets->setItem(row, 0, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_tickets->setItem(row, 1, new QTableWidgetItem(query.value(2).toString() + "-" + query.value(7).toString()));
        ui->tableWidget_tickets->setItem(row, 2, new QTableWidgetItem(query.value(3).toString() + "-" + query.value(8).toString()));

        // 日期时间格式化（确保显示正确）
        QDateTime depTime = query.value(4).toDateTime();
        QDateTime arrTime = query.value(5).toDateTime();
        ui->tableWidget_tickets->setItem(row, 3, new QTableWidgetItem(depTime.toString("yyyy-MM-dd HH:mm")));
        ui->tableWidget_tickets->setItem(row, 4, new QTableWidgetItem(arrTime.toString("yyyy-MM-dd HH:mm")));

        // 价格保留2位小数
        ui->tableWidget_tickets->setItem(row, 5, new QTableWidgetItem(QString::number(query.value(6).toDouble(), 'f', 2)));

        // 可用座位数
        ui->tableWidget_tickets->setItem(row, 6, new QTableWidgetItem(/*query.value(9).toString()*/testSeatNumber));
        // 公司名称
        ui->tableWidget_tickets->setItem(row, 7, new QTableWidgetItem(query.value(9).toString()));

        // 添加订票按钮
        QPushButton *btnBook = new QPushButton("订票");
        btnBook->setStyleSheet("background-color:#4CAF50; color:white; border:none; padding:5px; border-radius:3px;");
        btnBook->setProperty("ticketId", ticketId);
        connect(btnBook, &QPushButton::clicked, this, &Deal::onBookTicket);
        ui->tableWidget_tickets->setCellWidget(row, 8, btnBook);

        row++;
    }

    // 8. 调整表格列宽，优化显示
    ui->tableWidget_tickets->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget_tickets->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
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
