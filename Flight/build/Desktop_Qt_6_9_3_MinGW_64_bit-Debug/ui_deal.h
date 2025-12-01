/********************************************************************************
** Form generated from reading UI file 'deal.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEAL_H
#define UI_DEAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Deal
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page_tickets;
    QGroupBox *searchGroup;
    QLabel *label_from;
    QLineEdit *lineEdit_from;
    QLabel *label_to;
    QLineEdit *lineEdit_to;
    QLabel *label_date;
    QDateEdit *dateEdit;
    QLabel *label_type;
    QComboBox *comboBox_type;
    QPushButton *btn_search;
    QTableWidget *tableWidget_tickets;
    QPushButton *home;
    QPushButton *Deal_2;
    QPushButton *Single_Center;
    QPushButton *favorite_button;

    void setupUi(QWidget *Deal)
    {
        if (Deal->objectName().isEmpty())
            Deal->setObjectName("Deal");
        Deal->resize(1000, 700);
        stackedWidget = new QStackedWidget(Deal);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1001, 701));
        stackedWidget->setAutoFillBackground(true);
        page_tickets = new QWidget();
        page_tickets->setObjectName("page_tickets");
        page_tickets->setEnabled(true);
        searchGroup = new QGroupBox(page_tickets);
        searchGroup->setObjectName("searchGroup");
        searchGroup->setGeometry(QRect(10, 10, 981, 71));
        searchGroup->setAutoFillBackground(false);
        searchGroup->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 59, 59);\n"
"color: white;\n"
"border-radius: 6px"));
        label_from = new QLabel(searchGroup);
        label_from->setObjectName("label_from");
        label_from->setGeometry(QRect(20, 30, 60, 20));
        label_from->setStyleSheet(QString::fromUtf8("color: white;"));
        lineEdit_from = new QLineEdit(searchGroup);
        lineEdit_from->setObjectName("lineEdit_from");
        lineEdit_from->setGeometry(QRect(90, 28, 120, 25));
        lineEdit_from->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    border-bottom: 2px solid #606060;\n"
"    border-radius: 6px 6px 0px 0px;\n"
"    box-shadow: inset 2px 2px 5px #484848, \n"
"                inset -2px -2px 5px #787878;\n"
"    padding: 4px 12px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-bottom: 2px solid #0078d7;\n"
"    background-color: #646464;\n"
"}"));
        label_to = new QLabel(searchGroup);
        label_to->setObjectName("label_to");
        label_to->setGeometry(QRect(230, 30, 60, 20));
        label_to->setStyleSheet(QString::fromUtf8("color: white;"));
        lineEdit_to = new QLineEdit(searchGroup);
        lineEdit_to->setObjectName("lineEdit_to");
        lineEdit_to->setGeometry(QRect(300, 28, 120, 25));
        lineEdit_to->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    border-bottom: 2px solid #606060;\n"
"    border-radius: 6px 6px 0px 0px;\n"
"    box-shadow: inset 2px 2px 5px #484848, \n"
"                inset -2px -2px 5px #787878;\n"
"    padding: 4px 12px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-bottom: 2px solid #0078d7;\n"
"    background-color: #646464;\n"
"}"));
        label_date = new QLabel(searchGroup);
        label_date->setObjectName("label_date");
        label_date->setGeometry(QRect(440, 30, 60, 20));
        label_date->setStyleSheet(QString::fromUtf8("color: white;"));
        dateEdit = new QDateEdit(searchGroup);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(490, 20, 141, 33));
        dateEdit->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 4px 25px 4px 8px;\n"
"    color: white;\n"
"    font-size: 13px;\n"
"    min-height: 25px;\n"
"    box-shadow: inset 2px 2px 5px #484848, \n"
"                inset -2px -2px 5px #787878;\n"
"}\n"
"\n"
"QDateEdit:focus {\n"
"    background-color: #646464;\n"
"    box-shadow: inset 2px 2px 5px #404040, \n"
"                inset -2px -2px 5px #787878;\n"
"}"));
        dateEdit->setCalendarPopup(true);
        label_type = new QLabel(searchGroup);
        label_type->setObjectName("label_type");
        label_type->setGeometry(QRect(650, 30, 60, 20));
        label_type->setStyleSheet(QString::fromUtf8("color: white;"));
        comboBox_type = new QComboBox(searchGroup);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName("comboBox_type");
        comboBox_type->setGeometry(QRect(700, 20, 131, 33));
        comboBox_type->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 4px 25px 4px 8px;\n"
"    color: white;\n"
"    font-size: 13px;\n"
"    min-height: 25px;\n"
"    box-shadow: inset 2px 2px 5px #484848, \n"
"                inset -2px -2px 5px #787878;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    background-color: #646464;\n"
"}"));
        btn_search = new QPushButton(searchGroup);
        btn_search->setObjectName("btn_search");
        btn_search->setGeometry(QRect(880, 20, 80, 30));
        btn_search->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 13px;\n"
"    box-shadow: inset 2px 2px 4px #484848, \n"
"                inset -2px -2px 4px #787878;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #646464;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #5c5c5c;\n"
"    box-shadow: inset 3px 3px 6px #404040, \n"
"                inset -3px -3px 6px #787878;\n"
"}"));
        tableWidget_tickets = new QTableWidget(page_tickets);
        if (tableWidget_tickets->columnCount() < 11)
            tableWidget_tickets->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        tableWidget_tickets->setObjectName("tableWidget_tickets");
        tableWidget_tickets->setGeometry(QRect(10, 80, 981, 541));
        tableWidget_tickets->setAutoFillBackground(false);
        tableWidget_tickets->setStyleSheet(QString::fromUtf8("QTableView {\n"
"    background-color: rgb(45, 45, 45);\n"
"    color: #ffffff;            \n"
"    gridline-color:#444444;   \n"
"    border: none;           \n"
"    selection-background-color: #555555; \n"
"    selection-color: #ffffff;           \n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: rgb(255, 255, 255);  \n"
"    color: rgb(0, 0, 0);         \n"
"    padding: 3px;               \n"
"    border: none;             \n"
"    border-right: 1px solid #333333; \n"
"    border-bottom: 1px solid #333333; \n"
"    font-weight: bold;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QTableCornerButton::section {\n"
"    background-color: rgb(255, 255, 255);\n"
"    border: none;\n"
"}\n"
"QTableView QPushButton {\n"
"    background-color: rgb(255, 255, 255); /* \350\203\214\346\231\257\350\256\276\347\275\256\344\270\272\347\231\275\350\211\262 */\n"
"    color: rgb(0, 0, 0);                  /* \345\255\227\344\275\223\350\256\276\347\275\256\344\270\272\351\273\221\350\211\262 (\351\230\262\346\255\242"
                        "\347\231\275\345\255\227\347\231\275\345\272\225\347\234\213\344\270\215\350\247\201) */\n"
