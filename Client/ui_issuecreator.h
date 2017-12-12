/********************************************************************************
** Form generated from reading UI file 'issuecreator.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISSUECREATOR_H
#define UI_ISSUECREATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_issuecreator
{
public:
    QLineEdit *PassEdit;
    QLineEdit *RepoNameEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *UsernameEdit;
    QLabel *label_5;
    QLabel *statusLabel;
    QFrame *frame;
    QLabel *label_4;
    QTextEdit *DescriptionEdit;
    QLineEdit *TitleEdit;
    QPushButton *Send;

    void setupUi(QDialog *issuecreator)
    {
        if (issuecreator->objectName().isEmpty())
            issuecreator->setObjectName(QStringLiteral("issuecreator"));
        issuecreator->resize(398, 300);
        issuecreator->setMinimumSize(QSize(398, 300));
        issuecreator->setMaximumSize(QSize(398, 300));
        PassEdit = new QLineEdit(issuecreator);
        PassEdit->setObjectName(QStringLiteral("PassEdit"));
        PassEdit->setGeometry(QRect(280, 30, 111, 21));
        PassEdit->setStyleSheet(QStringLiteral(" border: 1px solid black;"));
        PassEdit->setEchoMode(QLineEdit::Password);
        RepoNameEdit = new QLineEdit(issuecreator);
        RepoNameEdit->setObjectName(QStringLiteral("RepoNameEdit"));
        RepoNameEdit->setGeometry(QRect(10, 30, 113, 21));
        RepoNameEdit->setStyleSheet(QStringLiteral(" border: 1px solid black;"));
        label = new QLabel(issuecreator);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 111, 16));
        label_2 = new QLabel(issuecreator);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(300, 10, 71, 16));
        label_3 = new QLabel(issuecreator);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(140, 10, 111, 16));
        UsernameEdit = new QLineEdit(issuecreator);
        UsernameEdit->setObjectName(QStringLiteral("UsernameEdit"));
        UsernameEdit->setGeometry(QRect(140, 30, 121, 21));
        UsernameEdit->setStyleSheet(QStringLiteral(" border: 1px solid black;"));
        label_5 = new QLabel(issuecreator);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 120, 81, 16));
        statusLabel = new QLabel(issuecreator);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(50, 260, 181, 21));
        frame = new QFrame(issuecreator);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-10, 80, 411, 221));
        frame->setStyleSheet(QStringLiteral(" border: 1px solid black;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 10, 71, 16));
        label_4->setStyleSheet(QStringLiteral(" border: none;"));
        DescriptionEdit = new QTextEdit(frame);
        DescriptionEdit->setObjectName(QStringLiteral("DescriptionEdit"));
        DescriptionEdit->setGeometry(QRect(20, 60, 371, 121));
        DescriptionEdit->setStyleSheet(QStringLiteral(" border: 1px solid black;"));
        TitleEdit = new QLineEdit(frame);
        TitleEdit->setObjectName(QStringLiteral("TitleEdit"));
        TitleEdit->setGeometry(QRect(130, 30, 161, 21));
        TitleEdit->setStyleSheet(QStringLiteral(" border: 1px solid black;"));
        Send = new QPushButton(frame);
        Send->setObjectName(QStringLiteral("Send"));
        Send->setGeometry(QRect(310, 180, 81, 21));
        Send->setStyleSheet(QStringLiteral("background-color: rgb(248, 188, 10) ; border: 1px solid black;"));

        retranslateUi(issuecreator);

        QMetaObject::connectSlotsByName(issuecreator);
    } // setupUi

    void retranslateUi(QDialog *issuecreator)
    {
        issuecreator->setWindowTitle(QApplication::translate("issuecreator", "Dialog", nullptr));
        PassEdit->setText(QString());
        RepoNameEdit->setText(QString());
        label->setText(QApplication::translate("issuecreator", "Repository name", nullptr));
        label_2->setText(QApplication::translate("issuecreator", "Password", nullptr));
        label_3->setText(QApplication::translate("issuecreator", "Github username", nullptr));
        label_5->setText(QApplication::translate("issuecreator", "Description", nullptr));
        statusLabel->setText(QString());
        label_4->setText(QApplication::translate("issuecreator", "Issue title", nullptr));
        TitleEdit->setText(QString());
        Send->setText(QApplication::translate("issuecreator", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class issuecreator: public Ui_issuecreator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISSUECREATOR_H
