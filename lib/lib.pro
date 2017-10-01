TARGET = scaleschords
TEMPLATE = lib


QT += core

HEADERS += chord.h note.h scale.h \
    database.h
SOURCES += chord.cpp note.cpp scale.cpp \
    database.cpp
