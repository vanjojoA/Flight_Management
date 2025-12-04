#include "favorite_dialog.h"
#include "ui_favorite_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QHeaderView>
#include <QDateTime>
#include <QTableWidgetItem>

favorite_dialog::favorite_dialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::favorite_dialog)
{
    ui->setupUi(this);
}

favorite_dialog::favorite_dialog(const QString &userID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::favorite_dialog)
    , currentUserID(userID)
{
    ui->setupUi(this);
    initTable();
    loadFavorites(); // 构造时加载数据
}

favorite_dialog::~favorite_dialog()
{
    delete ui;
}

void favorite_dialog::initTable()
{
    QStringList headers;
    headers << "类型" << "编号" << "出发地" << "目的地"
            << "出发时间" << "到达时间" << "价格（元）" << "公司" <<"收藏";
    ui->tableWidget_favorites->setHorizontalHeaderLabels(headers);
    ui->tableWidget_favorites->setColumnCount(headers.size());
    ui->tableWidget_favorites->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_favorites->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_favorites->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_favorites->verticalHeader()->setVisible(false);
}

void favorite_dialog::loadFavorites()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "未登录用户，无法加载收藏！");
        return;
    }

    // 清空现有表格
    ui->tableWidget_favorites->setRowCount(0);

    // 查询收藏夹内容
    QSqlQuery query;
    QString sql = "SELECT t.TicketID, t.TicketType, t.TicketNo, t.DepartureCity, t.ArrivalCity, "
                  "t.DepartureTime, t.ArrivalTime, t.Price, t.Company "
                  "FROM favorites f JOIN tickets t ON f.TicketID = t.TicketID "
                  "WHERE f.UserID = :userId";
    sql += " ORDER BY t.DepartureTime DESC";

    query.prepare(sql);
    query.bindValue(":userId", currentUserID);

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询收藏列表失败：" + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tableWidget_favorites->insertRow(row);

        int ticketId = query.value(0).toInt();
        QString ticketType = query.value(1).toString();
        QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");

        ui->tableWidget_favorites->setItem(row, 0, new QTableWidgetItem(typeName));
        ui->tableWidget_favorites->setItem(row, 1, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_favorites->setItem(row, 2, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_favorites->setItem(row, 3, new QTableWidgetItem(query.value(4).toString()));
        QDateTime depTime = query.value(5).toDateTime();
        ui->tableWidget_favorites->setItem(row, 4, new QTableWidgetItem(depTime.toString("yyyy-MM-dd hh:mm")));
        QDateTime arrTime = query.value(6).toDateTime();
        ui->tableWidget_favorites->setItem(row, 5, new QTableWidgetItem(arrTime.toString("yyyy-MM-dd hh:mm")));
        ui->tableWidget_favorites->setItem(row, 6, new QTableWidgetItem(QString::number(query.value(7).toDouble(), 'f', 2)));
        ui->tableWidget_favorites->setItem(row, 7, new QTableWidgetItem(query.value(8).toString()));

        // 添加移除按钮
        QPushButton *btnRemove = new QPushButton("移除");
        btnRemove->setProperty("ticketId", ticketId);
        connect(btnRemove, &QPushButton::clicked, this, &favorite_dialog::onRemoveFavorite);
        ui->tableWidget_favorites->setCellWidget(row,8, btnRemove);

        row++;
    }
}

void favorite_dialog::refreshFavoriteList()
{
    loadFavorites();
}

void favorite_dialog::on_btn_back_clicked()
{
    emit backRequested();
}

void favorite_dialog::on_btn_refresh_clicked()
{
    refreshFavoriteList();
}


void favorite_dialog::onRemoveFavorite()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int ticketId = btn->property("ticketId").toInt();

    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "错误", "未登录用户！");
        return;
    }

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM favorites WHERE UserID = :userId AND TicketID = :ticketId");
    removeQuery.bindValue(":userId", currentUserID);

    removeQuery.bindValue(":ticketId", ticketId);

    if (removeQuery.exec()) {
        QMessageBox::information(this, "成功", "已从收藏夹移除！");


        refreshFavoriteList(); // 刷新列表以移除该行
    } else {
        QMessageBox::critical(this, "错误", "移除失败：" + removeQuery.lastError().text());
    }
}


