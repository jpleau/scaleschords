QT       += core gui

TARGET = scaleschords

TEMPLATE = subdirs

SUBDIRS = lib app

CONFIG += c++14

app.depends = lib
