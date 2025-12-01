#include "deal.h"
#include "ui_deal.h"
#include "single_center.h"
#include "order_dialog.h"
#include "userprofile.h"
#include "favorite_dialog.h"
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

Deal::Deal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Deal)
{
    ui->setupUi(this);
    currentUsername = "";
    initTable();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->stackedWidget->setCurrentWidget(ui->page_tickets);
}

Deal::Deal(const QString &username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Deal)
{
    ui->setupUi(this);
    currentUsername = username;
    initTable();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    searchTickets();

    m_personalCenterPage = new Single_Center(currentUsername, this);
    ui->stackedWidget->addWidget(m_personalCenterPage);
    connect(m_personalCenterPage, &Single_Center::backRequested, this, &Deal::showTicketSearchPage);

    m_userProfilePage = new UserProfile(this);
    ui->stackedWidget->addWidget(m_userProfilePage);

    m_favoriteDialogPage = new favorite_dialog(currentUsername,this);
    ui->stackedWidget->addWidget(m_favoriteDialogPage);

    connect(m_favoriteDialogPage, &favorite_dialog::backRequested, this, &Deal::showTicketSearchPage); // <--- 连接返回信号
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
    connect(m_userProfilePage, &UserProfile::myFavoritesRequested, this, [=](){
        m_favoriteDialogPage->refreshFavoriteList();
        ui->stackedWidget->setCurrentWidget(m_favoriteDialogPage);
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
            << "到达时间" << "价格(元)" << "可用座位" << "公司" << "操作"<<"收藏";
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
    QList<int> favoriteTicketIds;
    if (!currentUsername.isEmpty()) {
        QSqlQuery userQuery;
        userQuery.prepare("SELECT UserID FROM users WHERE Username = :username");
        userQuery.bindValue(":username", currentUsername);
        if (userQuery.exec() && userQuery.next()) {
            int currentUserId = userQuery.value(0).toInt();

            QSqlQuery favQuery;
            favQuery.prepare("SELECT TicketID FROM favorites WHERE UserID = :uid");
            favQuery.bindValue(":uid", currentUserId);
            if (favQuery.exec()) {
                while(favQuery.next()) {
                    favoriteTicketIds.append(favQuery.value(0).toInt());
                }
            }
        }
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

        //添加收藏按钮
        bool isFavorited = favoriteTicketIds.contains(ticketId);
        QPushButton * btnFav = new QPushButton(isFavorited ? "已收藏" : "收藏");

        btnFav->setProperty("ticketId",ticketId);
        btnFav->setEnabled(!isFavorited); // 如果已收藏，按钮设为不可用

        connect(btnFav,&QPushButton::clicked,this,&::Deal::onAddFavorite);
        ui->tableWidget_tickets->setCellWidget(row, 10, btnFav);
        row++;
    }
}

void Deal::on_btn_search_clicked()
{
    searchTickets();
}

void Deal::on_btn_reset_clicked()
{
    ui->lineEdit_from->clear();
    ui->lineEdit_to->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_type->setCurrentIndex(0);
    searchTickets();
}

void Deal::onBookTicket()
{
    if (currentUsername.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }

    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int ticketId = btn->property("ticketId").toInt();
    
    // 获取当前用户ID
    QSqlQuery query;
    query.prepare("SELECT UserID FROM users WHERE Username = ?");
    query.addBindValue(currentUsername);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "错误", "获取用户信息失败！");
        return;
    }
    int userId = query.value(0).toInt();

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
    if (currentUsername.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    ui->stackedWidget->setCurrentWidget(m_userProfilePage);
    // Single_Center *center = new Single_Center(currentUsername, this);
    // center->setAttribute(Qt::WA_DeleteOnClose);
    // center->show();
}

void Deal::on_Deal_2_clicked()
{
    if (currentUsername.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    m_personalCenterPage->refreshOrderList();
    ui->stackedWidget->setCurrentWidget(m_personalCenterPage);

}
void Deal::on_favorite_button_clicked(){
    if (currentUsername.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    m_favoriteDialogPage->refreshFavoriteList();
    ui->stackedWidget->setCurrentWidget(m_favoriteDialogPage);
}
void Deal::showTicketSearchPage()
{
    searchTickets();
    ui->stackedWidget->setCurrentWidget(ui->page_tickets);
}
void Deal::on_tableView_clicked(const QModelIndex &index)
{

}
void Deal::onAddFavorite(){
    if (currentUsername.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    int ticketId = btn->property("ticketId").toInt();

    QSqlQuery query;
    query.prepare("SELECT UserID FROM users WHERE Username = ?");
    query.addBindValue(currentUsername);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "错误", "获取用户信息失败！");
        return;
    }
    int userId = query.value(0).toInt();

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO favorites (UserID, TicketID) VALUES (?, ?)");
    insertQuery.addBindValue(userId);
    insertQuery.addBindValue(ticketId);

    if (insertQuery.exec()) {
        QMessageBox::information(this, "成功", "已添加到收藏夹！");

        btn->setEnabled(false);
        btn->setText("已收藏");
    } else {
        if (insertQuery.lastError().text().contains("Duplicate entry") ||
            insertQuery.lastError().text().contains("UNIQUE")) {
            QMessageBox::information(this, "提示", "您已经收藏过该行程了！");
        } else {
            QMessageBox::critical(this, "错误", "收藏失败：" + insertQuery.lastError().text());
        }
    }
}
