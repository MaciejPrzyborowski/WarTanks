#pragma once

#include "Globals.h"
#include "Animation.h"
#include "WorldObject.h"

/**
 * @brief Klasa Bullet
 */
class Bullet : public WorldObject
{
public:

    /**
     * @param position - początkowa pozycja pocisku
     */
    Bullet(const sf::Vector2f &position);

    /**
     * @brief Resetuje parametry pocisku.
     */
    void reset();

    /**
     * @brief Sprawdza kolizje z innymi obiektami.
     * @param object - obiekt elementu gry
     */
    void getCollison(WorldObject &object);

    /**
     * @brief Przesuwa pocisk o wektor velocity_ zgodnie z upływem czasu.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void step(const float &elapsed);

    /**
     * @brief Wyświetla pocisk oraz jego wybuch.
     * @param window - okno gry
     */
    void draw(sf::RenderTarget &window);

    /**
     * @brief Sprawdza czy pocisk wybuchł
     * @return
     *        true - pocisk nie wybuchł;
     *        false - pocisk wybuchł
     */
    bool getStatus();

    /**
     * @brief Ustawia przyśpieszenie pocisku.
     * @param acceleration - przyspieszenie pocisku dla współrzędnych (x, y)
     */
    void setAcceleration(const sf::Vector2f &acceleration);

    /**
     * @brief Ustawia prędkość pocisku.
     * @param velocity - prędkość pocisku dla współrzędnych (x, y)
     */
    void setVelocity(const sf::Vector2f &velocity);

private:
    sf::Clock clock_; /**< Upłynięty czas */
    unique_ptr<Animation> explode_; /**< Animacja wybuchu */

    bool status_; /**< Status pocisku */

    int players_; /**< Ilość graczy */
    int explodeSize_; /**< Rozmiar wybuchu */

    sf::Sound explodeSound_; /**< Dźwięk wybuchu */
    sf::SoundBuffer explodeSoundBuffer_; /**< Bufer dźwięku wybuchu */
    sf::CircleShape bullet_; /**< Kształt pocisku */
    sf::Vector2f acceleration_; /**< Wektor przyśpieszenia */
    sf::Vector2f velocity_; /**< Wektor prędkości */

    /**
     * @brief Wykonuje eksplozję w miejscu kolizji.
     */
    void explode();

    /**
     * @brief Sprawdza czy pocisk uderzył w gracza.
     * @param bullet - dane pocisku
     * @param Tank - dane gracza
     * @return
     *        true - pocisk uderzył w gracza;
     *        false - pocisk nie uderzył w gracza
     */
    bool intersects(const sf::CircleShape &bullet, const sf::RectangleShape &Tank);
};
