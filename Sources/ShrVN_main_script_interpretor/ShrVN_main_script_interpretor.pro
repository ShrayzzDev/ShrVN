TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

include(../ShrVN/include.pri)

PROJECT_DIR = ../ShrVN

INCLUDEPATH += $$PROJECT_DIR

SOURCES += \
        initialisation_error.cpp \
        main.cpp \
        window.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2
else:unix: LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -libSDL2

INCLUDEPATH += $$PWD/../../3rdparty/SDL2/includes
DEPENDPATH += $$PWD/../../3rdparty/SDL2/includes

HEADERS += \
    initialisation_error.hpp \
    window.hpp
