#pragma once

#include "Globals.h"

class Animation
{
public:
    Animation(const string &name, sf::Vector2f mapPosition, sf::IntRect texturePosition, int step, int radius);
    void changeAnimation(const float elapsed);
    void draw(const float elapsed, sf::RenderTarget &window);

    bool getStatus();

private:
    bool active_;

    int stepPositionX_;
    float timeElapsed_;
    float changeAnimationTime_;

    sf::IntRect texturePosition_;
    sf::Texture AnimationTexture;
    sf::CircleShape AnimationShape;
};
