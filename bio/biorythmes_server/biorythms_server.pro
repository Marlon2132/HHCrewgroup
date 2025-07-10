# Файл проекта qmake
QT       += widgets network
TARGET    = biorythms_take5
TEMPLATE  = app
CONFIG   += c++17

# Автоматическая обработка Qt-специфичных файлов
CONFIG += qt warn_on release
CONFIG += uic moc

# Исходные файлы
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    date.cpp \
    painter.cpp \
    server.cpp

HEADERS += \
    mainwindow.h \
    date.h \
    painter.h \
    server.h \
    records.h

FORMS += \
    mainwindow.ui

# Настройки для macOS
macx {
    CONFIG += app_bundle
    QMAKE_INFO_PLIST = Info.plist
    TARGET = $$join(TARGET,,,"")
    BUNDLE_IDENTIFIER = com.example.biorythms_take5
    VERSION = 0.1
    SHORT_VERSION = 0.1
    ICON = 
}

# Настройки для Windows
#win32 {
 #   RC_ICONS = app.ico
  #  VERSION = 0.1.0
#2}

# Флаги компилятора
QMAKE_CXXFLAGS += -std=c++17
