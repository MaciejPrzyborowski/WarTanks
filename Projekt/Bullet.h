#pragma once

#include "Globals.h"

class Bullet
{
public:
    Bullet(const sf::Vector2f &position);
    void move(const float elapsed);
    void setVelocity(const sf::Vector2f &velocity);
    void setAcceleration(const sf::Vector2f &velocity);
    void draw(sf::RenderTarget &window);
    bool destructed;

private:
    void explode();
    sf::CircleShape bullet_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
};
