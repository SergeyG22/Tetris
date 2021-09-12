include(gtest_dependency.pri)

QT       += core gui

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt
INCLUDEPATH += ../

HEADERS += \
        ../i.h \
        ../shape.h \
        tst_test.h

SOURCES += \
        ../i.cpp \
        main.cpp
