#include "Animation.h"

Animation::Animation(const string &fileName, const sf::IntRect &position,
                     const int &stepPosition, const int &radius, const bool &repeat, const float &scale) :
    active_(true),
    stepPosition_(stepPosition),
    stepTime_(0.1),
    timeElapsed_(0.0),
    startPosition_(position)
{
    repeat_ = repeat;
    position_ = startPosition_;
    texture_.loadFromFile(fileName);
    shape_.setRadius(radius);
    shape_.setScale(scale, scale);
    shape_.setTexture(&texture_);
    shape_.setTextureRect(position_);
}

bool Animation::changeAnimation(const float &elapsed)
{
    if((timeElapsed_ += elapsed) >= stepTime_)
    {
        timeElapsed_ -= stepTime_;
        position_.left += stepPosition_;
        if(position_.left == (int)texture_.getSize().x)
        {
            if(repeat_)
            {
                position_.left = startPosition_.left;
            }
            else
            {
                active_ = false;
            }
        }
        shape_.setTextureRect(position_);
    }
    return active_;
}

void Animation::changePosition(const sf::Vector2f &position)
{
    shape_.setPosition(position);
}

void Animation::draw(sf::RenderTarget &window)
{
    if(active_)
    {
        window.draw(shape_);
    }
}

bool Animation::getStatus()
{
    return active_;
}
