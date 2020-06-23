#include "Perlin.h"


const int Perlin::permutation[256] =
{
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
    8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117,
    35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
    134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41,
    55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89,
    18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226,
    250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
    189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43,
    172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
    228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239,
    107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
    138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

const int Perlin::gradientsCube[12][3] =
{
    {1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
    {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
    {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}
};

Perlin::Perlin(const float &octaves, const float &persistence) :
    octaves_(octaves),
    persistence_(persistence)
{
    factor_[0] = 0.5 * (sqrtf(3.0) - 1.0); // Skewing Factor (~0.366025)
    factor_[1] = (3.0 - sqrtf(3.0)) / 6.0; // Unskewing Factor (~0.211325)
}

float Perlin::octaveNoise(const float &x, const float &y)
{
    float total = 0;
    float frequency = 1;
    float amplitude = 1;
    float maxAmplitude = 0;
    for(int i = 0; i < octaves_; i++)
    {
        total += rawNoise(x * frequency, y * frequency) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= persistence_;
        frequency *= 2;
    }
    return (total / maxAmplitude) * (WindowHeight) / 3 + (WindowHeight) / 3;
}

float Perlin::rawNoise(const float &x, const float &y)
{
    float Noise[3];

    int SimplexCell[2][3];
    float SkewedCell = (x + y) * factor_[0];
    SimplexCell[0][0] = fastFloor(x + SkewedCell);
    SimplexCell[1][0] = fastFloor(y + SkewedCell);

    float CellOrigin[2][3];
    float UnSkewedCell = (SimplexCell[0][0] + SimplexCell[1][0]) * factor_[1];
    CellOrigin[0][0] = x - SimplexCell[0][0] + UnSkewedCell;
    CellOrigin[1][0] = y - SimplexCell[1][0] + UnSkewedCell;
    if(CellOrigin[0][0] > CellOrigin[1][0])
    {
        SimplexCell[0][1] = 1;
        SimplexCell[1][1] = 0;
    }
    else
    {
        SimplexCell[0][1] = 0;
        SimplexCell[1][1] = 1;
    }
    CellOrigin[0][1] = CellOrigin[0][0] - SimplexCell[0][1] + factor_[1];
    CellOrigin[1][1] = CellOrigin[1][0] - SimplexCell[1][1] + factor_[1];
    CellOrigin[0][2] = CellOrigin[0][0] - 1.0 + 2.0 * factor_[1];
    CellOrigin[1][2] = CellOrigin[1][0] - 1.0 + 2.0 * factor_[1];
    SimplexCell[0][2] = SimplexCell[0][0] & 255;
    SimplexCell[1][2] = SimplexCell[1][0] & 255;

    int GradientIndex[3];
    GradientIndex[0] = hash(SimplexCell[0][2] + hash(SimplexCell[1][2])) % 12;
    GradientIndex[1] = hash(SimplexCell[0][2] + SimplexCell[0][1] + hash(SimplexCell[1][2] + SimplexCell[1][1])) % 12;
    GradientIndex[2] = hash(SimplexCell[0][2] + 1 + hash(SimplexCell[1][2] + 1)) % 12;
    for(int i = 0; i < 3; i++)
    {
        Noise[i] = getCornerValue(CellOrigin[0][i], CellOrigin[1][i], GradientIndex[i]);
    }
    return 70.0 * (Noise[0] + Noise[1] + Noise[2]);
}

float Perlin::getCornerValue(const float &x, const float &y, const int &gradientIndex)
{
    float CornerValue = 0.5 - powf(x, 2) - powf(y, 2);
    if(CornerValue < 0)
    {
        return 0.0;
    }
    return (powf(CornerValue, 4) * matrixDot(gradientsCube[gradientIndex], x, y));
}

float Perlin::matrixDot(const int *matrix, const float &x, const float &y)
{
    return matrix[0] * x + matrix[1] * y;
}

int Perlin::fastFloor(const float &x)
{
    return (x > 0.0) ? (int)x : (int)(x - 1.0);
}

int Perlin::hash(const int &i)
{
    return permutation[i & 255];
}
