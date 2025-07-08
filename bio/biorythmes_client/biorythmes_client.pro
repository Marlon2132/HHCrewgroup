QT += core gui widgets network
QT += core5compat
CONFIG += c++17
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = biorythms_client

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    plotter.cpp

HEADERS += \
    mainwindow.h \
    plotter.h \
    request.h

FORMS += \
    mainwindow.ui

CONFIG += c++17
win32:msvc* {
    QMAKE_CXXFLAGS += /MP
    CONFIG += console
}
