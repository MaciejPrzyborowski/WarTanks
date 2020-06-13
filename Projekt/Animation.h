#pragma once

#include "Globals.h"

class Animation
{
public:
    Animation(const string &name, sf::IntRect texturePosition, int step, int radius, bool repeat, float scale);
    void changeAnimation(const float elapsed);
    void draw(const float elapsed, sf::Vector2f mapPosition, sf::RenderTarget &window);

    bool getStatus();

private:
    bool active_;
    bool repeat_;

    int stepPositionX_;
    float timeElapsed_;
    float changeAnimationTime_;

    sf::IntRect texturePosition_;
    sf::IntRect textureStartPosition_;
    sf::Texture animationTexture_;
    sf::CircleShape animationShape_;
};
