QT += core
QT -= gui

CONFIG += c++11

TARGET = CubeSolver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    cubesolver.cpp \
    canvasprinter.cpp \
    pieceblock.cpp \
    piecelocationcontainer.cpp \
    puzzlecontainer.cpp \
    puzzlepiece.cpp \
    printableblock.cpp \
    printablepiece.cpp \
    piececreator.cpp

HEADERS += \
    canvasprinter.hpp \
    coordinates.h \
    pieceblock.h \
    piecelocationcontainer.h \
    puzzlecontainer.h \
    puzzlepiece.h \
    printableblock.h \
    printablepiece.h \
    piececreator.h
