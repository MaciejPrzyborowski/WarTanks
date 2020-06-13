#include "Tank.h"

Tank::Tank(const int playerID, const bool active, const string &texture, Land &land_) :
    land(&land_),
    tankInterface_(playerID),
    freefall_(false),
    crosshairActive_(false),
    status_(active),
    playerID_(playerID),
    moveDirection_(0),
    shootPower_(50),
    health_(100),
    speed_(50.0),
    maxAngle_(75),
    timeLeft_(15),
    velocityFreefall_(0.0)
{
    TankTexture.loadFromFile(texture);
    CannonTexture.loadFromFile(BarrelTextureSrc);
    CrosshairTexture.loadFromFile(CrosshairTextureSrc);
    TankSprite.setTexture(TankTexture);
    CannonSprite.setTexture(CannonTexture);
    CrosshairSprite.setTexture(CrosshairTexture);

    TankSprite.setOrigin(TankSprite.getLocalBounds().width / 2, TankSprite.getLocalBounds().height);
    CannonSprite.setOrigin(0, CannonSprite.getLocalBounds().height / 2);
}

void Tank::Reset()
{
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
    CannonSprite.setRotation(-90);
}

/**
 * Tworzy pocisk w miejscu aktualnej pozycji celownika
 */
void Tank::shoot()
{
    if(!moveDirection_ && !crosshairActive_ && bullet_ == nullptr)
    {
        float BulletVelocity = (float)shootPower_ * 5.0;
        float CannonRotation = DegreeToRadian(CannonSprite.getRotation());
        sf::Vector2f BulletRotation(cos(CannonRotation), sin(CannonRotation));
        bullet_ = make_unique<Bullet>(sf::Vector2f(CannonSprite.getPosition().x + CannonSprite.getLocalBounds().width * BulletRotation.x,
                                                   CannonSprite.getPosition().y + CannonSprite.getLocalBounds().width * BulletRotation.y),
                                      getTankShape(TankSprite), getTankShape(enemy->TankSprite), *land);
        bullet_->setVelocity(sf::Vector2f(BulletVelocity * BulletRotation.x, BulletVelocity * BulletRotation.y));
    }
}

/**
 * Obsługuje przemieszczenie czołgu
 */
void Tank::moveTank(const float elapsed)
{
    if(moveDirection_)
    {
        sf::Vector2f velocity(0.0, 0.0);
        velocity.x = (speed_ * cos(DegreeToRadian(TankSprite.getRotation()))) * moveDirection_ * elapsed;
        velocity.y = land->getLandHeight(TankSprite.getPosition().x + velocity.x) - TankSprite.getPosition().y;
        moveTankPosition(velocity);
    }
}

/**
 * Obsługuje przemieszczenie lufy
 */
void Tank::moveCannon(sf::RenderWindow &window)
{
    if(crosshairActive_)
    {
        sf::Vector2i rotatePosition;
        sf::Vector2f cannonPosition = CannonSprite.getPosition();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        rotatePosition.x = mousePosition.x - cannonPosition.x;
        rotatePosition.y = mousePosition.y - cannonPosition.y;

        float angle = atan2f(rotatePosition.y, rotatePosition.x);
        CrosshairSprite.setPosition(cannonPosition);
        CrosshairSprite.move(cos(angle) * 100, sin(angle) * 100);
        CannonSprite.setRotation(RadianToDegree(angle));
    }
}

/**
 * Obsługuje zmianę siły wytrzału
 */
void Tank::moveShootPower(const int direction)
{
    if(!((shootPower_ == 0 && direction < 0) || (shootPower_ == 100 && direction > 0)))
    {
        shootPower_ += direction;
    }
}

/**
 * Obsługuje zdarzenia wykonane przez gracza
 */
void Tank::passEvent(sf::Event &event, sf::RenderWindow &window)
{
    if(status_ == 1)
    {
        if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Left)
            {
                if(moveDirection_ == -1)
                {
                    moveDirection_ = 0;
                }
            }
            if(event.key.code == sf::Keyboard::Right)
            {
                if(moveDirection_ == 1)
                {
                    moveDirection_ = 0;
                }
            }
        }
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Space)
            {
                shoot();
            }
            if(event.key.code == sf::Keyboard::Up)
            {
                moveShootPower(1);
            }
            if(event.key.code == sf::Keyboard::Down)
            {
                moveShootPower(-1);
            }

            if(event.key.code == sf::Keyboard::Left)
            {
                moveDirection_ = -1;
            }
            if(event.key.code == sf::Keyboard::Right)
            {
                moveDirection_ = 1;
            }
        }
        if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            if(canCannonMove())
            {
                crosshairActive_ = !crosshairActive_;
                window.setMouseCursorVisible(!crosshairActive_);
            }
        }
    }
}

/**
 * Aktualizuje dane gracza
 */
void Tank::update(const float elapsed, sf::RenderWindow &window)
{
    step(elapsed);
    if(status_ == 1)
    {
        if(bullet_ == nullptr)
        {
            if((timeLeft_ -= elapsed) <= 0)
            {
                status_ = 2;
            }
        }
        moveTank(elapsed);
        moveCannon(window);
    }
    cout << timeLeft_ << endl;
    draw(elapsed, window);
}

