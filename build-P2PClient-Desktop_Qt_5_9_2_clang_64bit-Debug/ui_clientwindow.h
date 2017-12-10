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
#include <QtWidgets/QFrame>
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
    QLineEdit *NameInput;
    QLabel *NameLabel;
    QTextBrowser *MsgBrowser;
    QLineEdit *MsgInput;
    QLabel *label_3;
    QListWidget *FriendList;
    QCheckBox *checkBox;
    QPushButton *UpdateListButton;
    QLabel *label;
    QLabel *DestName;
    QFrame *frame;
    QLineEdit *SearchLine;
    QLabel *label_2;
    QPushButton *SearchButton;
    QLabel *DebugLabel;
    QFrame *frame_2;
    QPushButton *pushButton;
    QPushButton *LoginButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ClientWindow)
    {
        if (ClientWindow->objectName().isEmpty())
            ClientWindow->setObjectName(QStringLiteral("ClientWindow"));
        ClientWindow->resize(640, 480);
        ClientWindow->setMinimumSize(QSize(640, 480));
        ClientWindow->setMaximumSize(QSize(640, 480));
        ClientWindow->setAutoFillBackground(false);
        ClientWindow->setStyleSheet(QStringLiteral(""));
        ClientWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralWidget = new QWidget(ClientWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        NameInput = new QLineEdit(centralWidget);
        NameInput->setObjectName(QStringLiteral("NameInput"));
        NameInput->setGeometry(QRect(10, 30, 191, 21));
        NameInput->setStyleSheet(QStringLiteral("border: 1px solid black;"));
        NameLabel = new QLabel(centralWidget);
        NameLabel->setObjectName(QStringLiteral("NameLabel"));
        NameLabel->setGeometry(QRect(10, 10, 271, 16));
        MsgBrowser = new QTextBrowser(centralWidget);
        MsgBrowser->setObjectName(QStringLiteral("MsgBrowser"));
        MsgBrowser->setGeometry(QRect(290, 30, 331, 321));
        MsgBrowser->setStyleSheet(QStringLiteral("border: 1px solid black;"));
        MsgInput = new QLineEdit(centralWidget);
        MsgInput->setObjectName(QStringLiteral("MsgInput"));
        MsgInput->setGeometry(QRect(290, 360, 331, 61));
        MsgInput->setStyleSheet(QStringLiteral("border: 1px solid black;"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 91, 16));
        FriendList = new QListWidget(centralWidget);
        FriendList->setObjectName(QStringLiteral("FriendList"));
        FriendList->setGeometry(QRect(10, 110, 260, 251));
        FriendList->setStyleSheet(QStringLiteral("border: 1px solid black;"));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 50, 121, 20));
        UpdateListButton = new QPushButton(centralWidget);
        UpdateListButton->setObjectName(QStringLiteral("UpdateListButton"));
        UpdateListButton->setGeometry(QRect(199, 90, 71, 21));
        UpdateListButton->setMouseTracking(false);
        UpdateListButton->setStyleSheet(QStringLiteral("background-color:orange ;border: 1px solid black;"));
        UpdateListButton->setCheckable(false);
        UpdateListButton->setFlat(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(300, 10, 101, 16));
        DestName = new QLabel(centralWidget);
        DestName->setObjectName(QStringLiteral("DestName"));
        DestName->setGeometry(QRect(390, 10, 131, 16));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 360, 260, 61));
        frame->setStyleSheet(QStringLiteral(" border: 1px solid black ;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        SearchLine = new QLineEdit(frame);
        SearchLine->setObjectName(QStringLiteral("SearchLine"));
        SearchLine->setGeometry(QRect(10, 30, 201, 21));
        SearchLine->setStyleSheet(QStringLiteral("background-color: white; border: 1px solid black;"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 131, 16));
        label_2->setStyleSheet(QStringLiteral("border:none;"));
        SearchButton = new QPushButton(frame);
        SearchButton->setObjectName(QStringLiteral("SearchButton"));
        SearchButton->setGeometry(QRect(210, 30, 41, 21));
        SearchButton->setStyleSheet(QStringLiteral("background-color:rgb(132, 176, 255) ;border: 1px solid black;"));
        DebugLabel = new QLabel(centralWidget);
        DebugLabel->setObjectName(QStringLiteral("DebugLabel"));
        DebugLabel->setGeometry(QRect(9, 425, 271, 20));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(290, 10, 231, 21));
        frame_2->setStyleSheet(QStringLiteral("border : 1px solid black;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(520, 10, 101, 21));
        pushButton->setStyleSheet(QStringLiteral("background-color:orange ;border: 1px solid black;"));
        LoginButton = new QPushButton(centralWidget);
        LoginButton->setObjectName(QStringLiteral("LoginButton"));
        LoginButton->setGeometry(QRect(200, 30, 71, 21));
        LoginButton->setStyleSheet(QStringLiteral("background-color: orange ;border: 1px solid black;"));
        ClientWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ClientWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 22));
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
        NameInput->setText(QString());
        NameLabel->setText(QApplication::translate("ClientWindow", "Your name:", Q_NULLPTR));
        MsgInput->setPlaceholderText(QString());
        label_3->setText(QApplication::translate("ClientWindow", "Peers list", Q_NULLPTR));
        checkBox->setText(QApplication::translate("ClientWindow", "Private account", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        UpdateListButton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        UpdateListButton->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        UpdateListButton->setText(QApplication::translate("ClientWindow", "Update", Q_NULLPTR));
        label->setText(QApplication::translate("ClientWindow", "Message for:", Q_NULLPTR));
        DestName->setText(QString());
        SearchLine->setText(QString());
        label_2->setText(QApplication::translate("ClientWindow", "Search private users:", Q_NULLPTR));
        SearchButton->setText(QApplication::translate("ClientWindow", "Go!", Q_NULLPTR));
        DebugLabel->setText(QString());
        pushButton->setText(QApplication::translate("ClientWindow", "Create Issue", Q_NULLPTR));
        LoginButton->setText(QApplication::translate("ClientWindow", "Log in", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ClientWindow: public Ui_ClientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
