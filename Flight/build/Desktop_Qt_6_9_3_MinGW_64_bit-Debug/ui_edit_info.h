/********************************************************************************
** Form generated from reading UI file 'edit_info.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_INFO_H
#define UI_EDIT_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_edit_info
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_3;
    QLineEdit *old_name;
    QLineEdit *new_name;
    QLabel *label_4;
    QLineEdit *new_jianjie;
    QLabel *label_newname;

    void setupUi(QDialog *edit_info)
    {
        if (edit_info->objectName().isEmpty())
            edit_info->setObjectName("edit_info");
        edit_info->resize(634, 361);
        edit_info->setStyleSheet(QString::fromUtf8("/* ================= \345\205\250\345\261\200\347\252\227\345\217\243\350\256\276\347\275\256 ================= */\n"
"QDialog {\n"
"    background-color: #ffffff;   /* \347\231\275\345\272\225 */\n"
"    color: #333333;              /* \346\267\261\347\201\260\350\211\262\345\255\227\344\275\223 (\346\257\224\347\272\257\351\273\221\346\233\264\346\237\224\345\222\214) */\n"
"    font-family: \"Microsoft YaHei\", \"Segoe UI\", sans-serif;\n"
"}\n"
"\n"
"/* ================= \346\240\207\347\255\276 (Label) \346\240\267\345\274\217 ================= */\n"
"QLabel {\n"
"    color: #333333;              /* \346\240\207\347\255\276\346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    font-size: 14px;\n"
"    font-weight: bold;           /* \345\212\240\347\262\227\357\274\214\346\217\220\345\215\207\350\276\250\350\257\206\345\272\246 */\n"
"    background: transparent;     /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"}\n"
"\n"
"/* ================= \350\276\223\345\205\245\346\241\206 (LineEd"
                        "it) \346\240\267\345\274\217 ================= */\n"
"QLineEdit {\n"
"    background-color: #f7f7f7;   /* \346\236\201\346\265\205\347\201\260\350\211\262\350\203\214\346\231\257\357\274\214\345\214\272\345\210\206\347\231\275\350\211\262\345\272\225\346\235\277 */\n"
"    border: 1px solid #cccccc;   /* \346\265\205\347\201\260\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 4px;          /* 4px \345\234\206\350\247\222 */\n"
"    color: #000000;              /* \350\276\223\345\205\245\345\206\205\345\256\271\344\270\272\347\272\257\351\273\221 */\n"
"    padding: 5px 8px;            /* \345\242\236\345\212\240\344\270\200\347\202\271\345\206\205\350\276\271\350\267\235\357\274\214\346\226\207\345\255\227\344\270\215\346\213\245\346\214\244 */\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* \350\276\223\345\205\245\346\241\206\350\216\267\345\276\227\347\204\246\347\202\271\357\274\210\351\274\240\346\240\207\347\202\271\350\277\233\345\216\273\357\274\211\346\227\266\347\232\204\346\240\267\345\274"
                        "\217 */\n"
"QLineEdit:focus {\n"
"    background-color: #ffffff;   /* \351\200\211\344\270\255\346\227\266\350\203\214\346\231\257\345\217\230\347\231\275 */\n"
"    border: 1px solid #0078d7;   /* \350\276\271\346\241\206\345\217\230\344\270\272\344\272\256\350\223\235\350\211\262 */\n"
"}\n"
"\n"
"/* \351\222\210\345\257\271\345\217\252\350\257\273\350\276\223\345\205\245\346\241\206\357\274\210\345\246\202\345\216\237\347\224\250\346\210\267\345\220\215\357\274\211\347\232\204\346\240\267\345\274\217 */\n"
"QLineEdit[readOnly=\"true\"] {\n"
"    background-color: #eeeeee;   /* \347\201\260\350\211\262\350\203\214\346\231\257\350\241\250\347\244\272\344\270\215\345\217\257\347\274\226\350\276\221 */\n"
"    color: #888888;              /* \346\226\207\345\255\227\345\217\230\346\267\241 */\n"
"    border: 1px solid #dddddd;\n"
"}\n"
"\n"
"/* ================= \346\214\211\351\222\256 (PushButton) \346\240\267\345\274\217 ================= */\n"
"QPushButton {\n"
"    background-color: #ffffff;   /* \346\214\211"
                        "\351\222\256\347\231\275\345\272\225 */\n"
