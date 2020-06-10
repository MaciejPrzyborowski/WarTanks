#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f &position, const sf::RectangleShape &client, const sf::RectangleShape &target, Land &land_) :
    land(&land_),
    clientExploded_(false),
    targetExploded_(false),
    status_(1),
    explodeSize_(30),
    client_(client),
    target_(target),
    acceleration_(0, Gravity),
    velocity_(0, 0)
{
    bullet_.setRadius(4.0);
    bullet_.setFillColor(sf::Color::Red);
    bullet_.setOrigin(bullet_.getRadius(), bullet_.getRadius());
    bullet_.setPosition(position);
}

void Bullet::move(const float elapsed)
{
    if(status_ == 1)
    {
        if(bullet_.getPosition().x < 0 || bullet_.getPosition().x > WindowWidth || bullet_.getPosition().y >= WindowHeight)
        {
            status_ = 0;
        }
        else if(intersects(bullet_, target_) || intersects(bullet_, client_) || bullet_.getPosition().y + bullet_.getRadius() >= land->getLandHeight(bullet_.getPosition().x))
        {
            explode();
        }
        velocity_ += acceleration_ * elapsed;
        bullet_.move(velocity_ * elapsed);
    }
}

void Bullet::draw(sf::RenderTarget &window)
{
    sf::Time elapsed = clock.restart();
    if(explode_)
    {
        explode_->draw(elapsed.asSeconds(), window);
        if(explode_->getStatus() == false)
        {
            status_ = 0;
        }
    }
    else
    {
        window.draw(bullet_);
    }
}

void Bullet::explode()
{
    status_ = 2;
    sf::CircleShape explosionBullet = bullet_;
    explosionBullet.setOrigin(explodeSize_, explodeSize_);
    explosionBullet.setRadius(explodeSize_);
    if(intersects(explosionBullet, target_))
    {
        targetExploded_ = true;
    }
    if(intersects(explosionBullet, client_))
    {
        clientExploded_ = true;
    }
    land->destroyCircle(bullet_.getPosition().x, bullet_.getPosition().y, explodeSize_);
    explode_ = make_unique<Animation>(ExplosionTextureSrc, sf::Vector2f(bullet_.getPosition().x - 30.0, bullet_.getPosition().y - 30.0),
                                      sf::IntRect(0, 0, 60, 60), 60, 30);
}

void Bullet::setAcceleration(const sf::Vector2f &velocity)
{
    acceleration_ = velocity;
}

void Bullet::setVelocity(const sf::Vector2f &velocity)
{
    velocity_ = velocity;
}

int Bullet::getStatus()
{
    return status_;
}

int Bullet::getStatusExplosion(int client)
{
    if(client == 0)
    {
        return clientExploded_;
    }
    return targetExploded_;
}

bool Bullet::intersects(sf::CircleShape bullet, sf::RectangleShape Tank)
{
    sf::Vector2f BulletDistance;
    BulletDistance.x = fabs(bullet.getPosition().x - Tank.getPosition().x);
    BulletDistance.y = fabs(bullet.getPosition().y - Tank.getPosition().y);
    double CornerDistance = powf((BulletDistance.x - Tank.getLocalBounds().width / 2), 2) +
            powf((BulletDistance.y - Tank.getLocalBounds().height / 2), 2);

    if((BulletDistance.x <= Tank.getLocalBounds().width / 2)
            && (bullet.getRadius() && BulletDistance.y <= Tank.getLocalBounds().height / 2 + bullet.getRadius()))
    {
        return true;
    }
    return (CornerDistance <= powf((bullet.getRadius()), 2));
}
