/********************************************************************************
** Form generated from reading UI file 'userprofile.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPROFILE_H
#define UI_USERPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserProfile
{
public:
    QWidget *widget;
    QLabel *label;
    QPushButton *btn_back;
    QFrame *frame;
    QLabel *label_2;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *label_username;
    QLineEdit *lineEdit_2;
    QLineEdit *label_jianjie;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QFrame *frame_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *edit_btn;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;

    void setupUi(QWidget *UserProfile)
    {
        if (UserProfile->objectName().isEmpty())
            UserProfile->setObjectName("UserProfile");
        UserProfile->setEnabled(true);
        UserProfile->resize(1000, 700);
        UserProfile->setAutoFillBackground(false);
        UserProfile->setStyleSheet(QString::fromUtf8("/* ================= \345\205\250\345\261\200\350\256\276\347\275\256 ================= */\n"
"QWidget {\n"
"    font-family: \"Microsoft YaHei\", \"Segoe UI\", sans-serif;\n"
"    color: #ffffff; /* \345\205\250\345\261\200\347\231\275\350\211\262\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"QWidget#UserProfile {\n"
"    background-color: #2d2d2d; /* \345\205\250\345\261\200\346\267\261\350\211\262\350\203\214\346\231\257 */\n"
"}\n"
"\n"
"/* ================= \346\214\211\351\222\256\347\273\237\344\270\200\351\243\216\346\240\274 (\345\244\215\347\224\250 deal.ui \346\240\267\345\274\217) ================= */\n"
"QPushButton {\n"
"    background-color: #606060;\n"
"    border: 1px solid #ffffff;\n"
"    border-radius: 6px;\n"
"    padding: 8px 16px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    /* \346\250\241\346\213\237\351\230\264\345\275\261\346\225\210\346\236\234 */\n"
"    box-shadow: inset 2px 2px 4px #484848,\n"
"                inset -2px -2px 4px #787878;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
""
                        "    background-color: #646464;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #404040;      \n"
"    border: 1px solid #555555;     \n"
"    padding-left: 10px;            \n"
"    padding-top: 10px;               \n"
"    padding-right: 6px;           \n"
"    padding-bottom: 6px;             \n"
"\n"
"    box-shadow: inset 4px 4px 8px #202020,\n"
"                inset -4px -4px 8px #505050;\n"
"}\n"
"\n"
"/* ================= \351\241\266\351\203\250\345\257\274\350\210\252\346\240\217 ================= */\n"
"QWidget#widget {\n"
"    background-color: #3b3b3b;\n"
"    border-bottom: 1px solid #555555;\n"
"}\n"
"\n"
"/* \346\240\207\351\242\230 */\n"
"QLabel#label {\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"/* ================= \345\215\241\347\211\207\346\240\267\345\274\217 ================= */\n"
"QFrame#frame, QFrame#frame_2 {\n"
"    background-color: #3b3b3b;\n"
"    border-radius: 12px;\n"
"    border: 1px solid #555555;\n"
"}\n"
"\n"
""
                        "/* ================= \344\270\252\344\272\272\344\277\241\346\201\257\345\214\272 ================= */\n"
