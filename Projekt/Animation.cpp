#include "Animation.h"

Animation::Animation(const string &fileName, sf::IntRect position, int stepPosition, int radius, bool repeat, float scale) :
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

/**
 * Zmienia pozycję obrazka o wartość stepPosition_ tworząc jego animację
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 */
void Animation::changeAnimation(const float elapsed)
{
    if((timeElapsed_ += elapsed) >= stepTime_)
    {
        timeElapsed_ -= stepTime_;
        position_.left += stepPosition_;
        if(repeat_ && position_.left == (int)texture_.getSize().x)
        {
            position_.left = startPosition_.left;
        }
        else if(position_.left == (int)texture_.getSize().x)
        {
            active_ = false;
        }
        shape_.setTextureRect(position_);
    }
}

/**
 * Wyświetla animację w punkcie position(x, y)
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 * @param position - współrzędne punktu (x, y), w którym ma zostać wyświetlona animacja
 * @param window - okno gry
 */
void Animation::draw(const float elapsed, const sf::Vector2f &position, sf::RenderTarget &window)
{
    shape_.setPosition(position);
    if(active_)
    {
        changeAnimation(elapsed);
        window.draw(shape_);
    }
}

/**
 * Sprawdza status animacji
 *
 * @return
 *          true - animacja jest akywna
 *          false - animacja nie jest aktywna
 */
bool Animation::getStatus()
{
    return active_;
}
