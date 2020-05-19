#include "Tank.h"

Tank::Tank(const int PlayerID, const string &texture) : playerID_(PlayerID)
{
    TankTexture.loadFromFile(texture);
    CannonTexture.loadFromFile(BarrelTextureSrc);
    CannonSprite.setTexture(CannonTexture);
    TankSprite.setTexture(TankTexture);

    TankSprite.setOrigin(TankSprite.getLocalBounds().width / 2, TankSprite.getLocalBounds().height);
    CannonSprite.setOrigin(0, CannonSprite.getLocalBounds().height / 2);
    CannonSprite.setRotation(-90);
}

void Tank::Reset(Land &Land)
{
    if(playerID_ == 1)
    {
        setPosition(sf::Vector2f(rand()%150+50, 0));
    }
    else
    {
        setPosition(sf::Vector2f(rand()%150+400, 0));
    }
    float x = TankSprite.getPosition().x;
    float y = Land.GetLandHeight(x);
    float ang = Land.GetLandAngle(x, y);
    TankSprite.setRotation(fmod(90 - RadianToDegree(ang), 360));
    setPosition(sf::Vector2f(x, y));
}

void Tank::move(Land &Land)
{
    int x = TankSprite.getPosition().x;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        x -= 2;
        float y = Land.GetLandHeight(x);
        float ang = Land.GetLandAngle(x, y);
        TankSprite.setRotation(fmod(90 - RadianToDegree(ang), 360));
        setPosition(sf::Vector2f(x, y));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        x += 2;
        float y = Land.GetLandHeight(x);
        float ang = Land.GetLandAngle(x, y);
        TankSprite.setRotation(fmod(90 - RadianToDegree(ang), 360));
        setPosition(sf::Vector2f(x, y));
    }
}

/**
 * Ustawia pozycję czołgu oraz jego lufy
 */
void Tank::setPosition(const sf::Vector2f &position)
{
    TankSprite.setPosition(position);
    CannonSprite.setPosition(position - sf::Vector2f(0, TankSprite.getLocalBounds().height/2));
}

/**
 * Wyświetla czołg z jego lufą
 */
void Tank::draw(sf::RenderTarget &window)
{
    window.draw(CannonSprite);
    window.draw(TankSprite);
}