"    border: 1px solid #cccccc;            /* \345\217\257\351\200\211\357\274\232\345\212\240\344\270\200\344\270\252\346\265\205\347\201\260\350\211\262\350\276\271\346\241\206\350\256\251\346\214\211\351\222\256\346\233\264\346\230\216\346\230\276 */\n"
"    border-radius: 4px;                   /* \345\217\257\351\200\211\357\274\232\345\234\206\350\247\222 */\n"
"    padding: 2px 8px;                     /* \345\217\257\351\200\211\357\274\232\345\206\205\350\276\271\350\267\235 */\n"
"}"));
        tableWidget_tickets->setFrameShadow(QFrame::Shadow::Sunken);
        tableWidget_tickets->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableWidget_tickets->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        home = new QPushButton(page_tickets);
        home->setObjectName("home");
        home->setGeometry(QRect(10, 620, 251, 71));
        home->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border:1px solid white;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    box-shadow: inset 2px 2px 4px #484848, \n"
"                inset -2px -2px 4px #787878;\n"
"	border-radius: 6px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #646464;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #5c5c5c;\n"
"    box-shadow: inset 3px 3px 6px #404040, \n"
"                inset -3px -3px 6px #787878;\n"
"}"));
        Deal_2 = new QPushButton(page_tickets);
        Deal_2->setObjectName("Deal_2");
        Deal_2->setGeometry(QRect(260, 620, 251, 71));
        Deal_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border:1px solid white;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    box-shadow: inset 2px 2px 4px #484848, \n"
