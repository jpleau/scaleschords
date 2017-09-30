TEMPLATE = app
TARGET = scaleschords
QT += core widgets

CONFIG += c++14

SOURCES += main.cpp

INCLUDEPATH += ../lib
LIBS += -L../lib/libscaleschords.dll