"/* \345\244\264\345\203\217\346\241\206 */\n"
"QLabel#label_2 {\n"
"    background-color: #505050;\n"
"    border-radius: 35px;\n"
"    border: 2px solid #606060;\n"
"    color: #cccccc;\n"
"    qproperty-alignment: AlignCenter;\n"
"}\n"
"\n"
"/* \350\241\250\345\215\225\346\240\207\347\255\276 */\n"
"QFormLayout QLabel {\n"
"    color: #cccccc;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* \345\217\252\350\257\273\350\276\223\345\205\245\346\241\206 */\n"
"QLineEdit[readOnly=\"true\"] {\n"
"    background: transparent;\n"
"    border: none;\n"
"    border-bottom: 1px solid #555555;\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding-bottom: 2px;\n"
"}"));
        widget = new QWidget(UserProfile);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 981, 41));
        widget->setStyleSheet(QString::fromUtf8("background-color: #3b3b3b;"));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 81, 21));
        btn_back = new QPushButton(widget);
        btn_back->setObjectName("btn_back");
        btn_back->setGeometry(QRect(880, 5, 80, 30));
        btn_back->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        frame = new QFrame(UserProfile);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 60, 981, 181));
        frame->setStyleSheet(QString::fromUtf8("background-color: #3b3b3b;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 20, 121, 141));
        label_2->setStyleSheet(QString::fromUtf8("background-color: #505050;"));
        formLayoutWidget = new QWidget(frame);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(570, 40, 291, 121));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_3);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_4);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName("label_5");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_5);

        label_username = new QLineEdit(formLayoutWidget);
        label_username->setObjectName("label_username");
        label_username->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, label_username);

        lineEdit_2 = new QLineEdit(formLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_2);

        label_jianjie = new QLineEdit(formLayoutWidget);
        label_jianjie->setObjectName("label_jianjie");
        label_jianjie->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, label_jianjie);

        lineEdit_4 = new QLineEdit(formLayoutWidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEdit_4);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName("label_6");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_6);

        frame_2 = new QFrame(UserProfile);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 250, 981, 441));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #3b3b3b;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayoutWidget = new QWidget(frame_2);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(50, 30, 281, 341));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        edit_btn = new QPushButton(verticalLayoutWidget);
        edit_btn->setObjectName("edit_btn");

        verticalLayout->addWidget(edit_btn);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName("pushButton_4");

        verticalLayout->addWidget(pushButton_4);

        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName("pushButton_6");

        verticalLayout->addWidget(pushButton_6);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        verticalLayoutWidget_2 = new QWidget(frame_2);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(630, 40, 271, 311));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_8 = new QPushButton(verticalLayoutWidget_2);
        pushButton_8->setObjectName("pushButton_8");

        verticalLayout_2->addWidget(pushButton_8);

        pushButton_7 = new QPushButton(verticalLayoutWidget_2);
        pushButton_7->setObjectName("pushButton_7");

        verticalLayout_2->addWidget(pushButton_7);

        pushButton_9 = new QPushButton(verticalLayoutWidget_2);
        pushButton_9->setObjectName("pushButton_9");

        verticalLayout_2->addWidget(pushButton_9);


        retranslateUi(UserProfile);

        QMetaObject::connectSlotsByName(UserProfile);
    } // setupUi

    void retranslateUi(QWidget *UserProfile)
    {
        UserProfile->setWindowTitle(QCoreApplication::translate("UserProfile", "Form", nullptr));
        label->setText(QCoreApplication::translate("UserProfile", "\344\270\252\344\272\272\344\270\255\345\277\203", nullptr));
        btn_back->setText(QCoreApplication::translate("UserProfile", "\350\277\224\345\233\236", nullptr));
        label_2->setText(QCoreApplication::translate("UserProfile", "\347\205\247\347\211\207", nullptr));
        label_3->setText(QCoreApplication::translate("UserProfile", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("UserProfile", "\347\256\200\344\273\213\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("UserProfile", "\350\264\246\345\217\267\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("UserProfile", "\351\222\261\345\214\205\344\275\231\351\242\235\357\274\232", nullptr));
        edit_btn->setText(QCoreApplication::translate("UserProfile", "\347\274\226\350\276\221\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
        pushButton_4->setText(QCoreApplication::translate("UserProfile", "\346\210\221\347\232\204\350\256\242\345\215\225", nullptr));
        pushButton_6->setText(QCoreApplication::translate("UserProfile", "\345\205\205\345\200\274", nullptr));
        pushButton_2->setText(QCoreApplication::translate("UserProfile", "\346\224\266\350\227\217", nullptr));
        pushButton_8->setText(QCoreApplication::translate("UserProfile", "\346\263\250\345\206\214", nullptr));
        pushButton_7->setText(QCoreApplication::translate("UserProfile", "\347\231\273\345\275\225", nullptr));
        pushButton_9->setText(QCoreApplication::translate("UserProfile", "\346\263\250\351\224\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserProfile: public Ui_UserProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPROFILE_H
