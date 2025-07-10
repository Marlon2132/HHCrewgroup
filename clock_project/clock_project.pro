QT       += core gui widgets
CONFIG   += c++17
TARGET    = SoftClock
TEMPLATE  = app

# Исходные файлы
SOURCES += \
    datetimeconverter.cpp \
    datetimeinputdialog.cpp \
    datetimevalidator.cpp \
    main.cpp \
    mainwindow.cpp \
    softwatchwidget.cpp \
    softwatchwidget.cpp \
    datetimeinputdialog.cpp \
    datetimeconverter.cpp \
    datetimevalidator.cpp

HEADERS += \
    datetimeconverter.h \
    datetimeinputdialog.h \
    datetimevalidator.h \
    mainwindow.h \
    softwatchwidget.h \
    softwatchwidget.h \
    datetimeinputdialog.h \
    datetimeconverter.h \
    datetimevalidator.h

FORMS += \
    datetimeinputdialog.ui \
    mainwindow.ui \
    datetimeinputdialog.ui

# Ресурсы (фон для часов)
RESOURCES += resources.qrc \
    resources.qrc
