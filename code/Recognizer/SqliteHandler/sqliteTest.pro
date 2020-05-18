QT += core
QT -= gui

CONFIG += c++11
QT += sql
TARGET = sqliteTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    SqliteHandler.cpp

HEADERS += \
    SqliteHandler.h
