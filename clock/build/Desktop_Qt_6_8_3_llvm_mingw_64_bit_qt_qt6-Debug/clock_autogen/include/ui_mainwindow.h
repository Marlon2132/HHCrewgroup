/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_3;
    QAction *action_1;
    QAction *action_6;
    QAction *open_stats_action;
    QAction *from_timer_action;
    QAction *manually_action;
    QAction *wordly_action;
    QAction *open_clock_action;
    QAction *open_help_action;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *clockLabel;
    QMenuBar *menubar;
    QMenu *file_menu;
    QMenu *main_menu;
    QMenu *design_menu;
    QMenu *background_menu;
    QMenu *arrow_menu;
    QMenu *music_menu;
    QMenu *stats_menu;
    QMenu *format_menu;
    QMenu *number_format_menu;
    QMenu *help_menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
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
        MainWindow->setPalette(palette);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName("action_3");
        action_1 = new QAction(MainWindow);
        action_1->setObjectName("action_1");
        action_6 = new QAction(MainWindow);
        action_6->setObjectName("action_6");
        open_stats_action = new QAction(MainWindow);
        open_stats_action->setObjectName("open_stats_action");
        from_timer_action = new QAction(MainWindow);
        from_timer_action->setObjectName("from_timer_action");
        manually_action = new QAction(MainWindow);
        manually_action->setObjectName("manually_action");
        wordly_action = new QAction(MainWindow);
        wordly_action->setObjectName("wordly_action");
        open_clock_action = new QAction(MainWindow);
        open_clock_action->setObjectName("open_clock_action");
        open_help_action = new QAction(MainWindow);
        open_help_action->setObjectName("open_help_action");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        clockLabel = new QLabel(centralwidget);
        clockLabel->setObjectName("clockLabel");
        clockLabel->setTextFormat(Qt::TextFormat::PlainText);
        clockLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        clockLabel->setWordWrap(true);

        verticalLayout->addWidget(clockLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        file_menu = new QMenu(menubar);
        file_menu->setObjectName("file_menu");
        main_menu = new QMenu(menubar);
        main_menu->setObjectName("main_menu");
        design_menu = new QMenu(main_menu);
        design_menu->setObjectName("design_menu");
        background_menu = new QMenu(design_menu);
        background_menu->setObjectName("background_menu");
        arrow_menu = new QMenu(design_menu);
        arrow_menu->setObjectName("arrow_menu");
        music_menu = new QMenu(main_menu);
        music_menu->setObjectName("music_menu");
        stats_menu = new QMenu(menubar);
        stats_menu->setObjectName("stats_menu");
        format_menu = new QMenu(menubar);
        format_menu->setObjectName("format_menu");
        number_format_menu = new QMenu(format_menu);
        number_format_menu->setObjectName("number_format_menu");
        help_menu = new QMenu(menubar);
        help_menu->setObjectName("help_menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(file_menu->menuAction());
        menubar->addAction(main_menu->menuAction());
        menubar->addAction(stats_menu->menuAction());
        menubar->addAction(format_menu->menuAction());
        menubar->addAction(help_menu->menuAction());
        file_menu->addAction(open_clock_action);
        main_menu->addAction(design_menu->menuAction());
        main_menu->addAction(music_menu->menuAction());
        design_menu->addAction(background_menu->menuAction());
        design_menu->addAction(arrow_menu->menuAction());
        background_menu->addAction(action_3);
        arrow_menu->addAction(action_1);
        music_menu->addAction(action_6);
        stats_menu->addAction(open_stats_action);
        format_menu->addAction(number_format_menu->menuAction());
        format_menu->addAction(wordly_action);
        number_format_menu->addAction(from_timer_action);
        number_format_menu->addAction(manually_action);
        help_menu->addAction(open_help_action);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\213 \320\224\320\260\320\273\320\270", nullptr));
        action_3->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\217\321\216\321\211\320\270\320\271\321\201\321\217", nullptr));
        action_1->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\321\200\320\265\320\273\320\272\320\260 1", nullptr));
        action_6->setText(QCoreApplication::translate("MainWindow", "\320\234\321\203\320\267\321\213\320\272\320\260 1", nullptr));
        open_stats_action->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\201\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\321\203", nullptr));
        from_timer_action->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267 \321\202\320\260\320\271\320\274\320\265\321\200\320\260", nullptr));
        manually_action->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\321\203\321\207\320\275\321\203\321\216", nullptr));
        wordly_action->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\276\320\262\320\265\321\201\320\275\321\213\320\271", nullptr));
        open_clock_action->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\207\320\260\321\201\321\213", nullptr));
        open_help_action->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\277\320\276\320\274\320\276\321\211\321\214", nullptr));
        clockLabel->setText(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\213 \320\261\321\203\320\264\321\203\321\202 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214\321\201\321\217 \320\267\320\264\320\265\321\201\321\214", nullptr));
        file_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        main_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\223\320\273\320\260\320\262\320\275\320\260\321\217", nullptr));
        design_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\267\320\260\320\271\320\275", nullptr));
        background_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\276\320\275", nullptr));
        arrow_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\270\320\273\321\214 \321\201\321\202\321\200\320\265\320\273\320\276\320\272", nullptr));
        music_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\234\321\203\320\267\321\213\320\272\320\260", nullptr));
        stats_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        format_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260\321\202", nullptr));
        number_format_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\247\320\270\321\201\320\273\320\276\320\262\320\276\320\271", nullptr));
        help_menu->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\276\321\211\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
