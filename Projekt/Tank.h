#pragma once

#include "Globals.h"
#include "Land.h"

class Tank
{
public:
    Tank(const int playerID, const bool active, const string &texture, Land &land_);
    void Reset();
    void move(const float elapsed);
    void passEvent(sf::Event &event);
    void draw(sf::RenderTarget &window);

    bool getStatus();
    bool isMoving();

private:
    Land *land;

    bool active_;

    int playerID_;
    int moveDirection_ = 0;

    float speed_ = 50.0;
    float maxAngle_ = 72.5;

    sf::Sprite TankSprite;
    sf::Sprite CannonSprite;
    sf::Texture TankTexture;
    sf::Texture CannonTexture;

    bool canMove(const sf::Vector2f &velocity);

    void movePosition(const sf::Vector2f &velocity);
    void setPosition(const sf::Vector2f &position);
    void setRotation(const sf::Vector2f &position);
};
