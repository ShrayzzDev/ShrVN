QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++20

TEMPLATE = app

include(../../3rdparty/catch/catch.pri)

PROJECT_DIR = ../ShrVN

INCLUDEPATH += $$PROJECT_DIR

PROJECT_SOURCES = \
    $$PROJECT_DIR/characters.cpp

PROJECT_HEADERS = \
    $$PROJECT_DIR/characters.hpp


SOURCES += \
    catch.cpp \
    main.cpp \
    tst_charactertests.cpp\
    $$PROJECT_SOURCES

HEADERS += \
    $$PROJECT_HEADERS
