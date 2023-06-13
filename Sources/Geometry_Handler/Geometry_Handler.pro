TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bezier_curve.cpp \
        main.cpp \
        point.cpp

HEADERS += \
    bezier.h \
    point.hpp
