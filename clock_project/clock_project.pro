QT       += core gui widgets
CONFIG   += c++17
TEMPLATE  = app
TARGET    = SoftClock

# Исходные исходники
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    softwatchwidget.cpp \
    datetimeconverter.cpp \
    datetimeinputdialog.cpp \
    datetimevalidator.cpp

# Заголовки
HEADERS += \
    mainwindow.h \
    softwatchwidget.h \
    datetimeconverter.h \
    datetimeinputdialog.h \
    datetimevalidator.h

# Файлы форм UI
FORMS += \
    mainwindow.ui \
    datetimeinputdialog.ui

# Ресурсный файл
RESOURCES += \
    resources.qrc
