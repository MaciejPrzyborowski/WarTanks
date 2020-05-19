#include "Land.h"

Land::Land(const float octaves, const float persistence) : Perlin(octaves, persistence)
{
    size_ = WindowWidth / 2.0;
    height_.resize(WindowWidth);
    image_.create(WindowWidth, WindowHeight, sf::Color::Transparent);
    modified_ = false;
}

/**
 * Generuje teren mapy
 */
void Land::Generate()
{
    modified_ = true;
    image_.create(image_.getSize().x, image_.getSize().y, sf::Color::Transparent);
    float offsetx = rand()%1000;
    float offsety = rand()%1000;
    for(int x = 0; x < WindowWidth; x++)
    {
        height_[x] = OctaveNoise((x + offsetx) / size_, offsety / size_);
        for(int y = WindowHeight - height_[x]; y < WindowHeight ; y++)
        {
            image_.setPixel(x, y, Gradient(float(WindowHeight - y) / height_[x],
                                              sf::Color(35, 35, 35), sf::Color(200, 200, 200)));
        }
    }
}

/**
 * Generuje gradient używając interpolacji liniowej
 */
sf::Color Land::Gradient(float t, sf::Color a, sf::Color b)
{
    sf::Color Gradient;
    Gradient.r = LERP(t, a.r, b.r);
    Gradient.g = LERP(t, a.g, b.g);
    Gradient.b = LERP(t, a.b, b.b);
    Gradient.a = LERP(t, a.a, b.a);
    return Gradient;
}

/**
 * Sprawdza czy istnieje teren w punkcie (x, y)
 */
bool Land::IsSolidPixel(int x, int y)
{
    if((x >= 0 && x <= (int)image_.getSize().x) && (y >= 0 && y <= (int)image_.getSize().y))
    {
        return image_.getPixel(x,y) != sf::Color::Transparent;
    }
    return false;
}

/**
 * Zwraca kąt nachylenia powierzchni w punkcie (x,y)
 */
float Land::GetLandAngle(int x, int y)
{
    int d = 3;
    float avgX = 0, avgY = 0;
    for(int x0 = -d; x0 <= d; x0++)
    {
        for(int y0 = -d; y0 <= d; y0++)
        {
            if(IsSolidPixel(x + x0, y + y0))
            {
                avgX += x0;
                avgY += y0;
            }
        }
    }
    return avgX ? atan2(avgY, -avgX) : M_PI_2;
}

/**
 * Zwraca wysokość powierzchni
 */
int Land::GetLandHeight(const int x)
{
    return WindowHeight - height_[x];
}

/**
 * Aktualizuje i wyświetla teren
 */
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
