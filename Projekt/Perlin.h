#pragma once

#include "Globals.h"

/**
 * @brief Klasa Perlin
 */
class Perlin
{
public:

    /**
     * @brief Konstruktor klasy Perlin
     * @param octaves - liczba oktaw (poziom szczegółowości hałasu)
     * @param persistence - liczba określająca, ile każda oktawa przyczynia się do ogólnego kształu
     */
    Perlin(const float &octaves, const float &persistence);

    /**
     * @brief Sumuje wartości szumów Perlina w punkcie [x, y] dla kolejnych oktaw. Do każdej oktawy zostanie dodana większa częstotliwość / mniejsza amplituda.
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return Suma wartości szumów Perlina, która jest dopasowana do wysokości okna
     */
    float octaveNoise(const float &x, const float &y);

private:
    float factor_[2]; /**< Skewing Factor (~0.366025), Unskewing Factor (~0.211325) */
    const float octaves_; /**< Liczba oktaw (poziom szczegółowości hałasu) */
    const float persistence_; /**< Liczba określająca, ile każda oktawa przyczynia się do ogólnego kształu */

    /**
     * @brief Tablica zdefiniowana przez Ken Perlin. Permutacja jest losowo ułożona z liczb od 0 do 255.
     */
    static const int permutation[256];

    /**
     * @brief Wektory punktów środka sześcianu.
     */
    static const int gradientsCube[12][3];

    /**
     * @brief Oblicza wartość szumu Perlina w punkcie [x, y].
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return Wartość szumu w zakresie [-1, 1]
     */
    float rawNoise(const float &x, const float &y);

    /**
     * @brief Oblicza wartość wkładu jednego rogu.
     * @param x - wartość x
     * @param y - wartość y
     * @param gradientIndex - wartość gradientu
     * @return Wartość wkładu jednego rogu
     */
    float getCornerValue(const float &x, const float &y, const int &gradientIndex);

    /**
     * @brief Oblicza wyznacznik macierzy.
     * @param matrix - macierz
     * @param x - wartość zmiennoprzecinkowa
     * @param y - wartość zmiennoprzecinkowa
     * @return Wyznacznik macierzy w zależności od wartości x i y
     */
    float matrixDot(const int *matrix, const float &x, const float &y);

    /**
     * @brief Oblicza największą wartość całkowitą liczby dla wartości zmiennoprzecinkowej.
     * @param x - wartość zmiennoprzecinkowa
     * @return Największa wartość całkowita liczby dla wartości zmiennoprzecinkowej
     */
    int fastFloor(const float &x);

    /**
     * @brief Oblicza wartość permutacji dla podanej wartości całkowitej.
     * @param i - wartość całkowita
     * @return Wartość permutacji dla podanej wartości całkowitej
     */
    int hash(const int &i);
};
