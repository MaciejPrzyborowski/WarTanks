#pragma once

#include "Globals.h"
#include "Perlin.h"

struct StepLand
{
    int top_;
    int bottom_;
    float velocity_;
    bool active_;
};

class Land : Perlin
{
public:
    Land(const float &octaves, const float &persistence);
    void generate();
    void destroyCircle(const int &x, const int &y, const int &radius);
    void destroyColumn(const int &x, int top, int bottom);
    void draw(sf::RenderTarget &window);
    void step(const float &elapsed);

    bool isSolidPixel(const int &x, const int &y);
    float getAngleDegree(const int &x, const int &y);
    float getAngleRadian(const int &x, const int &y);
    int getLandHeight(const int &x);

private:
    bool modified_;
    float size_;

    sf::Image image_;
    sf::Sprite sprite_;
    sf::Texture texture_;
    std::vector<int> height_;
    std::map<int, StepLand> steps_;

    sf::Color gradient(const float &brightness, const sf::Color &darkColor, const sf::Color &lightColor);
};
