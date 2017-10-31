/********************************************************************************
** Form generated from reading UI file 'serverwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWINDOW_H
#define UI_SERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWindow
{
public:
    QWidget *centralWidget;
    QTextBrowser *Logs;
    QTextBrowser *RegisteredUsers;
    QPushButton *Starting;
    QPushButton *Stopping;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ServerWindow)
    {
        if (ServerWindow->objectName().isEmpty())
            ServerWindow->setObjectName(QStringLiteral("ServerWindow"));
        ServerWindow->resize(531, 424);
        centralWidget = new QWidget(ServerWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Logs = new QTextBrowser(centralWidget);
        Logs->setObjectName(QStringLiteral("Logs"));
        Logs->setGeometry(QRect(10, 60, 241, 192));
        RegisteredUsers = new QTextBrowser(centralWidget);
        RegisteredUsers->setObjectName(QStringLiteral("RegisteredUsers"));
        RegisteredUsers->setGeometry(QRect(330, 60, 191, 192));
        Starting = new QPushButton(centralWidget);
        Starting->setObjectName(QStringLiteral("Starting"));
        Starting->setGeometry(QRect(230, 310, 113, 32));
        Stopping = new QPushButton(centralWidget);
        Stopping->setObjectName(QStringLiteral("Stopping"));
        Stopping->setGeometry(QRect(360, 310, 113, 32));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 40, 131, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(350, 40, 101, 16));
        ServerWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ServerWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 531, 22));
        ServerWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ServerWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ServerWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ServerWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ServerWindow->setStatusBar(statusBar);

        retranslateUi(ServerWindow);

        QMetaObject::connectSlotsByName(ServerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ServerWindow)
    {
        ServerWindow->setWindowTitle(QApplication::translate("ServerWindow", "ServerWindow", Q_NULLPTR));
        Starting->setText(QApplication::translate("ServerWindow", "Run Server", Q_NULLPTR));
        Stopping->setText(QApplication::translate("ServerWindow", "Stop Server", Q_NULLPTR));
        label->setText(QApplication::translate("ServerWindow", "Server logs", Q_NULLPTR));
        label_2->setText(QApplication::translate("ServerWindow", "Registered users", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ServerWindow: public Ui_ServerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWINDOW_H
