#include "Tank.h"
#include "Application.h"

Tank::Tank(const int playerID) :
    moveDirection_(TankMove::None),
    velocity(0.0, 0.0),
    freefall_(false),
    crosshairActive_(false),
    getCollision_(false),
    health_(100),
    playerID_(playerID),
    shootPower_(50),
    speed_(50.0),
    timeLeft_(15.0),
    velocityFreefall_(0.0)
{
    type_ = ObjectType::Tank;
    if(playerID == 1)
    {
        status_ = TankState::Active;
        tankTexture_.loadFromFile(TankTextureSrc1);
    }
    else
    {
        status_ = TankState::InActive;
        tankTexture_.loadFromFile(TankTextureSrc2);
    }
    tankInterface_ = make_unique<Interface>(playerID);

    cannonTexture_.loadFromFile(BarrelTextureSrc);
    crosshairTexture_.loadFromFile(CrosshairTextureSrc);
    tankSprite_.setTexture(tankTexture_);
    cannonSprite_.setTexture(cannonTexture_);
    crosshairSprite_.setTexture(crosshairTexture_);

    shootBuffer_.loadFromFile(ShootSoundSrc);
    shootSound_.setBuffer(shootBuffer_);
    shootSound_.setVolume(10);

    tankSprite_.setOrigin(tankSprite_.getLocalBounds().width / 2, tankSprite_.getLocalBounds().height);
    cannonSprite_.setOrigin(0, cannonSprite_.getLocalBounds().height / 2);
}

void Tank::reset()
{
    health_ = 100;
    timeLeft_ = 15.0;
    shootPower_ = 50;
    velocityFreefall_ = 0.0;
    velocity = sf::Vector2f(0.0, 0.0);

    freefall_ = false;
    crosshairActive_ = false;
    moveDirection_ = TankMove::None;

    sf::Vector2f StartPosition(rand() % 150, 0);
    if(playerID_ == 1)
    {
        StartPosition.x += 50;
        status_ = TankState::Active;
    }
    else
    {
        StartPosition.x += 400;
        status_ = TankState::InActive;
    }
    StartPosition.y = Application::getGame().getLandHeight(StartPosition.x);
    tankSprite_.setPosition(StartPosition);
    cannonSprite_.setPosition(StartPosition - sf::Vector2f(0, tankSprite_.getLocalBounds().height / 2));
    tankSprite_.setRotation(getTankAngle());
    cannonSprite_.setRotation(-90);
}

void Tank::shoot()
{
    if(!(int)moveDirection_ && !crosshairActive_)
    {
        status_ = TankState::Waiting;
        if(shootSound_.getStatus() != sf::Music::Playing)
        {
            shootSound_.play();
        }
        float BulletPower = (float)shootPower_ * 5.0;
        float CannonRotation = DegreeToRadian(cannonSprite_.getRotation());
        sf::Vector2f BulletRotation(cos(CannonRotation), sin(CannonRotation));
        Bullet *bullet = new Bullet(sf::Vector2f(cannonSprite_.getPosition().x + cannonSprite_.getLocalBounds().width * BulletRotation.x,
                                                 cannonSprite_.getPosition().y + cannonSprite_.getLocalBounds().width * BulletRotation.y));
        bullet -> setVelocity(sf::Vector2f(BulletPower * BulletRotation.x, BulletPower * BulletRotation.y));
        Application::getGame().addWorldObj(bullet);
    }
}

void Tank::moveCannon(sf::RenderWindow &window)
{
    if(crosshairActive_)
    {
        sf::Vector2i rotatePosition;
        sf::Vector2f cannonPosition = cannonSprite_.getPosition();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        rotatePosition.x = mousePosition.x - cannonPosition.x;
        rotatePosition.y = mousePosition.y - cannonPosition.y;

        float angle = atan2f(rotatePosition.y, rotatePosition.x);
        crosshairSprite_.setPosition(cannonPosition);
        crosshairSprite_.move(cos(angle) * 100, sin(angle) * 100);
        cannonSprite_.setRotation(RadianToDegree(angle));
    }
}

void Tank::moveShootPower(const ShootPowerMove &direction)
{
    if(!((shootPower_ == 0 && (int)direction < 0) || (shootPower_ == 100 && (int)direction > 0)))
    {
        shootPower_ += (int)direction;
    }
}

