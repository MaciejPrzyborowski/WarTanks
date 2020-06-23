#pragma once

#include "Globals.h"
#include "Game.h"

class Application
{
public:
    Application() = delete;

    static void run();
    static void quit();

    static sf::RenderWindow &getWindow();
    static Game &getGame();

private:
    static sf::RenderWindow window_;
    static Game game_;
};