void favorite_dialog::on_searchBtn_clicked()
{
    if (currentUserID.isEmpty()) {
        return;
    }
    QString depCity = ui->lineEdit_dep->text().trimmed();     // 出发地
    QString arrCity = ui->lineEdit_arr->text().trimmed();     // 目的地
    QDate startDate = ui->dateEdit_begin->date();             // 开始日期
    QDate endDate = ui->dateEdit_end->date();                 // 结束日期
    QString type = ui->comboBox_type->currentText();          // 交通类型

    QString sql = "SELECT t.TicketID, t.TicketType, t.TicketNo, t.DepartureCity, t.ArrivalCity, "
                  "t.DepartureTime, t.ArrivalTime, t.Price, t.Company "
                  "FROM favorites f JOIN tickets t ON f.TicketID = t.TicketID "
                  "WHERE f.UserID = :userId";

    if (!depCity.isEmpty()) {
        sql += " AND t.DepartureCity LIKE :depCity";
    }
    if (!arrCity.isEmpty()) {
        sql += " AND t.ArrivalCity LIKE :arrCity";
    }

    sql += " AND DATE(t.DepartureTime) >= :startDate";
    sql += " AND DATE(t.DepartureTime) <= :endDate";
    if (type != "全部") {
        if (type == "飞机") sql += " AND t.TicketType = 'Flight'";
        else if (type == "火车") sql += " AND t.TicketType = 'Train'";
        else if (type == "汽车") sql += " AND t.TicketType = 'Bus'";
    }

    sql += " ORDER BY t.DepartureTime DESC"; // 排序
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":userId", currentUserID);
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);

    if (!depCity.isEmpty()) {
        query.bindValue(":depCity", "%" + depCity + "%"); // 模糊查询
    }
    if (!arrCity.isEmpty()) {
        query.bindValue(":arrCity", "%" + arrCity + "%"); // 模糊查询
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "搜索失败：" + query.lastError().text());
        return;
    }

    ui->tableWidget_favorites->setRowCount(0); // 清空旧数据

    int row = 0;
    while (query.next()) {
        ui->tableWidget_favorites->insertRow(row);

        int ticketId = query.value(0).toInt();

        QString ticketType = query.value(1).toString();
        QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");

        ui->tableWidget_favorites->setItem(row, 0, new QTableWidgetItem(typeName));

        ui->tableWidget_favorites->setItem(row, 1, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_favorites->setItem(row, 2, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_favorites->setItem(row, 3, new QTableWidgetItem(query.value(4).toString()));
        QDateTime depTime = query.value(5).toDateTime();
        ui->tableWidget_favorites->setItem(row, 4, new QTableWidgetItem(depTime.toString("yyyy-MM-dd hh:mm")));
        QDateTime arrTime = query.value(6).toDateTime();
        ui->tableWidget_favorites->setItem(row, 5, new QTableWidgetItem(arrTime.toString("yyyy-MM-dd hh:mm")));
        ui->tableWidget_favorites->setItem(row, 6, new QTableWidgetItem(QString::number(query.value(7).toDouble(), 'f', 2)));
        ui->tableWidget_favorites->setItem(row, 7, new QTableWidgetItem(query.value(8).toString()));

        QPushButton *btnRemove = new QPushButton("移除");
        btnRemove->setProperty("ticketId", ticketId);
        connect(btnRemove, &QPushButton::clicked, this, &favorite_dialog::onRemoveFavorite);
        ui->tableWidget_favorites->setCellWidget(row, 8, btnRemove);
        row++;
    }

    if (row == 0) {
        QMessageBox::information(this, "提示", "未找到符合条件的收藏记录。");
    }
}
