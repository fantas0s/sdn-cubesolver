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
    puzzlepiece.cpp

HEADERS += \
    canvasprinter.hpp \
    coordinates.h \
    pieceblock.h \
    piecelocationcontainer.h \
    puzzlecontainer.h \
    puzzlepiece.h
