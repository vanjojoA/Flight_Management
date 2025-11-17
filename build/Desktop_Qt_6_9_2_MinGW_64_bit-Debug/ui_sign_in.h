/********************************************************************************
** Form generated from reading UI file 'sign_in.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_IN_H
#define UI_SIGN_IN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sign_in
{
public:
    QLineEdit *Sign_in_UsernameT;
    QLineEdit *Sign_in_PassWordT;
    QLineEdit *Sign_in_PassWordAT;
    QLabel *Sign_in_Username;
    QLabel *Sign_in_PassWord;
    QLabel *Sign_in_PassWordA;
    QPushButton *Sign_in_Button;
    QPushButton *Sign_in_Cencel;

    void setupUi(QWidget *Sign_in)
    {
        if (Sign_in->objectName().isEmpty())
            Sign_in->setObjectName("Sign_in");
        Sign_in->resize(683, 438);
        Sign_in_UsernameT = new QLineEdit(Sign_in);
        Sign_in_UsernameT->setObjectName("Sign_in_UsernameT");
        Sign_in_UsernameT->setGeometry(QRect(260, 90, 171, 27));
        Sign_in_PassWordT = new QLineEdit(Sign_in);
        Sign_in_PassWordT->setObjectName("Sign_in_PassWordT");
        Sign_in_PassWordT->setGeometry(QRect(260, 130, 171, 27));
        Sign_in_PassWordAT = new QLineEdit(Sign_in);
        Sign_in_PassWordAT->setObjectName("Sign_in_PassWordAT");
        Sign_in_PassWordAT->setGeometry(QRect(260, 180, 171, 27));
        Sign_in_Username = new QLabel(Sign_in);
        Sign_in_Username->setObjectName("Sign_in_Username");
        Sign_in_Username->setGeometry(QRect(170, 90, 69, 19));
        Sign_in_PassWord = new QLabel(Sign_in);
        Sign_in_PassWord->setObjectName("Sign_in_PassWord");
        Sign_in_PassWord->setGeometry(QRect(170, 140, 69, 19));
        Sign_in_PassWordA = new QLabel(Sign_in);
        Sign_in_PassWordA->setObjectName("Sign_in_PassWordA");
        Sign_in_PassWordA->setGeometry(QRect(160, 190, 69, 19));
        Sign_in_Button = new QPushButton(Sign_in);
        Sign_in_Button->setObjectName("Sign_in_Button");
        Sign_in_Button->setGeometry(QRect(180, 270, 99, 28));
        Sign_in_Cencel = new QPushButton(Sign_in);
        Sign_in_Cencel->setObjectName("Sign_in_Cencel");
        Sign_in_Cencel->setGeometry(QRect(350, 270, 99, 28));

        retranslateUi(Sign_in);

        QMetaObject::connectSlotsByName(Sign_in);
    } // setupUi

    void retranslateUi(QWidget *Sign_in)
    {
        Sign_in->setWindowTitle(QCoreApplication::translate("Sign_in", "\346\263\250\345\206\214", nullptr));
        Sign_in_UsernameT->setPlaceholderText(QCoreApplication::translate("Sign_in", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204\347\224\250\346\210\267\345\220\215...", nullptr));
        Sign_in_PassWordT->setPlaceholderText(QCoreApplication::translate("Sign_in", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204\345\257\206\347\240\201...", nullptr));
        Sign_in_PassWordAT->setPlaceholderText(QCoreApplication::translate("Sign_in", "\350\257\267\347\241\256\350\256\244\344\275\240\347\232\204\345\257\206\347\240\201...", nullptr));
        Sign_in_Username->setText(QCoreApplication::translate("Sign_in", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        Sign_in_PassWord->setText(QCoreApplication::translate("Sign_in", "\345\257\206\347\240\201\357\274\232", nullptr));
        Sign_in_PassWordA->setText(QCoreApplication::translate("Sign_in", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        Sign_in_Button->setText(QCoreApplication::translate("Sign_in", "\346\263\250\345\206\214", nullptr));
        Sign_in_Cencel->setText(QCoreApplication::translate("Sign_in", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sign_in: public Ui_Sign_in {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_IN_H
