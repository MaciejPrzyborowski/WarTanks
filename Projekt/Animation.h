#pragma once
#include "Globals.h"

class Animation
{
public:
    Animation(sf::Vector2f position);
    void Explode(float elapsed, sf::RenderTarget &window);
    bool isExplosionEnd = false;

private:
    std::string name = "explosion.png";
    sf::Texture texture;
    sf::CircleShape explosion;
    float time = 0.0;
    sf::IntRect coords = sf::IntRect(0, 0, 60, 60);
};
