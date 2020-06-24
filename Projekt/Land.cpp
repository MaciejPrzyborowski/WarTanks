#include "Land.h"

Land::Land(const float &octaves, const float &persistence) :
    Perlin(octaves, persistence),
    modified_(false),
    size_(WindowWidth / 2.0),
    height_(WindowWidth),
    steps_()
{
    type_ = ObjectType::Land;
    image_.create(WindowWidth, WindowHeight, sf::Color::Transparent);
}

void Land::reset()
{
    image_.create(image_.getSize().x, image_.getSize().y, sf::Color::Transparent);
    float offsetx = rand() % 1000;
    float offsety = rand() % 1000;
    for(int x = 0; x < WindowWidth; x++)
    {
        height_[x] = octaveNoise((x + offsetx) / size_, offsety / size_);
        for(int y = WindowHeight - height_[x]; y < WindowHeight ; y++)
        {
            image_.setPixel(x, y, gradient(float(WindowHeight - y) / height_[x], sf::Color(0, 35, 0), sf::Color(0, 200, 0)));
        }
    }
    modified_ = true;
    steps_.clear();
}

void Land::destroyCircle(const int &x, const int &y, const int &r)
{
    for(int x0 = 0; x0 < r; x0++)
    {
        int y0 = sqrt(pow(r, 2) - pow(x0, 2));
        destroyColumn(x + x0, y - y0, y + y0);
        destroyColumn(x - x0, y - y0, y + y0);
    }
}

void Land::destroyColumn(const int &x, int top, int bottom)
{
    if(x >= 0 && x < (int)image_.getSize().x)
    {
        if(top < 0)
        {
            top = 0;
        }
        if(bottom > WindowHeight - 1)
        {
            bottom = WindowHeight - 1;
        }
        if(bottom > getHeight(x))
        {
            for(int y = top; y <= bottom; y++)
            {
                if(isSolidPixel(x, y))
                {
                    image_.setPixel(x, y, sf::Color::Transparent);
                }
            }
            if(top > getHeight(x))
            {
                steps_[x] = StepLand{top, bottom, Gravity, true};
            }
            else
            {
                height_[x] = WindowHeight - bottom;
            }
            modified_ = true;
        }
    }
}

void Land::step(const float &elapsed)
{
    if(steps_.size() > 0)
    {
        list<int> toRemoveSteps;
        for(auto &step : steps_)
        {
            int x = step.first;
            StepLand &stepList = step.second;
            if(stepList.active_)
            {
                stepList.velocity_ += Gravity * elapsed;
                int velocity = stepList.velocity_ * elapsed;
                if(velocity > 0)
                {
                    int y = getHeight(x);
                    if(stepList.top_ + velocity >= stepList.bottom_)
                    {
                        velocity = stepList.bottom_ - stepList.top_ + 1;
                        stepList.top_ = stepList.bottom_;
                        stepList.active_ = false;
                    }
                    else
                    {
                        stepList.top_ += velocity;
                    }
                    if(height_[x] - velocity > 0)
                    {
                        height_[x] -= velocity;
                    }
                    else
                    {
                        height_[x] = 0;
                    }
                    for(int y0 = stepList.top_; y0 >= y; y0--)
                    {
                        if(y0 - velocity >= 0)
                        {
                            image_.setPixel(x, y0, image_.getPixel(x, y0 - velocity));
                        }
                        else
                        {
                            image_.setPixel(x, y0, sf::Color::Transparent);
                        }
                    }
                }
            }
            else
            {
                toRemoveSteps.emplace_back(x);
            }
            modified_ = true;
        }
        for(auto const &x : toRemoveSteps)
        {
            steps_.erase(x);
        }
    }
}

void Land::getCollison(WorldObject &object)
{
    if(object.type_ == ObjectType::Tank)
    {
        object.getCollison(*this);
    }
    else if(object.type_ == ObjectType::Bullet)
    {
        object.getCollison(*this);
    }
}

void Land::draw(sf::RenderTarget &window)
{
    if(modified_)
    {
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);
        modified_ = false;
    }
    window.draw(sprite_);
}

bool Land::isSolidPixel(const int &x, const int &y)
{
    if((x >= 0 && x < (int)image_.getSize().x) && (y >= 0 && y < (int)image_.getSize().y))
    {
        return image_.getPixel(x, y) != sf::Color::Transparent;
    }
    return false;
}

float Land::getAngleDegree(const int &x, const int &y)
{
    return fmod(RadianToDegree(getAngleRadian(x, y)), 360.0);
}

float Land::getAngleRadian(const int &x, const int &y)
{
    int d = 3;
    float avgX = 0, avgY = 0;
    for(int x0 = -d; x0 <= d; x0++)
    {
        for(int y0 = -d; y0 <= d; y0++)
        {
            if(isSolidPixel(x + x0, y + y0))
            {
                avgX += x0;
                avgY += y0;
            }
        }
    }
    return avgX ? (M_PI_2 - atan2(avgY, -avgX)) : 0;
}

int Land::getHeight(const int &x)
{
    if(x >= 0 && x <= (int)height_.size())
    {
        return WindowHeight - height_[x];
    }
    return WindowHeight;
}

sf::Color Land::gradient(const float &brightness, const sf::Color &darkColor, const sf::Color &lightColor)
{
    sf::Color Gradient;
    Gradient.r = LERP(brightness, darkColor.r, lightColor.r);
    Gradient.g = LERP(brightness, darkColor.g, lightColor.g);
    Gradient.b = LERP(brightness, darkColor.b, lightColor.b);
    Gradient.a = LERP(brightness, darkColor.a, lightColor.a);
    return Gradient;
}
