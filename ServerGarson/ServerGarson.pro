QT += core gui network widgets

TARGET = garson-server
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

RESOURCES += Students.qrc

CONFIG += c++11
CONFIG += release
