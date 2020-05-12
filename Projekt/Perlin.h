#pragma once

#include "Globals.h"

class Perlin
{
public:
    Perlin(const float octaves, const float persistence);
    float OctaveNoise(const float x, const float y);

private:
    float Factor[2];

    const float octaves_;
    const float persistence_;

    static const int Permutation[256];
    static const int GradientsCube[12][3];

    float RawNoise(const float x, const float y);
    float GetCornerValue(const float x, const float y, const int GradientIndex);
    float MatrixDot(const int* Matrix, const float x, const float y);
    int FastFloor(const float x);
    int Hash(const int i);
};