void Tank::step(const float &elapsed)
{
    sf::Vector2f TankPosition = tankSprite_.getPosition();
    int landHeight = Application::getGame().getLandHeight(TankPosition.x);
    if(TankPosition.y < landHeight)
    {
        freefall_ = true;
        velocityFreefall_ += Gravity * elapsed;

        velocity.x = 0;
        velocity.y = velocityFreefall_ * elapsed;
        if(TankPosition.y + velocity.y >= landHeight)
        {
            velocity.y = landHeight - TankPosition.y + 1;
        }
        tankSprite_.move(velocity);
        cannonSprite_.move(velocity);
        tankSprite_.setRotation(getTankAngle());
    }
    else
    {
        if(freefall_)
        {
            freefall_ = false;
            velocityFreefall_ = 0.0;
        }
        if((int)moveDirection_)
        {
            velocity.x = (speed_ * cos(DegreeToRadian(tankSprite_.getRotation()))) * (int)moveDirection_ * elapsed;
            velocity.y = Application::getGame().getLandHeight(tankSprite_.getPosition().x + velocity.x) - tankSprite_.getPosition().y;
            if(canTankMove(velocity))
            {
                tankSprite_.move(velocity);
                cannonSprite_.move(velocity);
                tankSprite_.setRotation(getTankAngle());
            }
        }
        else
        {
            velocity = sf::Vector2f(0.0, 0.0);
        }
    }
}

void Tank::getCollison(WorldObject &object)
{
    if(object.type_ == ObjectType::Tank)
    {
        if(status_ == TankState::Active)
        {
            auto Enemy = dynamic_cast<Tank *>(&object);
            if(Enemy != nullptr)
            {
                sf::Sprite tempTankSprite = tankSprite_;
                tempTankSprite.move(velocity);
                tempTankSprite.setRotation(getTankAngle(velocity));
                if(tempTankSprite.getGlobalBounds().intersects(Enemy -> tankSprite_.getGlobalBounds()))
                {
                    getCollision_ = true;
                }
                else
                {
                    getCollision_ = false;
                }
            }
        }
    }
    else if(object.type_ == ObjectType::Bullet)
    {
        object.getCollison(*this);
    }
}

void Tank::update(const float &elapsed, sf::RenderWindow &window)
{
    tankInterface_ -> drawHealth(health_, window);
    if(status_ == TankState::Active)
    {
        if((timeLeft_ -= elapsed) <= 0)
        {
            status_ = TankState::Waiting;
            Application::getGame().decCounter();
        }
        else
        {
            moveCannon(window);
        }
    }
    if(status_ != TankState::InActive)
    {
        tankInterface_ -> drawShootPower(shootPower_, window);
        tankInterface_ -> drawTurn(playerID_, timeLeft_, window);
        tankInterface_ -> drawAngle(360 - cannonSprite_.getRotation(), window);
    }
}

void Tank::draw(sf::RenderTarget &window)
{
    window.draw(cannonSprite_);
    window.draw(tankSprite_);
    if(status_ == TankState::Active)
    {
        if(crosshairActive_)
        {
            window.draw(crosshairSprite_);
        }
    }
}

void Tank::setMoveDirection(const TankMove &direction)
{
    moveDirection_ = direction;
}

void Tank::setPlayerHealth(const int &health)
{
    health_ = health;
}

void Tank::switchCursorVisibility(sf::RenderWindow &window)
{
    if(canCannonMove())
    {
        crosshairActive_ = !crosshairActive_;
        window.setMouseCursorVisible(!crosshairActive_);
    }
}

void Tank::switchStatus(sf::RenderWindow &window)
{
    timeLeft_ = 15.0;
    velocity = sf::Vector2f(0.0, 0.0);
    if(status_ == TankState::InActive)
    {
        status_ = TankState::Active;
    }
    else
    {
        status_ = TankState::InActive;
    }
    moveDirection_ = TankMove::None;
    if(crosshairActive_)
    {
        crosshairActive_ = false;
        window.setMouseCursorVisible(true);
    }
}

int Tank::getPlayerHealth()
{
    return health_;
}

int Tank::getPlayerID()
{
    return playerID_;
}

TankState Tank::getStatus()
{
    return status_;
}

sf::Vector2f Tank::getTankPosition()
{
    return tankSprite_.getPosition();
}

sf::RectangleShape Tank::getTankShape()
{
    sf::RectangleShape TankShape(sf::Vector2f(tankSprite_.getLocalBounds().width, tankSprite_.getLocalBounds().height));
    TankShape.setPosition(tankSprite_.getPosition().x, tankSprite_.getPosition().y - tankSprite_.getLocalBounds().height / 2);
    return TankShape;
}

bool Tank::canCannonMove()
{
    if(status_ == TankState::Active && !(int)moveDirection_)
    {
        return true;
    }
    return false;
}

bool Tank::canTankMove(const sf::Vector2f &velocity)
{
    if(status_ == TankState::Active && !freefall_ && !crosshairActive_ && fabs(getTankAngle(velocity)) <= MaxAngle
            && !getCollision_ && tankSprite_.getPosition().x + velocity.x > 0 && tankSprite_.getPosition().x + velocity.x < WindowWidth)
    {
        return true;
    }
    return false;
}

float Tank::getTankAngle(const sf::Vector2f &velocity)
{
    sf::Sprite tempTankSprite = tankSprite_;
    tempTankSprite.move(velocity);
    return Application::getGame().getLandAngleDegree(tempTankSprite.getPosition().x, tempTankSprite.getPosition().y);
}
