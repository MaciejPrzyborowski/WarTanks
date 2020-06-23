#include "Tank.h"
#include "Application.h"

Tank::Tank(const int playerID, const string &texture, Land &land_) :
    moveDirection_(TankMove::None),
    land(&land_),
    freefall_(false),
    crosshairActive_(false),
    getEnemyCollision_(false),
    //playerID_(playerID),
    shootPower_(50),
    health_(100),
    speed_(50.0),
    maxAngle_(75.0),
    timeLeft_(15.0),
    velocityFreefall_(0.0)
{
    playerID_ = playerID;
    type_ = TypeObject::Tank;
    if(playerID == 1)
    {
        status_ = TankState::Active;
    }
    else
    {
        status_ = TankState::InActive;
    }
    tankInterface_ = make_unique<Interface>(playerID);
    tankTexture_.loadFromFile(texture);
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
    if(playerID_ == 1)
    {
        status_ = TankState::Active;
    }
    else
    {
        status_ = TankState::InActive;
    }
    freefall_ = false;
    crosshairActive_ = false;

    moveDirection_ = TankMove::None;
    shootPower_ = 50;

    health_ = 100;
    timeLeft_ = 15.0;
    velocityFreefall_ = 0.0;

    sf::Vector2f StartPosition(0, 0);
    StartPosition.x = rand() % 150;
    if(playerID_ == 1)
    {
        StartPosition.x += 50;
    }
    else
    {
        StartPosition.x += 400;
    }
    StartPosition.y = land->getLandHeight(StartPosition.x);
    setTankPosition(StartPosition);
    cannonSprite_.setRotation(-90);
}

void Tank::shoot()
{
    if(moveDirection_ == TankMove::None && !crosshairActive_)
    {
        if(shootSound_.getStatus() != sf::Music::Playing)
        {
            shootSound_.play();
        }
        float BulletPower = (float)shootPower_ * 5.0;
        float CannonRotation = DegreeToRadian(cannonSprite_.getRotation());
        sf::Vector2f BulletRotation(cos(CannonRotation), sin(CannonRotation));
        sf::Vector2f BulletPosition = sf::Vector2f(cannonSprite_.getPosition().x + cannonSprite_.getLocalBounds().width * BulletRotation.x,
                                    cannonSprite_.getPosition().y + cannonSprite_.getLocalBounds().width * BulletRotation.y);
        sf::Vector2f BulletVelocity = sf::Vector2f(BulletPower * BulletRotation.x, BulletPower * BulletRotation.y);

        Bullet *bullet = new Bullet(BulletPosition);
        bullet->setVelocity(BulletVelocity);
        Application::getGame().addWorldObj(bullet);
    }
}

