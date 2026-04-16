/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *settingsBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *pageIdLineEdit;
    QLabel *label_2;
    QLineEdit *accessTokenLineEdit;
    QPushButton *saveSettingsButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *postsLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *addPostButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *scheduleAllButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        settingsBox = new QGroupBox(centralwidget);
        settingsBox->setObjectName("settingsBox");
        gridLayout = new QGridLayout(settingsBox);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(settingsBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pageIdLineEdit = new QLineEdit(settingsBox);
        pageIdLineEdit->setObjectName("pageIdLineEdit");

        gridLayout->addWidget(pageIdLineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(settingsBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        accessTokenLineEdit = new QLineEdit(settingsBox);
        accessTokenLineEdit->setObjectName("accessTokenLineEdit");
        accessTokenLineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(accessTokenLineEdit, 1, 1, 1, 1);

        saveSettingsButton = new QPushButton(settingsBox);
        saveSettingsButton->setObjectName("saveSettingsButton");

        gridLayout->addWidget(saveSettingsButton, 2, 1, 1, 1);


        verticalLayout_2->addWidget(settingsBox);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 580, 419));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName("verticalLayout_3");
        postsLayout = new QVBoxLayout();
        postsLayout->setObjectName("postsLayout");

        verticalLayout_3->addLayout(postsLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addPostButton = new QPushButton(centralwidget);
        addPostButton->setObjectName("addPostButton");

        horizontalLayout->addWidget(addPostButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        scheduleAllButton = new QPushButton(centralwidget);
        scheduleAllButton->setObjectName("scheduleAllButton");

        horizontalLayout->addWidget(scheduleAllButton);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        settingsBox->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Page ID:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Access Token:", nullptr));
        saveSettingsButton->setText(QCoreApplication::translate("MainWindow", "Save Settings", nullptr));
        addPostButton->setText(QCoreApplication::translate("MainWindow", "Add New Post", nullptr));
        scheduleAllButton->setText(QCoreApplication::translate("MainWindow", "Schedule All Posts", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
