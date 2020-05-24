#include "Tank.h"

Tank::Tank(const int PlayerID, bool status, const string &texture, Land &land) : playerID_(PlayerID), active_(status), land(&land)
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

void Tank::move(float elapsed)
{
    int direction = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        direction = -1.0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        direction = 1.0;
    }
    if(direction)
    {
        sf::Vector2f velocity(0.0, 0.0);
        velocity.x = (speed_ * cos(DegreeToRadian(TankSprite.getRotation()))) * direction * elapsed;
        velocity.y = land->GetLandHeight(TankSprite.getPosition().x + velocity.x) - TankSprite.getPosition().y;
        cout << velocity.y << endl;
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
 * Ustawia status czołgu
 *
 * @param status
 * true - może wykonać wszystkie czynności
 * false - nie może wykonywać żadnych czynności
 */
void Tank::setStatus(const bool status)
{
    active_ = status;
}

/**
 * Wyświetla czołg z jego lufą
 */
void Tank::draw(sf::RenderTarget &window)
{
    window.draw(CannonSprite);
    window.draw(TankSprite);
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
    if(active_)
    {
        return true;
    }
    return false;
}