"    border: 1px solid #dcdcdc;   /* \347\201\260\350\211\262\347\273\206\350\276\271\346\241\206 */\n"
"    border-bottom: 2px solid #b0b0b0; /* \345\272\225\351\203\250\345\212\240\347\262\227\357\274\214\346\250\241\346\213\237\347\253\213\344\275\223\346\204\237 */\n"
"    border-radius: 6px;          /* \345\234\206\350\247\222\346\214\211\351\222\256 */\n"
"    color: #333333;              /* \346\214\211\351\222\256\346\226\207\345\255\227 */\n"
"    font-size: 14px;\n"
"    padding: 6px 16px;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234\345\234\250\346\214\211\351\222\256\344\270\212 */\n"
"QPushButton:hover {\n"
"    background-color: #f0f8ff;   /* \345\276\256\345\276\256\345\217\230\350\223\235\347\232\204\350\203\214\346\231\257 */\n"
"    border-color: #0078d7;       /* \350\276\271\346\241\206\345\217\230\350\223\235 */\n"
"    color: #0078d7;              /* \346\226\207\345\255\227\345\217\230\350\223\235 */\n"
"}\n"
"\n"
"/* \351"
                        "\274\240\346\240\207\346\214\211\344\270\213\346\214\211\351\222\256 */\n"
"QPushButton:pressed {\n"
"    background-color: #e0e0e0;   /* \346\214\211\344\270\213\350\203\214\346\231\257\345\217\230\346\267\261 */\n"
"    border-top: 2px solid #b0b0b0; /* \346\250\241\346\213\237\346\214\211\345\216\213\345\207\271\351\231\267\346\225\210\346\236\234 */\n"
"    border-bottom: none;         /* \345\216\273\346\216\211\345\272\225\351\203\250\347\253\213\344\275\223\350\276\271\346\241\206 */\n"
"    padding-top: 8px;            /* \346\226\207\345\255\227\344\270\213\347\247\273\357\274\214\344\272\247\347\224\237\346\214\211\345\216\213\345\212\250\346\225\210 */\n"
"    padding-bottom: 4px;\n"
"}\n"
"\n"
"/* \351\222\210\345\257\271\342\200\234\347\241\256\350\256\244/\345\217\226\346\266\210\342\200\235\346\214\211\351\222\256\347\233\222\345\255\220\347\232\204\347\211\271\346\256\212\345\276\256\350\260\203\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QDialogButtonBox QPushButton {\n"
"    min-wi"
                        "dth: 60px;             /* \344\277\235\350\257\201\346\214\211\351\222\256\344\270\215\350\246\201\345\244\252\347\252\204 */\n"
"}"));
        buttonBox = new QDialogButtonBox(edit_info);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(240, 290, 211, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(edit_info);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 50, 111, 19));
        pushButton = new QPushButton(edit_info);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(260, 50, 191, 28));
        label_3 = new QLabel(edit_info);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(160, 100, 69, 19));
        old_name = new QLineEdit(edit_info);
        old_name->setObjectName("old_name");
        old_name->setGeometry(QRect(260, 100, 191, 31));
        new_name = new QLineEdit(edit_info);
        new_name->setObjectName("new_name");
        new_name->setGeometry(QRect(260, 150, 191, 31));
        label_4 = new QLabel(edit_info);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(160, 200, 69, 19));
        new_jianjie = new QLineEdit(edit_info);
        new_jianjie->setObjectName("new_jianjie");
        new_jianjie->setGeometry(QRect(260, 200, 191, 27));
        label_newname = new QLabel(edit_info);
        label_newname->setObjectName("label_newname");
        label_newname->setGeometry(QRect(160, 150, 69, 19));

        retranslateUi(edit_info);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, edit_info, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, edit_info, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(edit_info);
    } // setupUi

    void retranslateUi(QDialog *edit_info)
    {
        edit_info->setWindowTitle(QCoreApplication::translate("edit_info", "\347\274\226\350\276\221\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("edit_info", "\350\256\276\347\275\256\344\275\240\347\232\204\347\205\247\347\211\207\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("edit_info", "\351\200\211\346\213\251\346\234\254\345\234\260\345\233\276\347\211\207", nullptr));
        label_3->setText(QCoreApplication::translate("edit_info", "\345\216\237\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("edit_info", "\347\256\200\344\273\213\357\274\232", nullptr));
        label_newname->setText(QCoreApplication::translate("edit_info", "\346\226\260\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_info: public Ui_edit_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_INFO_H
