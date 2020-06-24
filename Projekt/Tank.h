#pragma once

#include "Globals.h"
#include "Interface.h"
#include "World.h"

/**
 * @brief Status czołgu
 */
enum class TankState
{
    InActive, /**< Czołg jest nieaktywny */
    Active, /**< Czołg jest aktywny */
    Waiting /**< Czołg oczekuje na zmianę tury */
};

/**
 * @brief Kierunek przemieszczenia czołgu
 */
enum class TankMove
{
    Left = -1, /**< Przemieszczenie w lewo */
    None, /**< Brak przemieszczenia */
    Right /**< Przemieszczenie w lewo */
};

/**
 * @brief Kierunek przemieszczenia siły strzału
 */
enum class ShootPowerMove
{
    LevelDown = -1, /**< Zwiększenie siły wystrzału */
    LevelUp = 1 /**< Zmniejszenie siły wystrzału */
};

/**
 * @brief Klasa Tank
 */
class Tank : public WorldObject
{
public:

    /**
     * @param playerID - ID gracza
     */
    Tank(const int playerID);

    /**
     * @brief Resetuje parametry czołgu do ustawień domyślnych.
     */
    void reset();

    /**
     * @brief Tworzy pocisk w miejscu aktualnej pozycji celownika.
     */
    void shoot();

    /**
     * @brief Zmienia kąt nachylenia lufy.
     * @param window - okno gry
     */
    void moveCannon(sf::RenderWindow &window);

    /**
     * @brief Zmienia siłę wystrzału pocisku.
     * @param direction - kierunek zmiany siły wystrzału pocisku
     *          1 - zwiększenie siły wystrzału pocisku
     *          -1 - zmniejszenie siły wystrzału pocisku
     */
    void moveShootPower(const ShootPowerMove &direction);

    /**
     * @brief Obsługuje grawitacje i przemieszczenie gracza.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void step(const float &elapsed);

    /**
     * @brief Sprawdza kolizje z innymi obiektami.
     * @param object - obiekt elementu gry
     */
    void getCollison(WorldObject &object);

    /**
     * @brief Aktualizuje dane gracza.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     * @param window - okno gry
     */
    void update(const float &elapsed, sf::RenderWindow &window);

    /**
     * @brief Wyświetla czołg i jego elementy.
     * @param window - okno gry
     */
    void draw(sf::RenderTarget &window);

    /**
     * @brief Ustawia kierunek przemieszczenia czołgu
     * @param direction - kierunek przemieszczenia
     */
    void setMoveDirection(const TankMove &direction);

    /**
     * @brief Ustawia poziom życia gracza
     * @param health - poziom życia
     */
    void setPlayerHealth(const int &health);

    /**
     * @brief Zmienia status widoczności kursora.
     * @param window - okno gry
     */
    void switchCursorVisibility(sf::RenderWindow &window);

    /**
     * @brief Zmienia status gracza.
     * @param window - okno gry
     */
    void switchStatus(sf::RenderWindow &window);

    /**
     * @brief Określa poziom życia gracza.
     * @return Zwraca poziom życia gracza
     */
    int getPlayerHealth();

    /**
     * @brief Określa identyfikator czołgu.
     * @return Zwraca identyfikator czołgu
     */
    int getTankID();

    /**
     * @brief Zwraca status gracza.
     * @return
     *        TankState::InActive - czołg jest nieaktywny;
     *        TankState::Active - czołg jest aktywny;
     *        TankState::Waiting - czołg oczekuje na zmianę tury
     */
    TankState getStatus();

    /**
     * @brief Określa pozycje czołgu.
     * @return Zwraca pozycję czołgu
     */
    sf::Vector2f getTankPosition();

    /**
     * @brief Oblicza prawidłową figurę czołgu.
     * @param Tank - obiekt klasy sf::Sprite dla którego obliczana jest figura
     * @return Prawidłowa figura czołgu
     */
    sf::RectangleShape getTankShape();

private:
    TankState status_; /**< Status czołgu */
    TankMove moveDirection_; /**< Kierunek przemieszczenia czołgu */
    sf::Vector2f velocity; /**< Wektor prędkości czołgu */
    unique_ptr<Interface> tankInterface_; /**< Interface gracza */

    bool freefall_; /**< Określa czy czołg spada */
    bool crosshairActive_; /**< Określa czy celownik jest aktywny */
    bool getCollision_; /**< Określa czy jest kolizja z przeciwnikiem */

    int health_; /**< Ilość punktów życia */
    int playerID_; /** < Identyfikator gracza */
    int shootPower_; /**< Siła strzału */

    float speed_; /**< Szybkość czołgu */
    float timeLeft_; /**< Pozostały czas tury danego gracza */
    float velocityFreefall_; /**< Prędkość spadania czołgu */

    sf::Sprite tankSprite_; /**< Czołg */
    sf::Sprite cannonSprite_; /**< Lufa */
    sf::Sprite crosshairSprite_; /**< Celownik */
    sf::Sound shootSound_; /**< Dźwięk strzału */
    sf::SoundBuffer shootBuffer_; /**< Bufer dźwięku strzału */
    sf::Texture tankTexture_; /**< Tekstura czołgu */
    sf::Texture cannonTexture_; /**< Tekstura lufy */
    sf::Texture crosshairTexture_; /**< Tekstura celownika */

    /**
     * @brief Sprawdza czy gracz może zmienić położenie lufy.
     * @return
     *        true - gracz może zmienić położenie lufy;
     *        false - gracz nie może zmienić położenia lufy
     */
    bool canCannonMove();

    /**
     * @brief Sprawdza czy czołg może przemieścić się o wektor [x, y].
     * @param velocity - wektor prędkości
     * @return
     *        true - gracz może się przemieścić swoim czołgiem;
     *        false - gracz nie może się przemieścić swoim czołgiem
     */
    bool canTankMove(const sf::Vector2f &velocity);

    /**
     * @brief Oblicza nachylenie terenu po przemieszczeniu się o wektor prędkości [x, y].
     * @param velocity - wektor prędkości
     * @return Nachylenie terenu w radianach po przemieszczeniu się o wektor prędkości [x, y]
     */
    float getTankAngle(const sf::Vector2f &velocity = sf::Vector2f(0.0, 0.0));
};