/**
 * Wyświetla czołg i jego parametry
 */
void Tank::draw(const float elapsed, sf::RenderTarget &window)
{
    window.draw(CannonSprite);
    window.draw(TankSprite);
    if(status_ == 1)
    {
        if(!tankInterface_.checkPlayersHp(this->returnHp(), enemy->returnHp()))
        {
            tankInterface_.drawPower(window, shootPower_);
            window.draw(tankInterface_.showAngle(360 - CannonSprite.getRotation()));
        }
        if(bullet_)
        {
            if(bullet_->getStatus())
            {
                bullet_->move(elapsed);
                bullet_->draw(window);
            }
            else
            {
                shootReset();
            }
        }
        else if(crosshairActive_)
        {
            window.draw(CrosshairSprite);
        }
    }
}

/**
 * Obsługuje grawitacje
 */
void Tank::step(const float elapsed)
{
    sf::Vector2f TankPosition = TankSprite.getPosition();
    int landHeight = land->getLandHeight(TankSprite.getPosition().x);
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
        TankSprite.move(velocity);
        CannonSprite.move(velocity);
        TankSprite.setRotation(getLandAngle());
    }
    else if(freefall_)
    {
        velocityFreefall_ = 0.0;
        freefall_ = false;
    }
}

/**
 * Zwraca status gracza
 */
int Tank::getStatus()
{
    return status_;
}

/**
 * Zmienia status gracza
 */
void Tank::switchStatus(sf::RenderWindow &window)
{
    timeLeft_ = 15.0;
    if(status_ == 0)
    {
        status_ = 1;
    }
    else
    {
        status_ = 0;
    }
    if(bullet_)
    {
        bullet_.reset();
    }
    moveDirection_ = 0;
    if(crosshairActive_)
    {
        crosshairActive_ = false;
        window.setMouseCursorVisible(true);
    }
    setTankPosition(TankSprite.getPosition());
}

/**
 * Sprawdza czy gracz może zmienić położenie lufy
 */
bool Tank::canCannonMove()
{
    if(status_ == 1 && !freefall_ && !moveDirection_ && bullet_ == nullptr)
    {
        return true;
    }
    return false;
}

/**
 * Sprawdza czy czołg może przemieścić się o wektor [x, y]
 */
bool Tank::canTankMove(const sf::Vector2f &velocity)
{
    if(status_ == 1 && !freefall_ && !crosshairActive_ && bullet_ == nullptr && fabs(getLandAngle(velocity)) <= maxAngle_ && !getCollision(velocity)
            && TankSprite.getPosition().x + velocity.x > 0 && TankSprite.getPosition().x + velocity.x < WindowWidth)
    {
        return true;
    }
    return false;
}

/**
 * Sprawdza czy czołg ma kolizję z przeciwnikiem po przemieszczeniu się o wektor [x, y]
 */
bool Tank::getCollision(const sf::Vector2f &velocity)
{
    if(!TankSprite.getGlobalBounds().intersects(enemy->TankSprite.getGlobalBounds()))
    {
        sf::Sprite tempTankSprite = TankSprite;
        tempTankSprite.move(velocity);
        if(tempTankSprite.getGlobalBounds().intersects(enemy->TankSprite.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

/**
 * Zwraca nachylenie terenu po przemieszczeniu się o wektor [x, y]
 */
float Tank::getLandAngle(const sf::Vector2f &velocity)
{
    sf::Sprite tempTankSprite = TankSprite;
    tempTankSprite.move(velocity);
    return land->getAngleDegree(tempTankSprite.getPosition().x, tempTankSprite.getPosition().y);
}

/**
 * Przesuwa pozycję czołgu oraz jego lufy
 */
void Tank::moveTankPosition(const sf::Vector2f &velocity)
{
    if(canTankMove(velocity))
    {
        TankSprite.move(velocity);
        CannonSprite.move(velocity);
        TankSprite.setRotation(getLandAngle());
    }
}

/**
 * Ustawia pozycję czołgu oraz jego lufy
 */
void Tank::setTankPosition(const sf::Vector2f &position)
{
    TankSprite.setPosition(position);
    CannonSprite.setPosition(position - sf::Vector2f(0, TankSprite.getLocalBounds().height/2));
    TankSprite.setRotation(getLandAngle());
}

/**
 * Usuwa pocisk i zadaje obrażenia trafionym graczom
 */
void Tank::shootReset()
{
    if(bullet_)
    {
        if(bullet_->getStatusExplosion(0))
        {
            health_ -= 10;
        }
        if(bullet_->getStatusExplosion(1))
        {
            enemy->health_ -= 10;
        }
        bullet_.reset();
        status_ = 2;
    }
}

/**
 * Zwraca prawidłową figurę czołgu
 */
sf::RectangleShape Tank::getTankShape(const sf::Sprite &Tank)
{
    sf::RectangleShape TankShape(sf::Vector2f(Tank.getLocalBounds().width, Tank.getLocalBounds().height));
    TankShape.setPosition(Tank.getPosition().x, Tank.getPosition().y - Tank.getLocalBounds().height / 2);
    return TankShape;
}
