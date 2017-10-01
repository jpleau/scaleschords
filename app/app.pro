TEMPLATE = app
TARGET = scaleschords
QT += core widgets

CONFIG += c++14

SOURCES += main.cpp

INCLUDEPATH += ../lib
DEPENDPATH += ../libs

unix {
    LIBS += -L../lib -lscaleschords
}

win32 {
    LIBS += -L../lib/debug -lscaleschords
}
