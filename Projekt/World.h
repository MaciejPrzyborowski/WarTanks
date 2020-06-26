#pragma once

#include "Globals.h"
#include "WorldObject.h"

#include "Land.h"
#include "Tank.h"
#include "Bullet.h"

/**
 * @brief Klasa World
 */
class World
{
public:

    /**
     * @brief Konstruktor klasy World
     */
    World();

    /**
     * @brief Destruktor klasy (domyślny)
     */
    ~World() = default;

    /**
     * @brief Dodaje obiekt do wektora obiektów gry
     * @param object - obiekt elementu gry
     */
    WorldObject * addObject(WorldObject *object);

    /**
     * @brief Dodaje obiekt do świata gry
     * @param objectType - typ dodawanego obiektu
     */
    WorldObject * addObject(const ObjectType &objectType);

    /**
     * @brief Resetuje wszystkie elementy do stanu początkowego
     */
    void resetAll();

    /**
     * @brief stepAll
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void stepAll(const float &elapsed);

    /**
     * @brief Sprawdza kolizje z innymi obiektami
     */
    void getCollisionAll();

    /**
     * @brief Wyświetla elementy
     * @param window - okno gry
     */
    void drawAll(sf::RenderWindow &window);

    vector<unique_ptr<WorldObject>> objects_; /**< Wektor obiektów w grze */

private:

    int PlayerIndex = 0; /**< Aktualny indeks gracza */
};
