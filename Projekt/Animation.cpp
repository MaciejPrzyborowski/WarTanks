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
    animationTexture_.loadFromFile(name);
    animationShape_.setRadius(radius);
    animationShape_.setScale(scale, scale);
    animationShape_.setTexture(&animationTexture_);
    animationShape_.setTextureRect(texturePosition_);
}

void Animation::changeAnimation(const float elapsed)
{
    if((timeElapsed_ += elapsed) >= changeAnimationTime_)
    {
        timeElapsed_ -= changeAnimationTime_;
        texturePosition_.left += stepPositionX_;
        if(repeat_ && texturePosition_.left == (int)animationTexture_.getSize().x)
        {
            texturePosition_.left = textureStartPosition_.left;
        }
        else if(texturePosition_.left == (int)animationTexture_.getSize().x)
        {
            active_ = false;
        }
        animationShape_.setTextureRect(texturePosition_);
    }
}

void Animation::draw(const float elapsed, sf::Vector2f mapPosition, sf::RenderTarget &window)
{
    animationShape_.setPosition(mapPosition);
    if(active_)
    {
        changeAnimation(elapsed);
        window.draw(animationShape_);
    }
}

bool Animation::getStatus()
{
    return active_;
}
