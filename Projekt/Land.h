#pragma once

#include "Globals.h"
#include "Perlin.h"

class Land : Perlin
{
public:
    Land(const float octaves, const float persistence);
    void Generate();
    void draw(sf::RenderTarget &target);

    bool IsSolidPixel(int x, int y);
    float GetAngleRadian(int x, int y);
    float GetAngleDegree(int x, int y);
    int GetLandHeight(const int x);
    std::vector<int> height_;

private:
    bool modified_;
    float size_;

    sf::Image image_;
    sf::Sprite sprite_;
    sf::Texture texture_;

    sf::Color Gradient(float t, sf::Color a, sf::Color b);
};
