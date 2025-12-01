#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QWidget>

namespace Ui {
class Sign_in;
}

class Sign_in : public QWidget
{
    Q_OBJECT

public:
    explicit Sign_in(QWidget *parent = nullptr);
    ~Sign_in();

private slots:
    void on_Sign_in_Button_clicked();

    void on_Sign_in_Cencel_clicked();

private:
    Ui::Sign_in *ui;
};

#endif // SIGN_IN_H
