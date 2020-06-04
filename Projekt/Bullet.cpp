#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f &position, Land &land_) :
    land(&land_),
    active_(true),
    velocity_(0, 0),
    acceleration_(0, Gravity)
{
    bullet_.setRadius(4.0);
    bullet_.setFillColor(sf::Color::Red);
    bullet_.setPosition(position);
}

void Bullet::move(const float elapsed)
{
    velocity_ += acceleration_ * elapsed;
    bullet_.move(velocity_ * elapsed);
    if(bullet_.getPosition().x < 0 || bullet_.getPosition().x > WindowWidth || bullet_.getPosition().y >= WindowHeight)
    {
        active_ = false;
    }
    else if(bullet_.getPosition().y + bullet_.getRadius() >= land->getLandHeight(bullet_.getPosition().x))
    {
        active_ = false;
        land->destroyCircle(bullet_.getPosition().x, bullet_.getPosition().y, 30);
    }
}

void Bullet::setAcceleration(const sf::Vector2f &velocity)
{
    acceleration_ = velocity;
}

void Bullet::setVelocity(const sf::Vector2f &velocity)
{
    velocity_ = velocity;
}

bool Bullet::isActive()
{
    return active_;
}

void Bullet::draw(sf::RenderTarget &window)
{
    window.draw(bullet_);
}
