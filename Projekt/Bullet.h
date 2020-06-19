#pragma once

#include "Globals.h"
#include "Animation.h"
#include "Land.h"

enum class BulletState
{
    InActive,
    Active,
    Explode
};

class Bullet
{
public:
    Bullet(const sf::Vector2f &position, const sf::RectangleShape &client, const sf::RectangleShape &target, Land &land_);
    void move(const float elapsed);
    void draw(sf::RenderTarget &window);
    void explode();

    bool getStatusExplosion(int target);
    BulletState getStatus();
    void setAcceleration(const sf::Vector2f &acceleration);
    void setVelocity(const sf::Vector2f &velocity);

private:
    Land *land;
    sf::Clock clock_;
    unique_ptr<Animation> explode_;
    BulletState status_;

    bool clientExploded_;
    bool targetExploded_;
    int explodeSize_;

    sf::Sound explodeSound_;
    sf::SoundBuffer explodeSoundBuffer_;
    sf::CircleShape bullet_;
    sf::RectangleShape client_;
    sf::RectangleShape target_;
    sf::Vector2f acceleration_;
    sf::Vector2f velocity_;

    bool intersects(const sf::CircleShape &bullet, const sf::RectangleShape &Tank);
};
