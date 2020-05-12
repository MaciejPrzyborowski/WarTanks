#include "Tank.h"

Tank::Tank()
{
    TankTexture.loadFromFile("tank.png");
    TurretTexture.loadFromFile("turret.png");
    for(int i = 0; i < 160; i++)
    {
        TankSprite[i].setTexture(TankTexture);
    }
    TurretSprite.setTexture(TurretTexture);
}

void Tank::Reset()
{
    for(int i = 0; i < 160; i++)
    {
        TankSprite[i].setPosition(i*5, 5);
        TankSprite[i].setOrigin(TankSprite[i].getLocalBounds().width / 2, TankSprite[i].getLocalBounds().height);
    }
}

void Tank::Draw(sf::RenderTarget &window, Land &Land)
{
    for(int i = 0; i < 160; i++)
    {
        float x = TankSprite[i].getPosition().x;
        float y = Land.GetLandHeight(x);
        float ang = Land.GetLandAngle(x, y);
        TankSprite[i].setRotation(fmod(90 - TO_DEG(ang), 360));
        TankSprite[i].setPosition(x, y);
        window.draw(TankSprite[i]);
    }
}
