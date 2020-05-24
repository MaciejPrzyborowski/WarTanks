#pragma once

#include "Land.h"
#include "Tank.h"
#include "Menu.h"
#include "Globals.h"

class Game
{
public:
    Game();
    void Run();

    void Initialize();
    void Update();

private:
    unique_ptr<sf::RenderWindow> window_;
    unique_ptr<Menu> menu_;
    unique_ptr<Land> land_;
    unique_ptr<Tank> player1_;
    unique_ptr<Tank> player2_;
};
