#pragma once

#include "Globals.h"

class Animation
{
public:
    Animation(const string &fileName, sf::IntRect position, int stepPosition, int radius, bool repeat, float scale);
    void changeAnimation(const float elapsed);
    void draw(const float elapsed, const sf::Vector2f &position, sf::RenderTarget &window);

    bool getStatus();

private:
    bool active_;
    bool repeat_;

    int stepPosition_;
    float stepTime_;
    float timeElapsed_;

    sf::IntRect position_;
    sf::IntRect startPosition_;
    sf::Texture texture_;
    sf::CircleShape shape_;
};
