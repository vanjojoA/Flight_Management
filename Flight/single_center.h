#ifndef SINGLE_CENTER_H
#define SINGLE_CENTER_H

#include <QWidget>
#include <QString>

namespace Ui {
class Single_Center;
}

class Single_Center : public QWidget
{
    Q_OBJECT

public:
    explicit Single_Center(QWidget *parent = nullptr);
    explicit Single_Center(const QString &username, QWidget *parent = nullptr);
    ~Single_Center();
    void refreshOrderList();
signals:
    void backRequested();
private slots:

    void onCancelOrder();
    void onDeleteOrder();
    void onViewOrder();
    void on_btn_back_clicked();
private:
    void initTable();
    void loadOrders();
    QString currentUsername;
    int getUserId();

    Ui::Single_Center *ui;
};

#endif // SINGLE_CENTER_H
