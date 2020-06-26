#pragma once

#include "Globals.h"

/**
 * @brief Rodzaj obiektu
 */
enum class ObjectType
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
     * @brief Wirtualny destruktor klasy WorldObject
     */
    virtual ~WorldObject(){};

    /**
     * @brief Wirtualna funkcja do wyświetlania elementów
     * @param window - okno gry
     */
    virtual void draw(sf::RenderTarget &window) = 0;

    /**
     * @brief Wirtualna funkcja do grawitacji elementów
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    virtual void step(const float &elapsed) = 0;

    /**
     * @brief Wirtualna funkcja do resetowania elementów do stanu początkowego
     */
    virtual void reset() = 0;

    /**
     * @brief Wirtualna funkcja do sprawdzania kolizji elementów w grze
     * @param object - element gry
     */
    virtual void getCollison(WorldObject &object) = 0;

    bool isDestructed_ = false; /**< Określa czy dany obiekt został zniszczony */
    ObjectType type_; /**< Typ obiektu */
};
