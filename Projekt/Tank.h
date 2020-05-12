#pragma once

#include <Globals.h>
#include <Land.h>

class Tank
{
public:
    Tank();
    void Draw(sf::RenderTarget &window, Land &Land);
    void Reset();
    void setPosition(const sf::Vector2f& pos);

private:
    sf::Texture TankTexture;
    sf::Texture TurretTexture;

    sf::Sprite TankSprite[160];
    sf::Sprite TurretSprite;
};
