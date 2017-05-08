QT += core
QT -= gui

CONFIG += c++11

TARGET = pickupsticks
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    line.cpp \
    component.cpp

HEADERS += \
    line.h \
    component.h

DISTFILES += \
    sticks.txt

RESOURCES += \
    textfinder.qrc
