#pragma once

#include "Tank.h"
#include "Menu.h"
#include "Globals.h"
#include "Interface.h"
#include "Animation.h"

enum GameState
{
    GameMenu,
    GamePlay
};

class Game
{
public:
    Game();

    void run();
    void initialize(GameState gameState);
    void passEvent(sf::Event &Event);
    void update();
    void setTimer();
    void updateAll(sf::Time elapsed);

private:
    unique_ptr<Animation> fireworks_;
    unique_ptr<Animation> fire_;
    unique_ptr<sf::RenderWindow> window_;
    unique_ptr<Menu> menu_;
    unique_ptr<Land> land_;
    unique_ptr<Tank> player1_;
    unique_ptr<Tank> player2_;
    unique_ptr<Interface> GameInterface_;

    GameState gameState_;

    int playerHp1_, playerHp2_;

    sf::Vector2f playerPos1_, playerPos2_;
    sf::Vector2f winner_, loser_;

    sf::Texture gameBackgroundTexture_;
    sf::Sprite gameBackgroundSprite_;
    sf::Texture menuBackgroundTexture_;
    sf::Sprite menuBackgroundSprite_;
};
