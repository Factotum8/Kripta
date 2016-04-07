QT += core network
#QT -= gui
QT += network
QT += widgets

CONFIG += console
CONFIG -= app_bundle

#QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


TARGET = Server


SOURCES += main.cpp \
    SslServer.cpp \
    MyServer.cpp

HEADERS += \
    SslServer.h \
    MyServer.h \
    main.h
HEADERS += \
    main.h \
    MyServer.h

