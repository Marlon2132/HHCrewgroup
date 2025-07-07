/********************************************************************************
** Form generated from reading UI file 'datetimeinputdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATETIMEINPUTDIALOG_H
#define UI_DATETIMEINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DateTimeInputDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *currentTimeLabel;
    QLabel *numericLabel;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *numericInput;
    QPushButton *currentTimeBtn;
    QLabel *wordsLabel;
    QLabel *wordsOutput;
    QLabel *wordLabel;
    QTextEdit *wordInput;
    QLabel *numericLabel_2;
    QLabel *numericOutput;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *convertButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DateTimeInputDialog)
    {
        if (DateTimeInputDialog->objectName().isEmpty())
            DateTimeInputDialog->setObjectName("DateTimeInputDialog");
        DateTimeInputDialog->resize(500, 450);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(188, 188, 188, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(221, 221, 221, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(94, 94, 94, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(125, 125, 125, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush7(QColor(0, 0, 0, 127));
        brush7.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::Active, QPalette::Accent, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::Inactive, QPalette::Accent, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush8(QColor(94, 94, 94, 127));
        brush8.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        QBrush brush9(QColor(244, 244, 244, 255));
        brush9.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::Disabled, QPalette::Accent, brush9);
#endif
        DateTimeInputDialog->setPalette(palette);
        verticalLayout = new QVBoxLayout(DateTimeInputDialog);
        verticalLayout->setObjectName("verticalLayout");
        currentTimeLabel = new QLabel(DateTimeInputDialog);
        currentTimeLabel->setObjectName("currentTimeLabel");
        currentTimeLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #2c3e50;"));
        currentTimeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        currentTimeLabel->setWordWrap(true);

        verticalLayout->addWidget(currentTimeLabel);

        numericLabel = new QLabel(DateTimeInputDialog);
        numericLabel->setObjectName("numericLabel");

        verticalLayout->addWidget(numericLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        numericInput = new QLineEdit(DateTimeInputDialog);
        numericInput->setObjectName("numericInput");

        horizontalLayout_2->addWidget(numericInput);

        currentTimeBtn = new QPushButton(DateTimeInputDialog);
        currentTimeBtn->setObjectName("currentTimeBtn");

        horizontalLayout_2->addWidget(currentTimeBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        wordsLabel = new QLabel(DateTimeInputDialog);
        wordsLabel->setObjectName("wordsLabel");

        verticalLayout->addWidget(wordsLabel);

        wordsOutput = new QLabel(DateTimeInputDialog);
        wordsOutput->setObjectName("wordsOutput");
        wordsOutput->setWordWrap(true);

        verticalLayout->addWidget(wordsOutput);

        wordLabel = new QLabel(DateTimeInputDialog);
        wordLabel->setObjectName("wordLabel");

        verticalLayout->addWidget(wordLabel);

        wordInput = new QTextEdit(DateTimeInputDialog);
        wordInput->setObjectName("wordInput");

        verticalLayout->addWidget(wordInput);

        numericLabel_2 = new QLabel(DateTimeInputDialog);
        numericLabel_2->setObjectName("numericLabel_2");

        verticalLayout->addWidget(numericLabel_2);

        numericOutput = new QLabel(DateTimeInputDialog);
        numericOutput->setObjectName("numericOutput");

        verticalLayout->addWidget(numericOutput);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        convertButton = new QPushButton(DateTimeInputDialog);
        convertButton->setObjectName("convertButton");

        horizontalLayout->addWidget(convertButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        acceptButton = new QPushButton(DateTimeInputDialog);
        acceptButton->setObjectName("acceptButton");

        horizontalLayout->addWidget(acceptButton);

        cancelButton = new QPushButton(DateTimeInputDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DateTimeInputDialog);

        QMetaObject::connectSlotsByName(DateTimeInputDialog);
    } // setupUi

    void retranslateUi(QDialog *DateTimeInputDialog)
    {
        DateTimeInputDialog->setWindowTitle(QCoreApplication::translate("DateTimeInputDialog", "Dialog", nullptr));
        currentTimeLabel->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \320\262\321\200\320\265\320\274\321\217:", nullptr));
        numericLabel->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\247\320\270\321\201\320\273\320\276\320\262\320\276\320\271 \321\204\320\276\321\200\320\274\320\260\321\202 (\320\224\320\224.\320\234\320\234.\320\223\320\223\320\223\320\223 \320\247\320\247:\320\234\320\234:\320\241\320\241):", nullptr));
        currentTimeBtn->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\241\320\265\320\271\321\207\320\260\321\201", nullptr));
        wordsLabel->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\241\320\273\320\276\320\262\320\265\321\201\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202:", nullptr));
        wordsOutput->setText(QString());
        wordLabel->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\241\320\273\320\276\320\262\320\265\321\201\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202:", nullptr));
        numericLabel_2->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\247\320\270\321\201\320\273\320\276\320\262\320\276\320\271 \321\204\320\276\321\200\320\274\320\260\321\202:", nullptr));
        numericOutput->setText(QString());
        convertButton->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\237\321\200\320\265\320\276\320\261\321\200\320\260\320\267\320\276\320\262\320\260\321\202\321\214", nullptr));
        acceptButton->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\237\321\200\320\270\320\275\321\217\321\202\321\214", nullptr));
        cancelButton->setText(QCoreApplication::translate("DateTimeInputDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DateTimeInputDialog: public Ui_DateTimeInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATETIMEINPUTDIALOG_H
