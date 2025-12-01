#ifndef ORDER_DIALOG_H
#define ORDER_DIALOG_H

#include <QDialog>

namespace Ui {
class OrderDialog;
}

class OrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDialog(int ticketId, int userId, QWidget *parent = nullptr);
    ~OrderDialog();

private slots:
    void on_btn_confirm_clicked();
    void on_btn_cancel_clicked();
    void on_spinBox_count_valueChanged(int count);

private:
    void loadTicketInfo();
    void calculateTotal();

    bool checkTimeConflict(const QString &passengerIDCard, int newTicketId);
    QString getConflictDetails(const QString &passengerIDCard, int newTicketId);
    Ui::OrderDialog *ui;
    int ticketId;
    int userId;
    double ticketPrice;
};

#endif // ORDER_DIALOG_H


