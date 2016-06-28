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
    pieceblock.cpp \
    puzzlecontainer.cpp \
    piecelocationcontainer.cpp \
    canvasprinter.cpp \
    printableblock.cpp \
    printablepiece.cpp \
    piececreator.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    puzzlecontainer.h \
    puzzlepiece.h \
    pieceblock.h \
    coordinates.h \
    piecelocationcontainer.h \
    canvasprinter.hpp \
    printableblock.h \
    printablepiece.h \
    piececreator.h
