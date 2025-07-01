/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_3;
    QAction *action_4;
    QAction *standartFormat;
    QAction *textFormat;
    QAction *reverseFormat;
    QAction *physShowSwitch;
    QAction *psychoShowSwitcch;
    QAction *intellShowSwitch;
    QAction *setCurrDate;
    QAction *action_2;
    QAction *action;
    QAction *action_5;
    QAction *maxLineSwitch;
    QAction *maxCrossSwitch;
    QAction *minLineSwitch;
    QAction *minCrossSwitch;
    QAction *nullSwitch;
    QAction *critMinSwitch;
    QAction *critMaxSwitch;
    QAction *critNullSwitch;
    QAction *action_8;
    QAction *cursorTrackingSwitch;
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *birthdayLabelName;
    QLabel *physBiorythmName;
    QLabel *currDayLabelName;
    QLabel *psychoBiorythmName;
    QLabel *birthdayLabel;
    QLineEdit *currDayLineEdit;
    QLineEdit *birthdayLineEdit;
    QLabel *intellBiorythmName;
    QLabel *physBiorythm;
    QLabel *currDayLabel;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *psychoBiorythm;
    QPushButton *buildGraphic;
    QLabel *intellBiorythm;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 550);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName("action_3");
        action_3->setCheckable(true);
        action_4 = new QAction(MainWindow);
        action_4->setObjectName("action_4");
        standartFormat = new QAction(MainWindow);
        standartFormat->setObjectName("standartFormat");
        standartFormat->setCheckable(true);
        standartFormat->setChecked(true);
        textFormat = new QAction(MainWindow);
        textFormat->setObjectName("textFormat");
        textFormat->setCheckable(true);
        reverseFormat = new QAction(MainWindow);
        reverseFormat->setObjectName("reverseFormat");
        reverseFormat->setCheckable(true);
        physShowSwitch = new QAction(MainWindow);
        physShowSwitch->setObjectName("physShowSwitch");
        physShowSwitch->setCheckable(true);
        physShowSwitch->setChecked(true);
        psychoShowSwitcch = new QAction(MainWindow);
        psychoShowSwitcch->setObjectName("psychoShowSwitcch");
        psychoShowSwitcch->setCheckable(true);
        psychoShowSwitcch->setChecked(true);
        intellShowSwitch = new QAction(MainWindow);
        intellShowSwitch->setObjectName("intellShowSwitch");
        intellShowSwitch->setCheckable(true);
        intellShowSwitch->setChecked(true);
        setCurrDate = new QAction(MainWindow);
        setCurrDate->setObjectName("setCurrDate");
        action_2 = new QAction(MainWindow);
        action_2->setObjectName("action_2");
        action = new QAction(MainWindow);
        action->setObjectName("action");
        action->setCheckable(true);
        action->setChecked(true);
        action_5 = new QAction(MainWindow);
        action_5->setObjectName("action_5");
        action_5->setCheckable(true);
        maxLineSwitch = new QAction(MainWindow);
        maxLineSwitch->setObjectName("maxLineSwitch");
        maxLineSwitch->setCheckable(true);
        maxCrossSwitch = new QAction(MainWindow);
        maxCrossSwitch->setObjectName("maxCrossSwitch");
        maxCrossSwitch->setCheckable(true);
        minLineSwitch = new QAction(MainWindow);
        minLineSwitch->setObjectName("minLineSwitch");
        minLineSwitch->setCheckable(true);
        minCrossSwitch = new QAction(MainWindow);
        minCrossSwitch->setObjectName("minCrossSwitch");
        minCrossSwitch->setCheckable(true);
        nullSwitch = new QAction(MainWindow);
        nullSwitch->setObjectName("nullSwitch");
        nullSwitch->setCheckable(true);
        critMinSwitch = new QAction(MainWindow);
        critMinSwitch->setObjectName("critMinSwitch");
        critMinSwitch->setCheckable(true);
        critMaxSwitch = new QAction(MainWindow);
        critMaxSwitch->setObjectName("critMaxSwitch");
        critMaxSwitch->setCheckable(true);
        critNullSwitch = new QAction(MainWindow);
        critNullSwitch->setObjectName("critNullSwitch");
        critNullSwitch->setCheckable(true);
        action_8 = new QAction(MainWindow);
        action_8->setObjectName("action_8");
        action_8->setCheckable(true);
        action_8->setChecked(true);
        cursorTrackingSwitch = new QAction(MainWindow);
        cursorTrackingSwitch->setObjectName("cursorTrackingSwitch");
        cursorTrackingSwitch->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(600, 300));
        centralwidget->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        centralwidget->setTabletTracking(false);
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        birthdayLabelName = new QLabel(centralwidget);
        birthdayLabelName->setObjectName("birthdayLabelName");
        birthdayLabelName->setMaximumSize(QSize(175, 25));

        gridLayout_4->addWidget(birthdayLabelName, 0, 0, 1, 1);

        physBiorythmName = new QLabel(centralwidget);
        physBiorythmName->setObjectName("physBiorythmName");
        physBiorythmName->setMaximumSize(QSize(200, 16777215));

        gridLayout_4->addWidget(physBiorythmName, 0, 3, 1, 1);

        currDayLabelName = new QLabel(centralwidget);
        currDayLabelName->setObjectName("currDayLabelName");
        currDayLabelName->setMaximumSize(QSize(175, 25));

        gridLayout_4->addWidget(currDayLabelName, 2, 0, 1, 1);

        psychoBiorythmName = new QLabel(centralwidget);
        psychoBiorythmName->setObjectName("psychoBiorythmName");
        psychoBiorythmName->setMaximumSize(QSize(200, 16777215));

        gridLayout_4->addWidget(psychoBiorythmName, 1, 3, 1, 1);

        birthdayLabel = new QLabel(centralwidget);
        birthdayLabel->setObjectName("birthdayLabel");

        gridLayout_4->addWidget(birthdayLabel, 0, 1, 1, 1);

        currDayLineEdit = new QLineEdit(centralwidget);
        currDayLineEdit->setObjectName("currDayLineEdit");
        currDayLineEdit->setMaximumSize(QSize(600, 16777215));

        gridLayout_4->addWidget(currDayLineEdit, 3, 0, 1, 2);

        birthdayLineEdit = new QLineEdit(centralwidget);
        birthdayLineEdit->setObjectName("birthdayLineEdit");
        birthdayLineEdit->setMaximumSize(QSize(600, 16777215));

        gridLayout_4->addWidget(birthdayLineEdit, 1, 0, 1, 2);

        intellBiorythmName = new QLabel(centralwidget);
        intellBiorythmName->setObjectName("intellBiorythmName");
        intellBiorythmName->setMaximumSize(QSize(200, 16777215));

        gridLayout_4->addWidget(intellBiorythmName, 2, 3, 1, 1);

        physBiorythm = new QLabel(centralwidget);
        physBiorythm->setObjectName("physBiorythm");
        physBiorythm->setMinimumSize(QSize(50, 0));
        physBiorythm->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(physBiorythm, 0, 4, 1, 1);

        currDayLabel = new QLabel(centralwidget);
        currDayLabel->setObjectName("currDayLabel");

        gridLayout_4->addWidget(currDayLabel, 2, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");

        gridLayout_4->addLayout(gridLayout, 4, 0, 1, 6);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(27, 0));
        label->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_4->addWidget(label, 0, 2, 1, 1);

        psychoBiorythm = new QLabel(centralwidget);
        psychoBiorythm->setObjectName("psychoBiorythm");
        psychoBiorythm->setMinimumSize(QSize(50, 0));
        psychoBiorythm->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(psychoBiorythm, 1, 4, 1, 1);

        buildGraphic = new QPushButton(centralwidget);
        buildGraphic->setObjectName("buildGraphic");
        buildGraphic->setMinimumSize(QSize(140, 0));
        buildGraphic->setMaximumSize(QSize(140, 16777215));

        gridLayout_4->addWidget(buildGraphic, 0, 5, 4, 1);

        intellBiorythm = new QLabel(centralwidget);
        intellBiorythm->setObjectName("intellBiorythm");
        intellBiorythm->setMinimumSize(QSize(50, 0));
        intellBiorythm->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(intellBiorythm, 2, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(70, 25));
        pushButton->setMaximumSize(QSize(70, 25));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(70, 25));
        pushButton_2->setMaximumSize(QSize(70, 25));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout_4->addLayout(horizontalLayout, 3, 3, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName("menu_4");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menu->addSeparator();
        menu->addAction(setCurrDate);
        menu->addSeparator();
        menu->addAction(action_5);
        menu->addAction(cursorTrackingSwitch);
        menu->addAction(action);
        menu->addAction(action_3);
        menu->addSeparator();
        menu->addAction(action_2);
        menu->addSeparator();
        menu->addAction(action_4);
        menu_2->addSeparator();
        menu_2->addAction(standartFormat);
        menu_2->addAction(textFormat);
        menu_2->addAction(reverseFormat);
        menu_3->addAction(physShowSwitch);
        menu_3->addAction(psychoShowSwitcch);
        menu_3->addAction(intellShowSwitch);
        menu_4->addAction(maxLineSwitch);
        menu_4->addAction(maxCrossSwitch);
        menu_4->addAction(minLineSwitch);
        menu_4->addAction(minCrossSwitch);
        menu_4->addAction(nullSwitch);
        menu_4->addAction(critMinSwitch);
        menu_4->addAction(critMaxSwitch);
        menu_4->addAction(critNullSwitch);
        menu_4->addAction(action_8);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\275\320\276\321\215\320\272\321\200\320\260\320\275\320\275\321\213\320\271 \321\200\320\265\320\266\320\270\320\274", nullptr));
        action_4->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        standartFormat->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\321\213\320\271", nullptr));
        textFormat->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271", nullptr));
        reverseFormat->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\321\202\320\275\321\213\320\271 \"\320\260\320\274\320\265\321\200\320\270\320\272\320\260\320\275\321\201\320\272\320\270\320\271\"", nullptr));
        physShowSwitch->setText(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\267\320\270\320\276\320\273\320\276\320\263\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\261\320\270\320\276\321\200\320\270\321\202\320\274", nullptr));
        psychoShowSwitcch->setText(QCoreApplication::translate("MainWindow", "\320\237\321\201\320\270\321\205\320\276\320\273\320\276\320\263\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\261\320\270\320\276\321\200\320\270\321\202\320\274", nullptr));
        intellShowSwitch->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\320\273\320\273\320\265\320\272\321\202\321\203\320\260\320\273\321\214\320\275\321\213\320\271 \320\261\320\270\320\276\321\200\320\270\321\202\320\274", nullptr));
        setCurrDate->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \321\201\320\265\320\263\320\276\320\264\320\275\321\217\321\210\320\275\321\216\321\216 \320\264\320\260\321\202\321\203", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\241\320\263\320\273\320\260\320\266\320\270\320\262\320\260\320\275\320\270\320\265", nullptr));
        action_5->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\320\273\321\201\321\202\321\213\320\265 \320\273\320\270\320\275\320\270\320\270 \320\261\320\270\320\276\321\200\320\270\321\202\320\274\320\276\320\262", nullptr));
        maxLineSwitch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\320\270 \320\274\320\260\320\272\321\201\320\270\320\274\321\203\320\274\320\260 \320\277\321\200\321\217\320\274\321\213\320\274\320\270", nullptr));
        maxCrossSwitch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\320\270 \320\274\320\260\320\272\321\201\320\270\320\274\321\203\320\274\320\260 \320\272\321\200\320\265\321\201\321\202\320\260\320\274\320\270", nullptr));
        minLineSwitch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\320\270 \320\274\320\270\320\275\320\270\320\274\321\203\320\274\320\260 \320\277\321\200\321\217\320\274\321\213\320\274\320\270", nullptr));
        minCrossSwitch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\320\270 \320\274\320\270\320\275\320\270\320\274\321\203\320\274\320\260 \320\272\321\200\320\265\321\201\321\202\320\260\320\274\320\270", nullptr));
        nullSwitch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\320\270 \320\275\320\265\321\203\321\201\321\202\320\276\320\271\321\207\320\270\320\262\320\276\321\201\321\202\320\270 \320\276\320\272\321\200\321\203\320\266\320\275\320\276\321\201\321\202\321\217\320\274\320\270", nullptr));
        critMinSwitch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \320\272\321\200\320\270\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\274\320\270\320\275\320\270\320\274\321\203\320\274\321\213", nullptr));
        critMaxSwitch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \320\272\321\200\320\270\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\274\320\260\320\272\321\201\320\270\320\274\321\203\320\274\321\213", nullptr));
        critNullSwitch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\320\270 \320\272\321\200\320\270\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\271 \320\275\320\265\321\203\321\201\321\202\320\276\320\271\321\207\320\270\320\262\320\276\321\201\321\202\320\270", nullptr));
        action_8->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \320\264\320\260\321\202\321\203 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        cursorTrackingSwitch->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\201\320\273\320\265\320\266\320\270\320\262\320\260\320\275\320\270\320\265 \320\272\321\203\321\200\321\201\320\276\321\200\320\260", nullptr));
        birthdayLabelName->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\321\202\321\203 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217:", nullptr));
        physBiorythmName->setText(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\267\320\270\320\276\320\273\320\276\320\263\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\261\320\270\320\276\321\200\320\270\321\202\320\274", nullptr));
        currDayLabelName->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\321\202\321\203 \320\264\320\273\321\217 \321\200\320\260\321\201\321\207\320\265\321\202\320\260:", nullptr));
        psychoBiorythmName->setText(QCoreApplication::translate("MainWindow", "\320\237\321\201\320\270\321\205\320\276\320\273\320\276\320\263\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\261\320\270\320\276\321\200\320\270\321\202\320\274", nullptr));
        birthdayLabel->setText(QString());
        intellBiorythmName->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\320\273\320\273\320\265\320\272\321\202\321\203\320\260\320\273\321\214\320\275\321\213\320\271 \320\261\320\270\320\276\321\200\320\270\321\202\320\274", nullptr));
        physBiorythm->setText(QString());
        currDayLabel->setText(QString());
        label->setText(QString());
        psychoBiorythm->setText(QString());
        buildGraphic->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        intellBiorythm->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260\321\202 \320\262\320\262\320\276\320\264\320\260-\320\262\321\213\320\262\320\276\320\264\320\260", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\261\320\270\320\276\321\200\320\270\321\202\320\274\321\213", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\320\232\321\200\320\270\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \321\202\320\276\321\207\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
