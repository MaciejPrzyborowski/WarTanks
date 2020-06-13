#pragma once

#include "Tank.h"
#include "Menu.h"
#include "Globals.h"
#include "Interface.h"
#include "Animation.h"

class Game
{
public:
    Game();
    void Run();

    void Initialize();
    void Update();
    sf::Text gameTime(float time_);
    void setTimer();
    sf::Text gameEnd();
    bool checkPlayersHp();
    sf::Vector2f Winner();
    sf::Vector2f Loser();

private:
    unique_ptr<Animation> fireworks_;
    unique_ptr<Animation> fire_;
    unique_ptr<sf::RenderWindow> window_;
    unique_ptr<Menu> menu_;
    unique_ptr<Land> land_;
    unique_ptr<Tank> player1_;
    unique_ptr<Tank> player2_;

    int playerHp1_, playerHp2_;
    sf::Vector2f playerPos1_, playerPos2_;

    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    Interface GameInterface;
};
