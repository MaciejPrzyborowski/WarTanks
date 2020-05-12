#pragma once

#include "Globals.h"
#include "Perlin.h"

class Land : Perlin
{
public:
    Land(const float octaves, const float persistence);
    void Generate();
    void Draw(sf::RenderTarget &target);

    bool IsSolidPixel(int x, int y);
    float GetLandAngle(int x, int y);
    int GetLandHeight(const int x);

private:
    bool modified_;
    float size_;

    sf::Image image_;
    sf::Sprite sprite_;
    sf::Texture texture_;
    std::vector<int> height_;

    sf::Color Gradient(float t, sf::Color a, sf::Color b);
};