"                inset -2px -2px 4px #787878;\n"
"	border-radius: 6px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #646464;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #5c5c5c;\n"
"    box-shadow: inset 3px 3px 6px #404040, \n"
"                inset -3px -3px 6px #787878;\n"
"}"));
        Single_Center = new QPushButton(page_tickets);
        Single_Center->setObjectName("Single_Center");
        Single_Center->setGeometry(QRect(750, 620, 241, 71));
        Single_Center->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border: 1px solid white;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    box-shadow: inset 2px 2px 4px #484848, \n"
"                inset -2px -2px 4px #787878;\n"
"	border-radius: 6px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #646464;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #5c5c5c;\n"
"    box-shadow: inset 3px 3px 6px #404040, \n"
"                inset -3px -3px 6px #787878;\n"
"}"));
        favorite_button = new QPushButton(page_tickets);
        favorite_button->setObjectName("favorite_button");
        favorite_button->setGeometry(QRect(510, 620, 241, 71));
        favorite_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border:1px solid white;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    box-shadow: inset 2px 2px 4px #484848, \n"
"                inset -2px -2px 4px #787878;\n"
"	border-radius: 6px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #646464;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #5c5c5c;\n"
"    box-shadow: inset 3px 3px 6px #404040, \n"
"                inset -3px -3px 6px #787878;\n"
"}"));
        stackedWidget->addWidget(page_tickets);

        retranslateUi(Deal);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Deal);
    } // setupUi

    void retranslateUi(QWidget *Deal)
    {
        Deal->setWindowTitle(QCoreApplication::translate("Deal", "\350\256\242\347\245\250\347\263\273\347\273\237", nullptr));
        searchGroup->setTitle(QCoreApplication::translate("Deal", "\346\220\234\347\264\242\347\245\250\345\212\241", nullptr));
        label_from->setText(QCoreApplication::translate("Deal", "\345\207\272\345\217\221\345\234\260\357\274\232", nullptr));
        lineEdit_from->setPlaceholderText(QCoreApplication::translate("Deal", "\344\276\213\345\246\202\357\274\232\345\214\227\344\272\254", nullptr));
        label_to->setText(QCoreApplication::translate("Deal", "\347\233\256\347\232\204\345\234\260\357\274\232", nullptr));
        lineEdit_to->setPlaceholderText(QCoreApplication::translate("Deal", "\344\276\213\345\246\202\357\274\232\344\270\212\346\265\267", nullptr));
        label_date->setText(QCoreApplication::translate("Deal", "\346\227\245\346\234\237\357\274\232", nullptr));
        label_type->setText(QCoreApplication::translate("Deal", "\347\261\273\345\236\213\357\274\232", nullptr));
        comboBox_type->setItemText(0, QCoreApplication::translate("Deal", "\345\205\250\351\203\250", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("Deal", "\350\210\252\347\217\255", nullptr));
        comboBox_type->setItemText(2, QCoreApplication::translate("Deal", "\347\201\253\350\275\246", nullptr));
        comboBox_type->setItemText(3, QCoreApplication::translate("Deal", "\346\261\275\350\275\246", nullptr));

        btn_search->setText(QCoreApplication::translate("Deal", "\346\220\234\347\264\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_tickets->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Deal", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_tickets->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Deal", "\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_tickets->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Deal", "\345\207\272\345\217\221\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_tickets->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Deal", "\347\233\256\347\232\204\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_tickets->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Deal", "\345\207\272\345\217\221\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_tickets->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Deal", "\345\210\260\350\276\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_tickets->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Deal", "\344\273\267\346\240\274\357\274\210\345\205\203\357\274\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_tickets->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Deal", "\345\217\257\347\224\250\345\272\247\344\275\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_tickets->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("Deal", "\345\205\254\345\217\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_tickets->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("Deal", "\346\223\215\344\275\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_tickets->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("Deal", "\346\224\266\350\227\217", nullptr));
        home->setText(QCoreApplication::translate("Deal", "\351\246\226\351\241\265", nullptr));
        Deal_2->setText(QCoreApplication::translate("Deal", "\350\241\214\347\250\213", nullptr));
        Single_Center->setText(QCoreApplication::translate("Deal", "\344\270\252\344\272\272\344\270\255\345\277\203", nullptr));
        favorite_button->setText(QCoreApplication::translate("Deal", "\346\224\266\350\227\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Deal: public Ui_Deal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEAL_H
