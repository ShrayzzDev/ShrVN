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
        in_game_menu_interpretor.cpp \
        in_game_menu_parameters.cpp \
        in_game_menu_parserer.cpp \
        in_game_overlay_interpretor.cpp \
        in_game_overlay_parameters.cpp \
        in_game_overlay_parserer.cpp \
        init.cpp \
        main.cpp \
        main_menu_interpretor.cpp \
        main_menu_parameters.cpp \
        main_menu_parserer.cpp \
        options_menu_interpretor.cpp \
        options_menu_parameters.cpp \
        options_menu_parserer.cpp \
        parserer_utils.cpp \
        point.cpp \
        saves_menu_interpertor.cpp \
        saves_menu_parameters.cpp \
        saves_menu_parserer.cpp

HEADERS += \
    ICharacter_Interpreter.hpp \
    IInGameMenuInterpretor.h \
    IInGameOverlayInterpretor.h \
    IMainMenuInterpretor.h \
    IOptionMenuInterpretor.h \
    bezier.h \
    character_instantiator.hpp \
    character_parserer.h \
    characters.hpp \
    in_game_menu_interpretor.hpp \
    in_game_menu_parameters.hpp \
    in_game_menu_parserer.hpp \
    in_game_options_position.h \
    in_game_overlay_interpretor.hpp \
    in_game_overlay_parameters.hpp \
    in_game_overlay_parserer.hpp \
    init.h \
    isave_menu_interpretor.hpp \
    main_menu_interpretor.hpp \
    main_menu_parameters.hpp \
    main_menu_parserer.hpp \
    options_menu_interpretor.h \
    options_menu_parameters.hpp \
    options_menu_parserer.hpp \
    parserer_utils.h \
    point.hpp \
    saves_menu_interpertor.h \
    saves_menu_parameters.hpp \
    saves_menu_parserer.hpp \
    text_block_shape.h \
    text_mode.h

DISTFILES += \
    include.pri
