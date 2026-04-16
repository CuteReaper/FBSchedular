/********************************************************************************
** Form generated from reading UI file 'postwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTWIDGET_H
#define UI_POSTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PostWidget
{
public:
    QGridLayout *gridLayout;
    QRadioButton *photoRadioButton;
    QRadioButton *videoRadioButton;
    QDateTimeEdit *dateTimePicker;
    QLabel *previewLabel;
    QLineEdit *filePathLineEdit;
    QPushButton *browseButton;
    QTextEdit *descriptionTextEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *removeButton;

    void setupUi(QWidget *PostWidget)
    {
        if (PostWidget->objectName().isEmpty())
            PostWidget->setObjectName("PostWidget");
        PostWidget->resize(530, 250);
        gridLayout = new QGridLayout(PostWidget);
        gridLayout->setObjectName("gridLayout");
        photoRadioButton = new QRadioButton(PostWidget);
        photoRadioButton->setObjectName("photoRadioButton");
        photoRadioButton->setChecked(true);

        gridLayout->addWidget(photoRadioButton, 0, 0, 1, 1);

        videoRadioButton = new QRadioButton(PostWidget);
        videoRadioButton->setObjectName("videoRadioButton");

        gridLayout->addWidget(videoRadioButton, 0, 1, 1, 1);

        dateTimePicker = new QDateTimeEdit(PostWidget);
        dateTimePicker->setObjectName("dateTimePicker");
        dateTimePicker->setCalendarPopup(true);

        gridLayout->addWidget(dateTimePicker, 0, 2, 1, 1);

        previewLabel = new QLabel(PostWidget);
        previewLabel->setObjectName("previewLabel");
        previewLabel->setMinimumSize(QSize(150, 150));
        previewLabel->setMaximumSize(QSize(150, 150));
        previewLabel->setStyleSheet(QString::fromUtf8("background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 4px;"));
        previewLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(previewLabel, 0, 3, 3, 1);

        filePathLineEdit = new QLineEdit(PostWidget);
        filePathLineEdit->setObjectName("filePathLineEdit");

        gridLayout->addWidget(filePathLineEdit, 1, 0, 1, 2);

        browseButton = new QPushButton(PostWidget);
        browseButton->setObjectName("browseButton");

        gridLayout->addWidget(browseButton, 1, 2, 1, 1);

        descriptionTextEdit = new QTextEdit(PostWidget);
        descriptionTextEdit->setObjectName("descriptionTextEdit");

        gridLayout->addWidget(descriptionTextEdit, 2, 0, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        removeButton = new QPushButton(PostWidget);
        removeButton->setObjectName("removeButton");

        horizontalLayout->addWidget(removeButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 4);


        retranslateUi(PostWidget);

        QMetaObject::connectSlotsByName(PostWidget);
    } // setupUi

    void retranslateUi(QWidget *PostWidget)
    {
        PostWidget->setWindowTitle(QCoreApplication::translate("PostWidget", "Post", nullptr));
        photoRadioButton->setText(QCoreApplication::translate("PostWidget", "Photo", nullptr));
        videoRadioButton->setText(QCoreApplication::translate("PostWidget", "Video / Reel", nullptr));
        previewLabel->setText(QCoreApplication::translate("PostWidget", "Media Preview", nullptr));
        filePathLineEdit->setPlaceholderText(QCoreApplication::translate("PostWidget", "Click 'Browse' to select a file...", nullptr));
        browseButton->setText(QCoreApplication::translate("PostWidget", "Browse...", nullptr));
        descriptionTextEdit->setPlaceholderText(QCoreApplication::translate("PostWidget", "Enter your post description or caption here...", nullptr));
        removeButton->setText(QCoreApplication::translate("PostWidget", "Remove This Post", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PostWidget: public Ui_PostWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTWIDGET_H
