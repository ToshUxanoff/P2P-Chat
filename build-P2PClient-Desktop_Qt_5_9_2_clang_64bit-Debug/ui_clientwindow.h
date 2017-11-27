/********************************************************************************
** Form generated from reading UI file 'clientwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWINDOW_H
#define UI_CLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *SearchLine;
    QTextBrowser *DebugWindow;
    QLineEdit *NameInput;
    QLabel *NameLabel;
    QLabel *label_2;
    QTextBrowser *MsgBrowser;
    QPushButton *SendMsg;
    QLineEdit *MsgInput;
    QLabel *label_3;
    QListWidget *FriendList;
    QLabel *label_4;
    QCheckBox *checkBox;
    QPushButton *UpdateListButton;
    QLabel *label;
    QLabel *DestName;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ClientWindow)
    {
        if (ClientWindow->objectName().isEmpty())
            ClientWindow->setObjectName(QStringLiteral("ClientWindow"));
        ClientWindow->resize(739, 466);
        centralWidget = new QWidget(ClientWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SearchLine = new QLineEdit(centralWidget);
        SearchLine->setObjectName(QStringLiteral("SearchLine"));
        SearchLine->setGeometry(QRect(152, 30, 131, 21));
        DebugWindow = new QTextBrowser(centralWidget);
        DebugWindow->setObjectName(QStringLiteral("DebugWindow"));
        DebugWindow->setGeometry(QRect(10, 350, 261, 61));
        NameInput = new QLineEdit(centralWidget);
        NameInput->setObjectName(QStringLiteral("NameInput"));
        NameInput->setGeometry(QRect(10, 30, 113, 21));
        NameLabel = new QLabel(centralWidget);
        NameLabel->setObjectName(QStringLiteral("NameLabel"));
        NameLabel->setGeometry(QRect(10, 10, 161, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 10, 131, 16));
        MsgBrowser = new QTextBrowser(centralWidget);
        MsgBrowser->setObjectName(QStringLiteral("MsgBrowser"));
        MsgBrowser->setGeometry(QRect(290, 30, 331, 321));
        SendMsg = new QPushButton(centralWidget);
        SendMsg->setObjectName(QStringLiteral("SendMsg"));
        SendMsg->setGeometry(QRect(610, 360, 91, 41));
        MsgInput = new QLineEdit(centralWidget);
        MsgInput->setObjectName(QStringLiteral("MsgInput"));
        MsgInput->setGeometry(QRect(290, 350, 331, 61));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 80, 91, 16));
        FriendList = new QListWidget(centralWidget);
        FriendList->setObjectName(QStringLiteral("FriendList"));
        FriendList->setGeometry(QRect(10, 100, 256, 221));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(100, 325, 141, 21));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 50, 121, 20));
        UpdateListButton = new QPushButton(centralWidget);
        UpdateListButton->setObjectName(QStringLiteral("UpdateListButton"));
        UpdateListButton->setGeometry(QRect(200, 320, 71, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(310, 10, 101, 16));
        DestName = new QLabel(centralWidget);
        DestName->setObjectName(QStringLiteral("DestName"));
        DestName->setGeometry(QRect(400, 10, 211, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(520, 10, 101, 21));
        ClientWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ClientWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 739, 22));
        ClientWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ClientWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ClientWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ClientWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ClientWindow->setStatusBar(statusBar);

        retranslateUi(ClientWindow);

        QMetaObject::connectSlotsByName(ClientWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ClientWindow)
    {
        ClientWindow->setWindowTitle(QApplication::translate("ClientWindow", "ClientWindow", Q_NULLPTR));
        SearchLine->setText(QString());
        NameInput->setText(QString());
        NameLabel->setText(QApplication::translate("ClientWindow", "Name", Q_NULLPTR));
        label_2->setText(QApplication::translate("ClientWindow", "Private users search", Q_NULLPTR));
        SendMsg->setText(QApplication::translate("ClientWindow", "Send", Q_NULLPTR));
        label_3->setText(QApplication::translate("ClientWindow", "Peers list", Q_NULLPTR));
        label_4->setText(QApplication::translate("ClientWindow", "Information", Q_NULLPTR));
        checkBox->setText(QApplication::translate("ClientWindow", "Private account", Q_NULLPTR));
        UpdateListButton->setText(QApplication::translate("ClientWindow", "Update", Q_NULLPTR));
        label->setText(QApplication::translate("ClientWindow", "Message for:", Q_NULLPTR));
        DestName->setText(QString());
        pushButton->setText(QApplication::translate("ClientWindow", "Create Issue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ClientWindow: public Ui_ClientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
