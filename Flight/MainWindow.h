<<<<<<< HEAD
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void usernameSubmitted(const QString &username);
private slots:
    void on_log_in_clicked();
    void on_sign_in_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void usernameSubmitted(const QString &username);
private slots:
    void on_log_in_clicked();
    void on_sign_in_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
>>>>>>> 424bc0a8b89776bc4a6d5328940fb4156ce50bcf
