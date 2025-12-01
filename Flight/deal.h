#ifndef DEAL_H
#define DEAL_H
#include "userprofile.h"
#include <QWidget>
#include <QString>
#include "single_center.h"
#include "favorite_dialog.h"
// #include <QDialog>
// #include <QModelIndex>
// #include <QStandardItemModel>
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
    void loadFlightDeals();
    void checkFavoriteStatus();

private slots:
    void on_Single_Center_clicked();
    void on_btn_search_clicked();
    void on_btn_reset_clicked();
    void on_Deal_2_clicked();
    void on_favorite_button_clicked();
    void onBookTicket();
    void refreshTicketList();
    void showTicketSearchPage();
    void on_tableView_clicked(const QModelIndex &index);
    void onAddFavorite();
private:
    void initTable();
    void searchTickets();
    QString currentUsername;

    Ui::Deal *ui;
    Single_Center *m_personalCenterPage;
    UserProfile *m_userProfilePage;
    favorite_dialog *m_favoriteDialogPage;
};

#endif // DEAL_H
