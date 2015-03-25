#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T18:22:11
#
#-------------------------------------------------

QT       -= gui

TARGET = FirstLab
TEMPLATE = lib

DEFINES += FIRSTLAB_LIBRARY

CONFIG += c++11

SOURCES += stack.cpp \
    Native_Interface.cpp

HEADERS += stack.h\
        firstlab_global.h \
    Native_Interface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
