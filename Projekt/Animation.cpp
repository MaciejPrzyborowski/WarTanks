#include "Animation.h"

Animation::Animation(const string &name, sf::Vector2f mapPosition, sf::IntRect texturePosition, int step, int radius) :
    active_(true),
    stepPositionX_(step),
    timeElapsed_(0.0),
    changeAnimationTime_(0.1),
    texturePosition_(texturePosition)
{
    AnimationTexture.loadFromFile(name);
    AnimationShape.setRadius(radius);
    AnimationShape.setTexture(&AnimationTexture);
    AnimationShape.setTextureRect(texturePosition_);
    AnimationShape.setPosition(mapPosition);
}

void Animation::changeAnimation(const float elapsed)
{
    if((timeElapsed_ += elapsed) >= changeAnimationTime_)
    {
        if(texturePosition_.left == (int)AnimationTexture.getSize().x)
        {
            active_ = false;
        }
        timeElapsed_ -= changeAnimationTime_;
        texturePosition_.left += stepPositionX_;
        AnimationShape.setTextureRect(texturePosition_);
    }
}

void Animation::draw(const float elapsed, sf::RenderTarget &window)
{
    if(active_)
    {
        changeAnimation(elapsed);
        window.draw(AnimationShape);
    }
}

bool Animation::getStatus()
{
    return active_;
}
