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

#QMAKE_CXX = mpic++

INCLUDEPATH += "/usr/lib/mpich/include"

#LIBS += "C:/Program Files (x86)/MPICH2/lib/mpi.lib"

#QMAKE_CXXFLAGS += $$system(mpic++ --showme:compile) -std=c++11
#QMAKE_LFLAGS += $$system(mpic++ --showme:link)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    fragment.cpp \
    control.cpp

HEADERS += \
    fragment.h \
    control.h
