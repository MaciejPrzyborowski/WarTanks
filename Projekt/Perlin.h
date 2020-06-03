#pragma once

#include "Globals.h"

class Perlin
{
public:
    Perlin(const float octaves, const float persistence);
    float OctaveNoise(const float x, const float y);

private:
    float factor_[2];
    const float octaves_;
    const float persistence_;

    static const int Permutation[256];
    static const int GradientsCube[12][3];

    float rawNoise(const float x, const float y);
    float getCornerValue(const float x, const float y, const int GradientIndex);
    float matrixDot(const int* Matrix, const float x, const float y);
    int fastFloor(const float x);
    int hash(const int i);
};
