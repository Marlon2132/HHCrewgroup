QT += core gui widgets network

TEMPLATE = app

TARGET = biorythmes_client

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    painter.cpp \
    date.cpp

HEADERS += \
    mainwindow.h \
    painter.h \
    date.h \
    request.h

FORMS += \
    mainwindow.ui
