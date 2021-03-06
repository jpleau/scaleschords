include(../musictest.pri)

TEMPLATE = app
TARGET = scaleschords
QT += core widgets

CONFIG += c++14

SOURCES += main.cpp mainwindow.cpp \
    notecheckbox.cpp

HEADERS += mainwindow.h \
    notecheckbox.h

INCLUDEPATH += ../lib
DEPENDPATH += ../libs

FORMS += mainwindow.ui

unix {
    LIBS += -L../lib -lscaleschords
}

win32 {
    LIBS += -L../lib/debug -lscaleschords
}


target.path = $$PREFIX/bin

desktop.path = $$DATADIR/applications
desktop.files = ../scaleschords.desktop

INSTALLS += target desktop
