/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QCheckBox *isPrivate;
    QPushButton *EnterButton;
    QPushButton *ExitButton;
    QLabel *label;
    QLineEdit *UserNickname;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(403, 159);
        isPrivate = new QCheckBox(login);
        isPrivate->setObjectName(QStringLiteral("isPrivate"));
        isPrivate->setGeometry(QRect(230, 70, 121, 20));
        EnterButton = new QPushButton(login);
        EnterButton->setObjectName(QStringLiteral("EnterButton"));
        EnterButton->setGeometry(QRect(240, 100, 113, 32));
        ExitButton = new QPushButton(login);
        ExitButton->setObjectName(QStringLiteral("ExitButton"));
        ExitButton->setGeometry(QRect(150, 100, 71, 32));
        label = new QLabel(login);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 111, 16));
        UserNickname = new QLineEdit(login);
        UserNickname->setObjectName(QStringLiteral("UserNickname"));
        UserNickname->setGeometry(QRect(160, 40, 181, 21));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Dialog", Q_NULLPTR));
        isPrivate->setText(QApplication::translate("login", "Private account", Q_NULLPTR));
        EnterButton->setText(QApplication::translate("login", "Enter chat", Q_NULLPTR));
        ExitButton->setText(QApplication::translate("login", "Exit", Q_NULLPTR));
        label->setText(QApplication::translate("login", "Enter your name:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
