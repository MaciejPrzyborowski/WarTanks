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
     * @brief Dodaje nowy obiekt do gry
     * @param object - obiekt elementu gry
     * @return Wskaźnik stworzonego obiektu
     */
    WorldObject * addObject(WorldObject *object);

    /**
     * @brief Dodaje nowy obiekt do gry
     * @param objectType - typ dodawanego obiektu
     * @return Wskaźnik stworzonego obiektu
     */
    WorldObject * addObject(const ObjectType &objectType);

    /**
     * @brief Określa obiekty w grze
     * @return Zwraca wskaźnik do wszystkich obiektów w grze
     */
    vector<unique_ptr<WorldObject>> * getObjects();

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

private:

    int PlayerIndex = 0; /**< Aktualny indeks gracza */
    vector<unique_ptr<WorldObject>> objects_; /**< Wektor obiektów w grze */
};
