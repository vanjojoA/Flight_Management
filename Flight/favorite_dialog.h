#ifndef FAVORITE_DIALOG_H
#define FAVORITE_DIALOG_H

#include <QWidget>

namespace Ui {
class favorite_dialog;
}

class favorite_dialog : public QWidget
{
    Q_OBJECT

public:
    explicit favorite_dialog(QWidget *parent = nullptr);
    explicit favorite_dialog(const QString &userID, QWidget *parent = nullptr);

    ~favorite_dialog();
    void refreshFavoriteList();

signals:
    void backRequested();

private slots:
    void on_btn_back_clicked();
    void on_btn_refresh_clicked();
    void on_searchBtn_clicked();
    void onRemoveFavorite();

private:
    Ui::favorite_dialog *ui;

    QString currentUserID;

    QString currentUsername;

    void initTable();
    void loadFavorites();
};

#endif // FAVORITE_DIALOG_H
