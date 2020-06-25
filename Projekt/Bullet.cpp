#include "Bullet.h"
#include "Application.h"
#include "Land.h"
#include "Tank.h"

Bullet::Bullet(const sf::Vector2f &position) :
    explode_(nullptr),
    status_(true),
    players_(MaxPlayers),
    explodeSize_(30),
    acceleration_(0, Gravity),
    velocity_(0, 0)
{
    type_ = ObjectType::Bullet;

    bullet_.setRadius(4.0);
    bullet_.setFillColor(sf::Color::Red);
    bullet_.setOrigin(bullet_.getRadius(), bullet_.getRadius());
    bullet_.setPosition(position);

    explodeSoundBuffer_.loadFromFile(ExplodeSoundSrc);
    explodeSound_.setBuffer(explodeSoundBuffer_);
    explodeSound_.setVolume(10);
}

void Bullet::reset()
{
    isDestructed_ = false;
}

void Bullet::step(const float &elapsed)
{
    if(status_ == true)
    {
        if(bullet_.getPosition().x < 0 || bullet_.getPosition().x > WindowWidth || bullet_.getPosition().y >= WindowHeight)
        {
            Application::getGame().decCounter();
            isDestructed_ = true;
        }
        velocity_ += acceleration_ * elapsed;
        bullet_.move(velocity_ * elapsed);
    }
}

void Bullet::getCollison(WorldObject &object)
{
    if(status_)
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
            if(land != nullptr && (bullet_.getPosition().y + bullet_.getRadius() >= land -> getHeight(bullet_.getPosition().x)))
            {
                explode();
            }
        }
    }
    else if(players_ > 0)
    {
        if(object.type_ == ObjectType::Tank)
        {
            auto tank = dynamic_cast<Tank *>(&object);
            if(tank != nullptr)
            {
                if(intersects(bullet_, tank -> getTankShape()))
                {
                    tank->setPlayerHealth(tank->getPlayerHealth() - 25);
                }
                players_--;
            }
        }
    }
}

void Bullet::draw(sf::RenderTarget &window)
{
    sf::Time elapsed = clock_.restart();
    if(explode_ != nullptr)
    {
        if(explode_ -> getStatus())
        {
           if(explode_ -> changeAnimation(elapsed.asSeconds()))
           {
               explode_ -> draw(window);
           }
        }
        else
        {
            Application::getGame().decCounter();
            isDestructed_ = true;
        }
    }
    else
    {
        window.draw(bullet_);
    }
}

bool Bullet::getStatus()
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

void Bullet::explode()
{
    status_ = false;
    bullet_.setOrigin(explodeSize_, explodeSize_);
    bullet_.setRadius(explodeSize_);
    if(explodeSound_.getStatus() != sf::Music::Playing)
    {
        explodeSound_.play();
    }
    explode_ = make_unique<Animation>(ExplosionTextureSrc, sf::IntRect(0, 0, 60, 60), 60, 30, false, 1.0);
    explode_ -> changePosition(bullet_.getPosition() - sf::Vector2f((float)explodeSize_, (float)explodeSize_));
    Application::getGame().destroyLand(bullet_.getPosition().x, bullet_.getPosition().y, explodeSize_);
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
