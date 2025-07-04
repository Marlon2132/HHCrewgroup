QT += core gui network widgets

TARGET = server-app
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

# Настройки
CONFIG += c++11
CONFIG += release
