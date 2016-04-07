QT += core network
QT -= gui

QT += network
QT += widgets

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


TARGET = Client


SOURCES += main.cpp \
    MyClient.cpp

HEADERS += \
    MyClient.h \
    main.h

