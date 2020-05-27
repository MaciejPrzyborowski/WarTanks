#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f &position) : velocity_(0, 0), acceleration_(0, Gravity)
{
    destructed = false;
    bullet_.setRadius(4.0);
    bullet_.setFillColor(sf::Color::Red);
    cout << position.x << " " << position.y << endl;
    bullet_.setPosition(position);
}

void Bullet::setVelocity(const sf::Vector2f &velocity)
{
    velocity_ = velocity;
}

void Bullet::setAcceleration(const sf::Vector2f &velocity)
{
    acceleration_ = velocity;
}

void Bullet::draw(sf::RenderTarget &window)
{
    window.draw(bullet_);
}

void Bullet::move(const float elapsed)
{
    velocity_ += acceleration_ * elapsed;
    bullet_.move(velocity_ * elapsed);
    if(bullet_.getPosition().x >= WindowWidth || bullet_.getPosition().x < 0 || bullet_.getPosition().y >= WindowHeight)
    {
        destructed = true;
        //ChangePlayer_ = true;
        cout << "Destructed" << endl;
    }
}
