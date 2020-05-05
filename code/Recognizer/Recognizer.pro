#-------------------------------------------------
#
# Project created by QtCreator 2020-05-05T16:53:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Recognizer
TEMPLATE = app


SOURCES += main.cpp\
        Recognizer.cpp \
    RecognizerUI.cpp \
    RecognizerAlgorithm.cpp \
    DrawingBoard.cpp

HEADERS  += Recognizer.h \
    RecognizerUI.h \
    RecognizerAlgorithm.h \
    IRecognizer.h \
    DrawingBoard.h
