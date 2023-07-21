TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

include(../ShrVN/include.pri)

PROJECT_DIR = ../ShrVN

INCLUDEPATH += $$PROJECT_DIR

SOURCES += \
        main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2
else:unix: LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -libSDL2

INCLUDEPATH += $$PWD/../../3rdparty/SDL2/include
DEPENDPATH += $$PWD/../../3rdparty/SDL2/include
