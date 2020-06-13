#include "Animation.h"

Animation::Animation(const string &name, sf::IntRect texturePosition, int step, int radius, bool repeat, float scale) :
    active_(true),
    stepPositionX_(step),
    timeElapsed_(0.0),
    changeAnimationTime_(0.1),
    textureStartPosition_(texturePosition)
{
    repeat_ = repeat;
    texturePosition_ = textureStartPosition_;
    AnimationTexture.loadFromFile(name);
    AnimationShape.setRadius(radius);
    AnimationShape.setScale(scale, scale);
    AnimationShape.setTexture(&AnimationTexture);
    AnimationShape.setTextureRect(texturePosition_);
}

void Animation::changeAnimation(const float elapsed)
{
    if((timeElapsed_ += elapsed) >= changeAnimationTime_)
    {
        timeElapsed_ -= changeAnimationTime_;
        texturePosition_.left += stepPositionX_;
        if(repeat_ && texturePosition_.left == (int)AnimationTexture.getSize().x)
        {
            texturePosition_.left = textureStartPosition_.left;
        }
        else if(texturePosition_.left == (int)AnimationTexture.getSize().x)
        {
            active_ = false;
        }
        AnimationShape.setTextureRect(texturePosition_);
    }
}

void Animation::draw(const float elapsed, sf::Vector2f mapPosition, sf::RenderTarget &window)
{
    AnimationShape.setPosition(mapPosition);
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
