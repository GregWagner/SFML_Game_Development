TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    game.cpp

LIBS += -LC:/sfml-2.5.1-build/LIBS

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system

INCLUDEPATH += c:/SFML-2.5.1/include
DEPENDPATH += c:/SFML-2.5.1/include

HEADERS += \
    game.h
