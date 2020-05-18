#include "Tank.h"

Tank::Tank()
{
    TankTexture.loadFromFile(TankTextureSrc);
    CannonTexture.loadFromFile(BarrelTextureSrc);
    CannonSprite.setTexture(CannonTexture);
    TankSprite.setTexture(TankTexture);
    CannonSprite.setOrigin(0, CannonSprite.getLocalBounds().height / 2);
}

void Tank::Reset()
{
    TankSprite.setPosition(rand()%150+50, 5);
    TankSprite.setOrigin(TankSprite.getLocalBounds().width / 2, TankSprite.getLocalBounds().height);
}

void Tank::Draw(sf::RenderTarget &window, Land &Land)
{
    float x = TankSprite.getPosition().x;
    float y = Land.GetLandHeight(x);
    float ang = Land.GetLandAngle(x, y);
    TankSprite.setRotation(fmod(90 - TO_DEG(ang), 360));
    TankSprite.setPosition(x, y);
    CannonSprite.setRotation(-45);
    CannonSprite.setPosition(sf::Vector2f(x, y) - sf::Vector2f(0, TankSprite.getLocalBounds().height/2));

    window.draw(TankSprite);
    window.draw(CannonSprite);
}
