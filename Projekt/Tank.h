#pragma once

#include "Globals.h"
#include "Land.h"

class Tank
{
public:
    Tank(const int PlayerID, bool status, const string &texture, Land &land);
    ////////////////////////////////////////////////
    void draw(sf::RenderTarget &window);
    void movePosition(const sf::Vector2f &velocity);
    void setPosition(const sf::Vector2f &position);
    void setRotation(const sf::Vector2f &position);
    void setStatus(const bool status);

    bool canMove(const sf::Vector2f &velocity);
    bool getStatus();
    ////////////////////////////////////////////////
    void Reset();
    void move(float dt);
    float elapsedtime = 0.0;

private:
    sf::Texture CannonTexture;
    sf::Texture TankTexture;
    sf::Sprite CannonSprite;
    sf::Sprite TankSprite;

    //////////////////////////////////////////////////
    float maxAngle_ = 72.5;
    float speed_ = 50.0;
    int playerID_;
    bool active_;
    Land *land;
};
