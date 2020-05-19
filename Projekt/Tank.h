#pragma once

#include "Globals.h"
#include "Land.h"

class Tank
{
public:
    Tank(const int PlayerID, const string &texture);
    void draw(sf::RenderTarget &window);
    void Reset(Land &Land);
    void setPosition(const sf::Vector2f &position);
    void move(Land &Land);

private:
    sf::Texture CannonTexture;
    sf::Texture TankTexture;
    sf::Sprite CannonSprite;
    sf::Sprite TankSprite;
    bool FreeFall;
    int playerID_;
};
