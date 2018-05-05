include(../musictest.pri)

TEMPLATE = lib
TARGET = scaleschords

QT += core

HEADERS += chord.h note.h scale.h database.h intervals.h
SOURCES += chord.cpp note.cpp scale.cpp database.cpp

target.path = $$PREFIX/lib

INSTALLS += target
