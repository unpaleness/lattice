#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T11:49:06
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = lattice
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    fragment.cpp \
    lattice.cpp \
    control.cpp

HEADERS += \
    fragment.h \
    lattice.h \
    control.h
