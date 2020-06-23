#pragma once

#include "Globals.h"
#include "Animation.h"
#include "Land.h"
#include "Tank.h"
#include "WorldObject.h"

/**
 * @brief Enum BulletState
 */

enum class BulletState
{
    InActive, /**< Pocisk wybuchnął i już go nie ma */
    Active, /**< Pocisk się porusza */
    Explode /**< Pocisk wybuchnął */
};

/**
 * @brief Klasa Bullet
 */

class Bullet : public WorldObject
{
public:
    /**
     * @param position - początkowa pozycja pocisku
     * @param client - obiekt z którego strzał ma wylecieć
     * @param target - przeciwnik
     * @param land_ - teren gry
     */
    Bullet(const sf::Vector2f &position);

    /**
     * @brief Przesuwa pocisk o wektor velocity_ zgodnie z upływem czasu.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void step(const float &elapsed);

    /**
     * @brief Wywołuje funkcję przesunięcia i wyświetlenia pocisku oraz jego wybuchu.
     * @param window - okno gry
     */
    void draw(sf::RenderTarget &window);
    void getCollison(WorldObject &object);
    void reset();

    /**
     * @brief Wykonuje eksplozję w miejscu kolizji.
     */
    void explode();

    /**
     * @brief Sprawdza status pocisku.
     * @return
     *          BulletState::InActive - pocisk nie jest aktywny
     *          BulletState::Active - pocisk jest aktywny, porusza i wyświetla się
     *          BulletState::Explode - pocisk exploduje w trafionym punkcie
     */
    BulletState getStatus();

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

    /**
     * @brief Sprawdza czy pocisk uderzył w gracza.
     * @param bullet - dane pocisku
     * @param Tank - dane gracza
     * @return
     *          true - pocisk uderzył w gracza
     *          false - pocisk nie uderzył w gracza
     */
    bool intersects(const sf::CircleShape &bullet, const sf::RectangleShape &Tank);

private:
    sf::Clock clock_; /**< Obiek klasy sf::Clock */
    unique_ptr<Animation> explode_; /**< Animacja wybuchu */
    BulletState status_; /**< Status pocisku */

    int explodeSize_; /**< Rozmiar wybuchu */

    sf::Sound explodeSound_; /**< Dźwięk wybuchu */
    sf::SoundBuffer explodeSoundBuffer_; /**< Bufer dźwięku wybuchu */
    sf::CircleShape bullet_; /**< Okrągły kształ pocisku */
    sf::Vector2f acceleration_; /**< Wektor przyśpieszenia */
    sf::Vector2f velocity_; /**< Wektor prędkości */
};
