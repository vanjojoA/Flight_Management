<<<<<<< HEAD
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
private:
    void initTable();
    void searchTickets();
    QString currentUserID;

    Ui::Deal *ui;
    Single_Center *m_personalCenterPage;
    UserProfile *m_userProfilePage;
};

#endif // DEAL_H
=======
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
private:
    void initTable();
    void searchTickets();
    QString currentUserID;

    Ui::Deal *ui;
    Single_Center *m_personalCenterPage;
    UserProfile *m_userProfilePage;
};

#endif // DEAL_H
>>>>>>> 424bc0a8b89776bc4a6d5328940fb4156ce50bcf
