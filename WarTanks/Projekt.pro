TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        Animation.cpp \
        Application.cpp \
        Bullet.cpp \
        Game.cpp \
        Interface.cpp \
        World.cpp \
        Land.cpp \
        Perlin.cpp \
        Tank.cpp \
        Menu.cpp \
        main.cpp

HEADERS += \
    Animation.h \
    Application.h \
    Bullet.h \
    Game.h \
    Globals.h \
    Land.h \
    Perlin.h \
    Tank.h \
    Menu.h \
    Interface.h \
    World.h \
    WorldObject.h
