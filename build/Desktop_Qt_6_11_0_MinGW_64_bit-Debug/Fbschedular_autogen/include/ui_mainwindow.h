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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QGroupBox *credentialsBox;
    QGridLayout *credentialsLayout;
    QLabel *label_token;
    QLineEdit *accessTokenLineEdit;
    QPushButton *fetchPagesButton;
    QLabel *label_page;
    QComboBox *pageComboBox;
    QLabel *label_pageid;
    QLineEdit *pageIdLineEdit;
    QPushButton *saveSettingsButton;
    QGroupBox *scheduleBox;
    QGridLayout *scheduleLayout;
    QLabel *label_start;
    QDateTimeEdit *startDateTimeEdit;
    QLabel *label_interval;
    QComboBox *strategyComboBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *postsLayout;
    QTextEdit *logTextEdit;
    QHBoxLayout *bottomButtons;
    QPushButton *addPostButton;
    QPushButton *bulkAddButton;
    QSpacerItem *spacer;
    QPushButton *scheduleAllButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(650, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        credentialsBox = new QGroupBox(centralwidget);
        credentialsBox->setObjectName("credentialsBox");
        credentialsLayout = new QGridLayout(credentialsBox);
        credentialsLayout->setObjectName("credentialsLayout");
        label_token = new QLabel(credentialsBox);
        label_token->setObjectName("label_token");

        credentialsLayout->addWidget(label_token, 0, 0, 1, 1);

        accessTokenLineEdit = new QLineEdit(credentialsBox);
        accessTokenLineEdit->setObjectName("accessTokenLineEdit");
        accessTokenLineEdit->setEchoMode(QLineEdit::Password);

        credentialsLayout->addWidget(accessTokenLineEdit, 0, 1, 1, 1);

        fetchPagesButton = new QPushButton(credentialsBox);
        fetchPagesButton->setObjectName("fetchPagesButton");

        credentialsLayout->addWidget(fetchPagesButton, 0, 2, 1, 1);

        label_page = new QLabel(credentialsBox);
        label_page->setObjectName("label_page");

        credentialsLayout->addWidget(label_page, 1, 0, 1, 1);

        pageComboBox = new QComboBox(credentialsBox);
        pageComboBox->setObjectName("pageComboBox");

        credentialsLayout->addWidget(pageComboBox, 1, 1, 1, 2);

        label_pageid = new QLabel(credentialsBox);
        label_pageid->setObjectName("label_pageid");

        credentialsLayout->addWidget(label_pageid, 2, 0, 1, 1);

        pageIdLineEdit = new QLineEdit(credentialsBox);
        pageIdLineEdit->setObjectName("pageIdLineEdit");

        credentialsLayout->addWidget(pageIdLineEdit, 2, 1, 1, 2);

        saveSettingsButton = new QPushButton(credentialsBox);
        saveSettingsButton->setObjectName("saveSettingsButton");

        credentialsLayout->addWidget(saveSettingsButton, 3, 1, 1, 1);


        mainLayout->addWidget(credentialsBox);

        scheduleBox = new QGroupBox(centralwidget);
        scheduleBox->setObjectName("scheduleBox");
        scheduleLayout = new QGridLayout(scheduleBox);
        scheduleLayout->setObjectName("scheduleLayout");
        label_start = new QLabel(scheduleBox);
        label_start->setObjectName("label_start");

        scheduleLayout->addWidget(label_start, 0, 0, 1, 1);

        startDateTimeEdit = new QDateTimeEdit(scheduleBox);
        startDateTimeEdit->setObjectName("startDateTimeEdit");
        startDateTimeEdit->setCalendarPopup(true);

        scheduleLayout->addWidget(startDateTimeEdit, 0, 1, 1, 1);

        label_interval = new QLabel(scheduleBox);
        label_interval->setObjectName("label_interval");

        scheduleLayout->addWidget(label_interval, 1, 0, 1, 1);

        strategyComboBox = new QComboBox(scheduleBox);
        strategyComboBox->addItem(QString());
        strategyComboBox->addItem(QString());
        strategyComboBox->addItem(QString());
        strategyComboBox->addItem(QString());
        strategyComboBox->setObjectName("strategyComboBox");

        scheduleLayout->addWidget(strategyComboBox, 1, 1, 1, 1);


        mainLayout->addWidget(scheduleBox);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        postsLayout = new QVBoxLayout(scrollAreaWidgetContents);
        postsLayout->setObjectName("postsLayout");
        scrollArea->setWidget(scrollAreaWidgetContents);

        mainLayout->addWidget(scrollArea);

        logTextEdit = new QTextEdit(centralwidget);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setReadOnly(true);
        logTextEdit->setMaximumSize(QSize(16777215, 120));

        mainLayout->addWidget(logTextEdit);

        bottomButtons = new QHBoxLayout();
        bottomButtons->setObjectName("bottomButtons");
        addPostButton = new QPushButton(centralwidget);
        addPostButton->setObjectName("addPostButton");

        bottomButtons->addWidget(addPostButton);

        bulkAddButton = new QPushButton(centralwidget);
        bulkAddButton->setObjectName("bulkAddButton");

        bottomButtons->addWidget(bulkAddButton);

        spacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bottomButtons->addItem(spacer);

        scheduleAllButton = new QPushButton(centralwidget);
        scheduleAllButton->setObjectName("scheduleAllButton");

        bottomButtons->addWidget(scheduleAllButton);


        mainLayout->addLayout(bottomButtons);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Facebook Bulk Scheduler", nullptr));
        credentialsBox->setTitle(QCoreApplication::translate("MainWindow", "API Credentials", nullptr));
        label_token->setText(QCoreApplication::translate("MainWindow", "Access Token:", nullptr));
        fetchPagesButton->setText(QCoreApplication::translate("MainWindow", "Fetch Pages", nullptr));
        label_page->setText(QCoreApplication::translate("MainWindow", "Select Page:", nullptr));
        label_pageid->setText(QCoreApplication::translate("MainWindow", "Page ID:", nullptr));
        saveSettingsButton->setText(QCoreApplication::translate("MainWindow", "Save Credentials", nullptr));
        scheduleBox->setTitle(QCoreApplication::translate("MainWindow", "Scheduling Settings", nullptr));
        label_start->setText(QCoreApplication::translate("MainWindow", "Start Time:", nullptr));
        label_interval->setText(QCoreApplication::translate("MainWindow", "Interval:", nullptr));
        strategyComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Manual (Use individual times)", nullptr));
        strategyComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Hourly", nullptr));
        strategyComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Daily", nullptr));
        strategyComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Twice a Day (Every 12h)", nullptr));

        addPostButton->setText(QCoreApplication::translate("MainWindow", "Add New Post", nullptr));
        bulkAddButton->setText(QCoreApplication::translate("MainWindow", "Bulk Add Media", nullptr));
        scheduleAllButton->setText(QCoreApplication::translate("MainWindow", "Schedule All Posts", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
