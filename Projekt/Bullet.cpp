#include "Bullet.h"
#include "Application.h"

Bullet::Bullet(const sf::Vector2f &position) :
    status_(BulletState::Active),
    explodeSize_(30),
    acceleration_(0, Gravity),
    velocity_(0, 0)
{
    type_ = ObjectType::Bullet;
    isDestructed_ = false;

    bullet_.setRadius(4.0);
    bullet_.setFillColor(sf::Color::Red);
    bullet_.setOrigin(bullet_.getRadius(), bullet_.getRadius());
    bullet_.setPosition(position);

    explodeSoundBuffer_.loadFromFile(ExplodeSoundSrc);
    explodeSound_.setBuffer(explodeSoundBuffer_);
    explodeSound_.setVolume(10);
}

void Bullet::step(const float &elapsed)
{
    if(status_ == BulletState::Active)
    {
        if(bullet_.getPosition().x < 0 || bullet_.getPosition().x > WindowWidth || bullet_.getPosition().y >= WindowHeight)
        {
            status_ = BulletState::InActive;
        }
        velocity_ += acceleration_ * elapsed;
        bullet_.move(velocity_ * elapsed);
    }
}

void Bullet::draw(sf::RenderTarget &window)
{
    sf::Time elapsed = clock_.restart();
    if(explode_)
    {
        if(explode_->getStatus())
        {
            explode_->draw(elapsed.asSeconds(), bullet_.getPosition() - sf::Vector2f{(float)explodeSize_, (float)explodeSize_}, window);
        }
        else
        {
            status_ = BulletState::InActive;
            isDestructed_ = true;
        }
    }
    else
    {
        move(elapsed.asSeconds());
        window.draw(bullet_);
    }
}

void Bullet::getCollison(WorldObject &object)
{
    if(status_ == BulletState::Active)
    {
        if(object.type_ == ObjectType::Tank)
        {
            auto tank = dynamic_cast<Tank *>(&object);
            if(tank != nullptr && intersects(bullet_, tank -> getTankShape()))
            {
                explode();
            }
        }
        else if(object.type_ == ObjectType::Land)
        {
            auto land = dynamic_cast<Land *>(&object);
            if(land != nullptr && (bullet_.getPosition().y + bullet_.getRadius() >= land -> getLandHeight(bullet_.getPosition().x)))
            {
                explode();
            }
        }
    }
}

void Bullet::reset()
{
    isDestructed_ = false;
}

void Bullet::explode()
{
    status_ = BulletState::Explode;
    if(explodeSound_.getStatus() != sf::Music::Playing)
    {
        explodeSound_.play();
    }
    explode_ = make_unique<Animation>(ExplosionTextureSrc, sf::IntRect(0, 0, 60, 60), 60, 30, false, 1.0);
    Application::getGame().destroyLand(bullet_.getPosition().x, bullet_.getPosition().y, explodeSize_);
}

BulletState Bullet::getStatus()
{
    return status_;
}

void Bullet::setAcceleration(const sf::Vector2f &acceleration)
{
    acceleration_ = acceleration;
}

void Bullet::setVelocity(const sf::Vector2f &velocity)
{
    velocity_ = velocity;
}

bool Bullet::intersects(const sf::CircleShape &bullet, const sf::RectangleShape &Tank)
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
