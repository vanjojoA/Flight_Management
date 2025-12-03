#ifndef DEAL_H
#define DEAL_H
#include "userprofile.h"
#include <QWidget>
#include <QString>
#include "single_center.h"
namespace Ui {
class Deal;
}

class Deal : public QWidget
{
    Q_OBJECT

public:
    explicit Deal(QWidget *parent = nullptr);
    explicit Deal(const QString &username, QWidget *parent = nullptr);
    ~Deal();

private slots:
    void on_Single_Center_clicked();
    void on_btn_search_clicked();
   // void on_btn_reset_clicked();
    void on_Deal_2_clicked();
    void onBookTicket();
    void refreshTicketList();
    void showTicketSearchPage();
    // void onPrevPage();  // 上一页
    // void onNextPage();  //下一页
private:
    void initTable();
    void searchTickets();

    QString currentUserID;

    Ui::Deal *ui;
    Single_Center *m_personalCenterPage;
    UserProfile *m_userProfilePage;

    int currentPage = 1;    // 当前页码（默认第一页）
    int pageSize = 20;      // 每页显示 20 条（可调整）
    int totalCount = 0;     // 总数据条数（用于计算总页数）
};

#endif // DEAL_H
