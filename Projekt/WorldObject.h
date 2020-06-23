#pragma once

#include "Globals.h"

/**
 * @brief Enum TypeObject
 */
enum class TypeObject
{
    Bullet, /**< Pocisk */
    Land, /**< Teren */
    Tank /**< Czołg */
};

/**
 * @brief Klasa WorldObject
 */
class WorldObject
{
public:
    /**
     * @brief Wirtualna funkcja wyświetlania elementów
     * @param window - okno gry
     */
    virtual void draw(sf::RenderTarget &window) = 0;
    /**
     * @brief Wirtualna funkcja step
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    virtual void step(const float &elapsed) = 0;
    /**
     * @brief Wirtualna funkcja do resetowania wszystkich elementów do stanu początkowego
     */
    virtual void reset() = 0;
    /**
     * @brief Wirtualna funkcja do sprawdzania kolicji elementów w grze
     * @param object - element gry
     */
    virtual void getCollison(WorldObject &object) = 0;

    bool isDestructed_ = false; /**< Czy dany obiekt został zniszczony */
    TypeObject type_; /**< Typ obiektu */
};
