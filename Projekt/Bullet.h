#pragma once

#include "Globals.h"
#include "Land.h"

class Bullet
{
public:
    Bullet(const sf::Vector2f &position, Land &land_);
    void move(const float elapsed);
    void setAcceleration(const sf::Vector2f &velocity);
    void setVelocity(const sf::Vector2f &velocity);
    void draw(sf::RenderTarget &window);

    bool isActive();

private:
    Land *land;

    bool active_;

    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;

    sf::CircleShape bullet_;
};