void Tank::moveTank(const float &elapsed)
{
    if(moveDirection_ != TankMove::None)
    {
        velocity.x = (speed_ * cos(DegreeToRadian(tankSprite_.getRotation()))) * elapsed;
        if(moveDirection_ == TankMove::Left)
        {
            velocity.x *= -1;
        }
        velocity.y = land->getLandHeight(tankSprite_.getPosition().x + velocity.x) - tankSprite_.getPosition().y;
        moveTankPosition(velocity);
    }
    else
    {
        velocity = sf::Vector2f(0.0, 0.0);
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

void Tank::moveShootPower(const int &direction)
{
    if(!((shootPower_ == 0 && direction < 0) || (shootPower_ == 100 && direction > 0)))
    {
        shootPower_ += direction;
    }
}

void Tank::setCursorVisibility(sf::RenderWindow &window)
{
    if(canCannonMove())
    {
        crosshairActive_ = !crosshairActive_;
        window.setMouseCursorVisible(!crosshairActive_);
    }
}

void Tank::update(const float &elapsed, sf::RenderWindow &window)
{
    //step(elapsed);
    tankInterface_ -> drawHealth(health_, window);
    if(status_ == TankState::Active)
    {
        moveTank(elapsed);
        moveCannon(window);
        tankInterface_ -> drawShootPower(shootPower_, window);
        tankInterface_ -> drawTurn(playerID_, timeLeft_, window);
        tankInterface_ -> drawAngle(360 - cannonSprite_.getRotation(), window);
    }
}

void Tank::getCollison(WorldObject &object)
{
    if(object.type_ == TypeObject::Tank)
    {
        if(status_ == TankState::Active)
        {
            auto Enemy = dynamic_cast<Tank *>(&object);
            if(Enemy != nullptr)
            {
                sf::Sprite tempTankSprite = tankSprite_;
                tempTankSprite.move(velocity);
                tempTankSprite.setRotation(getLandAngle(velocity));
                if(tempTankSprite.getGlobalBounds().intersects(Enemy -> tankSprite_.getGlobalBounds()))
                {
                    getEnemyCollision_ = true;
                }
                else
                {
                    getEnemyCollision_ = false;
                }
            }
        }
    }
    else if(object.type_ == TypeObject::Bullet)
    {
        object.getCollison(*this);
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

void Tank::step(const float &elapsed)
{
    sf::Vector2f TankPosition = tankSprite_.getPosition();
    int landHeight = land -> getLandHeight(tankSprite_.getPosition().x);
    if(TankPosition.y < landHeight)
    {
        freefall_ = true;
        velocityFreefall_ += Gravity * elapsed;

        sf::Vector2f velocity(0.0, 0.0);
        velocity.y = velocityFreefall_ * elapsed;
        if(TankPosition.y + velocity.y >= landHeight)
        {
            velocity.y = landHeight - TankPosition.y + 1;
        }
        tankSprite_.move(velocity);
        cannonSprite_.move(velocity);
        tankSprite_.setRotation(getLandAngle());
    }
    else if(freefall_)
    {
        velocityFreefall_ = 0.0;
        freefall_ = false;
    }
}

TankState Tank::getStatus()
{
    return status_;
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

bool Tank::canCannonMove()
{
    if(status_ == TankState::Active && !freefall_ && moveDirection_ == TankMove::None)
    {
        return true;
    }
    return false;
}

bool Tank::canTankMove(const sf::Vector2f &velocity)
{
    if(status_ == TankState::Active && !freefall_ && !crosshairActive_ && fabs(getLandAngle(velocity)) <= maxAngle_
            && !getEnemyCollision_ && tankSprite_.getPosition().x + velocity.x > 0 && tankSprite_.getPosition().x + velocity.x < WindowWidth)
    {
        return true;
    }
    return false;
}

float Tank::getLandAngle(const sf::Vector2f &velocity)
{
    sf::Sprite tempTankSprite = tankSprite_;
    tempTankSprite.move(velocity);
    return land->getAngleDegree(tempTankSprite.getPosition().x, tempTankSprite.getPosition().y);
}

void Tank::moveTankPosition(const sf::Vector2f &velocity)
{
    if(canTankMove(velocity))
    {
        tankSprite_.move(velocity);
        cannonSprite_.move(velocity);
        tankSprite_.setRotation(getLandAngle());
    }
}

void Tank::setTankPosition(const sf::Vector2f &position)
{
    tankSprite_.setPosition(position);
    cannonSprite_.setPosition(position - sf::Vector2f(0, tankSprite_.getLocalBounds().height / 2));
    tankSprite_.setRotation(getLandAngle());
}

void Tank::shootReset()
{
}

sf::RectangleShape Tank::getTankShape()
{
    sf::RectangleShape TankShape(sf::Vector2f(tankSprite_.getLocalBounds().width, tankSprite_.getLocalBounds().height));
    TankShape.setPosition(tankSprite_.getPosition().x, tankSprite_.getPosition().y - tankSprite_.getLocalBounds().height / 2);
    return TankShape;
}
