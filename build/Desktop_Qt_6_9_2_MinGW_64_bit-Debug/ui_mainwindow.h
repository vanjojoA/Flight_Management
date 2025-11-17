/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *log_in;
    QPushButton *sign_in;
    QLabel *Username;
    QLabel *Password;
    QLineEdit *Usernamet;
    QLineEdit *Passwordt;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        log_in = new QPushButton(centralwidget);
        log_in->setObjectName("log_in");
        log_in->setEnabled(true);
        log_in->setGeometry(QRect(240, 370, 99, 28));
        sign_in = new QPushButton(centralwidget);
        sign_in->setObjectName("sign_in");
        sign_in->setGeometry(QRect(400, 370, 99, 28));
        Username = new QLabel(centralwidget);
        Username->setObjectName("Username");
        Username->setGeometry(QRect(250, 200, 69, 19));
        Password = new QLabel(centralwidget);
        Password->setObjectName("Password");
        Password->setGeometry(QRect(260, 240, 69, 19));
        Usernamet = new QLineEdit(centralwidget);
        Usernamet->setObjectName("Usernamet");
        Usernamet->setGeometry(QRect(320, 190, 171, 27));
        Usernamet->setFrame(false);
        Usernamet->setEchoMode(QLineEdit::EchoMode::Normal);
        Usernamet->setDragEnabled(true);
        Usernamet->setReadOnly(false);
        Usernamet->setCursorMoveStyle(Qt::CursorMoveStyle::LogicalMoveStyle);
        Usernamet->setClearButtonEnabled(false);
        Passwordt = new QLineEdit(centralwidget);
        Passwordt->setObjectName("Passwordt");
        Passwordt->setGeometry(QRect(320, 240, 171, 27));
        Passwordt->setEchoMode(QLineEdit::EchoMode::Password);
        Passwordt->setDragEnabled(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        log_in->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        sign_in->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        Username->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        Password->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        Usernamet->setInputMask(QString());
        Usernamet->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215...", nullptr));
        Passwordt->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201...", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
