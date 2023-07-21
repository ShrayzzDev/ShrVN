QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++20

TEMPLATE = app

include(../../3rdparty/catch/catch.pri)
include(../ShrVN/include.pri)

PROJECT_DIR = ../ShrVN

INCLUDEPATH += $$PROJECT_DIR

SOURCES += \
    catch.cpp \
    main.cpp \
    tst_charactertests.cpp\
