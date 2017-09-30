QT       += core gui

TARGET = scaleschords

TEMPLATE = subdirs

SUBDIRS = lib app

CONFIG += c++14

SOURCES += \
        main.cpp

HEADERS +=

FORMS +=

app.depends = lib
