TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ShrVN

SOURCES += \
        bezier_curve.cpp \
        characterinstantiator.cpp \
        characterparserer.cpp \
        characters.cpp \
        ingamemenuparameters.cpp \
        ingameoverlayparameters.cpp \
        init.cpp \
        main.cpp \
        menuparameters.cpp \
        optionsmenuparameters.cpp \
        point.cpp \
        savesmenuparameters.cpp

HEADERS += \
    bezier.h \
    characterinstantiator.hpp \
    characterparserer.h \
    characters.hpp \
    icharacterinterpreter.hpp \
    ingamemenuparameters.hpp \
    ingameoverlayparameters.hpp \
    init.h \
    menuparameters.hpp \
    optionsmenuparameters.hpp \
    point.hpp \
    savesmenuparameters.hpp
