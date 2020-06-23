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
     * @brief
     */
    World();
    /**
     * @brief
     */
    ~World();
    /**
     * @brief Dodaje obiekt do świata gry
     * @param type - typ dodawanego obiektu
     */
    void addObject(TypeObject type);
    /**
     * @brief Dodaje obiekt do wektora obiektów gry
     * @param object - obiekt elementu gry
     */
    void addObject(WorldObject *object);
    /**
     * @brief Wyświetla elementy
     * @param window - okno gry
     */
    void drawAll(sf::RenderWindow &window);
    /**
     * @brief stepAll
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void stepAll(const float &elapsed);
    /**
     * @brief Sprawdza kolizje elementów
     */
    void getCollisionAll();
    /**
     * @brief Resetuje wszystkie elementy do stanu początkowego
     */
    void resetAll();

    vector<unique_ptr<WorldObject>> objects_; /**< Wektor obiektów w grze */
    int PlayerIndex = 1; /**< Indeks gracza */
};
