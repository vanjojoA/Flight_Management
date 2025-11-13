/********************************************************************************
** Form generated from reading UI file 'maininterface.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAININTERFACE_H
#define UI_MAININTERFACE_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_MainInterface
{
public:
    QFrame *frame;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QDateEdit *dateEditInput;
    QPushButton *pushButton;
    QLabel *label_4;
    QComboBox *comboBox;
    QTableWidget *tableWidget;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QDialog *MainInterface)
    {
        if (MainInterface->objectName().isEmpty())
            MainInterface->setObjectName(QString::fromUtf8("MainInterface"));
        MainInterface->resize(1140, 693);
        MainInterface->setStyleSheet(QString::fromUtf8("background-color: rgb(45, 45, 45);"));
        frame = new QFrame(MainInterface);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 1101, 111));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 59, 59);"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(2);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 51, 19));
        label->setStyleSheet(QString::fromUtf8("color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        label->setFrameShadow(QFrame::Plain);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 30, 121, 25));
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(240, 30, 69, 19));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_2 = new QLineEdit(frame);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(310, 30, 131, 25));
        lineEdit_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(490, 30, 41, 19));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        dateEditInput = new QDateEdit(frame);
        dateEditInput->setObjectName(QString::fromUtf8("dateEditInput"));
        dateEditInput->setGeometry(QRect(540, 20, 141, 41));
        dateEditInput->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 8px 35px 8px 12px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
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
        dateEditInput->setCalendarPopup(true);
        dateEditInput->setDate(QDate(2025, 11, 1));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(930, 30, 93, 28));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
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
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(730, 30, 51, 19));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        comboBox = new QComboBox(frame);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(780, 20, 91, 41));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 8px 35px 8px 12px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    min-height: 25px;\n"
"    box-shadow: inset 2px 2px 5px #484848, \n"
"                inset -2px -2px 5px #787878;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    background-color: #646464;\n"
"}"));
        comboBox->setFrame(false);
        tableWidget = new QTableWidget(MainInterface);
        if (tableWidget->columnCount() < 10)
            tableWidget->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setBackground(QColor(0, 0, 0));
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 140, 1121, 451));
        QPalette palette;
        QBrush brush(QColor(45, 45, 45, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        tableWidget->setPalette(palette);
        tableWidget->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"    background-color: #000000;\n"
"    color: #ffffff;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}"));
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(false);
        pushButton_2 = new QPushButton(MainInterface);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 610, 311, 81));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
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
        pushButton_3 = new QPushButton(MainInterface);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(420, 610, 301, 81));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
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
        pushButton_4 = new QPushButton(MainInterface);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(810, 610, 301, 81));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #606060;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
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

        retranslateUi(MainInterface);

        QMetaObject::connectSlotsByName(MainInterface);
    } // setupUi

    void retranslateUi(QDialog *MainInterface)
    {
        MainInterface->setWindowTitle(QCoreApplication::translate("MainInterface", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("MainInterface", "\345\207\272\345\217\221\345\234\260:", nullptr));
        label_2->setText(QCoreApplication::translate("MainInterface", "\347\233\256\347\232\204\345\234\260\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainInterface", "\346\227\245\346\234\237\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("MainInterface", "\346\220\234\347\264\242", nullptr));
        label_4->setText(QCoreApplication::translate("MainInterface", "\347\261\273\345\236\213\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainInterface", "\345\205\250\351\203\250", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainInterface", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainInterface", "\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainInterface", "\345\207\272\345\217\221\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainInterface", "\347\233\256\347\232\204\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainInterface", "\345\207\272\345\217\221\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainInterface", "\345\210\260\350\276\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainInterface", "\344\273\267\346\240\274\357\274\210\345\205\203\357\274\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainInterface", "\345\217\257\347\224\250\345\272\247\344\275\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainInterface", "\345\205\254\345\217\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainInterface", "\346\223\215\344\275\234", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainInterface", "\351\246\226\351\241\265", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainInterface", "\350\241\214\347\250\213", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainInterface", "\344\270\252\344\272\272\344\270\255\345\277\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainInterface: public Ui_MainInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAININTERFACE_H
