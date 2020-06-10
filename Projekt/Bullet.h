#pragma once

#include "Globals.h"
#include "Land.h"
#include "Animation.h"

class Bullet
{
public:
    Bullet(const sf::Vector2f &position, const sf::RectangleShape &client, const sf::RectangleShape &target, Land &land_);
    void move(const float elapsed);
    void draw(sf::RenderTarget &window);
    void explode();

    int getStatus();
    int getStatusExplosion(int client);
    void setAcceleration(const sf::Vector2f &velocity);
    void setVelocity(const sf::Vector2f &velocity);

private:
    Land *land;
    sf::Clock clock;
    unique_ptr<Animation> explode_;

    bool clientExploded_;
    bool targetExploded_;

    int status_;
    int explodeSize_;

    sf::CircleShape bullet_;
    sf::RectangleShape client_;
    sf::RectangleShape target_;
    sf::Vector2f acceleration_;
    sf::Vector2f velocity_;
    sf::CircleShape explosionBullet;

    bool intersects(sf::CircleShape bullet, sf::RectangleShape Tank);
};
