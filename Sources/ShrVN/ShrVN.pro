TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ShrVN

SUBDIRS += \
    ../ShrVN-Tests

SOURCES += \
        bezier_curve.cpp \
        character_instantiator.cpp \
        character_parserer.cpp \
        characters.cpp \
        in_game_menu_parameters.cpp \
        in_game_overlay_parameters.cpp \
        init.cpp \
        main.cpp \
        main_menu_parameters.cpp \
        options_menu_parameters.cpp \
        point.cpp \
        saves_menu_parameters.cpp

HEADERS += \
    ICharacter_Interpreter.hpp \
    bezier.h \
    character_instantiator.hpp \
    character_parserer.h \
    characters.hpp \
    in_game_menu_parameters.hpp \
    in_game_options_position.h \
    in_game_overlay_parameters.hpp \
    init.h \
    main_menu_parameters.hpp \
    options_menu_parameters.hpp \
    point.hpp \
    saves_menu_parameters.hpp \
    text_block_shape.h \
    text_mode.h
