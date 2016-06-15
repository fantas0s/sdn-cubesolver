#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T13:16:30
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_sdncubesolvertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_sdncubesolvertest.cpp \
    puzzlepiece.cpp \
    pieceblock.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    puzzlecontainer.h \
    puzzlepiece.h \
    pieceblock.h
