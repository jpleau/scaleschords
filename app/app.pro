TEMPLATE = app
TARGET = scaleschords
QT += core widgets

CONFIG += c++14

SOURCES += main.cpp mainwindow.cpp

HEADERS += mainwindow.h

INCLUDEPATH += ../lib
DEPENDPATH += ../libs

FORMS += mainwindow.ui

unix {
    LIBS += -L../lib -lscaleschords
}

win32 {
    LIBS += -L../lib/release -lscaleschords
}
