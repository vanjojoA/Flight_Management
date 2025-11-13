#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QDialog>

namespace Ui {
class MainInterface;
}

class MainInterface : public QDialog
{
    Q_OBJECT

public:
    explicit MainInterface(QWidget *parent = nullptr);
    ~MainInterface();

private:
    Ui::MainInterface *ui;
};

#endif // MAININTERFACE_H
