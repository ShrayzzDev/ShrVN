TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ShrVN

SOURCES += \
        bezier_curve.cpp \
        characters.cpp \
        main.cpp \
        point.cpp

HEADERS += \
    bezier.h \
    characters.hpp \
    point.hpp
