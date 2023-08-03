TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

include(../ShrVN/include.pri)

PROJECT_DIR = ../ShrVN

INCLUDEPATH += $$PROJECT_DIR

SOURCES += \
        font.cpp \
        in_game_window.cpp \
        initialisation_error.cpp \
        main.cpp \
        sprite.cpp \
        window.cpp

INCLUDEPATH += $$PWD/../../3rdparty/SDL2/includes
DEPENDPATH += $$PWD/../../3rdparty/SDL2/includes

HEADERS += \
    CurrentScreen.h \
    dialogue.h \
    font.h \
    in_game_window.hpp \
    initialisation_error.hpp \
    sprite.hpp \
    window.hpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2
else:unix: LIBS += -lSDL2

win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2_image
else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2_image
else:unix: LIBS += -lSDL2_image

win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2_ttf
else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3rdparty/SDL2/bin/ -lSDL2_ttf
else:unix: LIBS += -lSDL2_ttf
