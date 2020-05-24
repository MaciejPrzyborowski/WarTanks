#include "Tank.h"

Tank::Tank(const int playerID, const bool active, const string &texture, Land &land_) : land(&land_), active_(active), playerID_(playerID)
{
    TankTexture.loadFromFile(texture);
    CannonTexture.loadFromFile(BarrelTextureSrc);
    CannonSprite.setTexture(CannonTexture);
    TankSprite.setTexture(TankTexture);

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
    StartPosition.y = land->GetLandHeight(StartPosition.x);
    setPosition(StartPosition);
    CannonSprite.setRotation(-90);
}

/**
 * Oblicza prędkość przemieszczenia czołgu
 */
void Tank::move(const float elapsed)
{
    if(isMoving())
    {
        sf::Vector2f velocity(0.0, 0.0);
        velocity.x = (speed_ * cos(DegreeToRadian(TankSprite.getRotation()))) * moveDirection_ * elapsed;
        velocity.y = land->GetLandHeight(TankSprite.getPosition().x + velocity.x) - TankSprite.getPosition().y;
        if(canMove(velocity))
        {
            movePosition(velocity);
        }
    }
}

/**
 * Przesuwa pozycję czołgu oraz jego lufy
 */
void Tank::movePosition(const sf::Vector2f &velocity)
{
    TankSprite.move(velocity);
    CannonSprite.move(velocity);
    setRotation(sf::Vector2f(TankSprite.getPosition().x, TankSprite.getPosition().y));
}

/**
 * Ustawia pozycję czołgu oraz jego lufy
 */
void Tank::setPosition(const sf::Vector2f &position)
{
    TankSprite.setPosition(position);
    CannonSprite.setPosition(position - sf::Vector2f(0, TankSprite.getLocalBounds().height/2));
    setRotation(sf::Vector2f(position));
}

/**
 * Ustawia kąt nachylenia czołgu
 */
void Tank::setRotation(const sf::Vector2f &position)
{
    float landAngle = land->GetAngleDegree(position.x, position.y);
    TankSprite.setRotation(landAngle);
}

/**
 * Sprawdza czy czołg może przemieścić się o wektor [x, y]
 */
bool Tank::canMove(const sf::Vector2f &velocity)
{
    if(getStatus() && (velocity.y >= 0 || fabs(TankSprite.getRotation()) <= maxAngle_ || fabs(TankSprite.getRotation()) >= 360.0 - maxAngle_))
    {
        return true;
    }
    return false;
}

/**
 * Sprawdza czy czołg może wykonać jakąś czynność
 */
bool Tank::getStatus()
{
    return active_;
}

/**
 * Sprawdza czy czołg się przemieszcza
 */
bool Tank::isMoving()
{
    if(getStatus())
    {
        if(moveDirection_)
        {
            return true;
        }
    }
    else if(moveDirection_)
    {
        moveDirection_ = 0;
    }
    return false;
}

/**
 * Obsługa zdarzeń wykonanych przez gracza
 */
void Tank::passEvent(sf::Event &event)
{
    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Space)
        {
            active_ = !active_;
        }
        if(event.key.code == sf::Keyboard::Left)
        {
            if(moveDirection_ == -1)
            {
                moveDirection_ = 0;
            }
        }
        else if(event.key.code == sf::Keyboard::Right)
        {
            if(moveDirection_ == 1)
            {
                moveDirection_ = 0;
            }
        }
    }
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Left)
        {
            moveDirection_ = -1;
        }
        if(event.key.code == sf::Keyboard::Right)
        {
            moveDirection_ = 1;
        }
    }
}

/**
 * Wyświetla czołg z jego lufą
 */
void Tank::draw(sf::RenderTarget &window)
{
    window.draw(CannonSprite);
    window.draw(TankSprite);
}
