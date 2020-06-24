#pragma once

#include "Globals.h"
#include "Interface.h"
#include "World.h"

/**
 * @brief Enum TankState
 */
enum class TankState
{
    InActive, /**< InActive */
    Active, /**< Active */
    Switch /**< Switch */
};

/**
 * @brief Enum TankMove
 */
enum class TankMove
{
    None, /**< Czołg się nie rusza */
    Left, /**< Czołg rusza się w lewo */
    Right /**< Czołg rusza się w prawo */
};

/**
 * @brief Klasa Tank
 */
class Tank : public WorldObject
{
public:
    /**
     * @param playerID - numer id gracza
     * @param texture - tekstura czołgu
     * @param land_ - teren gry
     */
    Tank(const int playerID, const string &texture);

    /**
     * @brief Resetuje parametry gracza do domyślnych.
     */
    void reset();

    /**
     * @brief Tworzy pocisk w miejscu aktualnej pozycji celownika. Pocisk jest wystrzeliwany z mocą shootPower_ wymnożoną przez 5.
     */
    void shoot();

    /**
     * @brief Obsługuje przemieszczenie czołgu.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void moveTank(const float &elapsed);

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
     *
     */
    void moveShootPower(const int &direction);

    /**
     * @brief Aktualizuje dane gracza.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     * @param window - okno gry
     */
    void update(const float &elapsed, sf::RenderWindow &window);

    /**
     * @brief
     *
     * @param object
     */
    void getCollison(WorldObject &object);

    /**
     * @brief Wyświetla czołg i jego elementy.
     * @param window - okno gry
     */
    void draw(sf::RenderTarget &window);

    /**
     * @brief Obsługuje grawitacje gracza.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void step(const float &elapsed);

    /**
     * @brief Zwraca status gracza.
     * @return
     *        TankState::InActive - gracz aktualnie nie jest aktywny
     *        TankState::Active - gracz aktualnie jest aktywny
     *        TankState::Switch - gracz aktualnie oczekuje na zmianę kolejki
     */
    TankState getStatus();

    /**
     * @brief Zmienia status gracza.
     * @param window - okno gry
     */
    void switchStatus(sf::RenderWindow &window);

    int playerID_; /** < Identyfikator gracza */

    /**
     * @brief Zwraca punkty życia gracza.
     * @return Zwraca punkty życia gracza
     */
    inline int returnHp() {return health_;};

    /**
     * @brief Zwarca pozycje czołgu.
     * @return Zwraca pozycję czołgu
     */
    inline sf::Vector2f returnPosition() {return tankSprite_.getPosition();};

    /**
     * @brief Sprawdza czy gracz może zmienić położenie lufy.
     * @return
     *          true - gracz może zmienić położenie lufy
     *          false - gracz nie może zmienić położenia lufy
     */
    bool canCannonMove();

    /**
     * @brief Sprawdza czy czołg może przemieścić się o wektor [x, y].
     * @param velocity - wektor prędkości
     * @return
     *          true - gracz może się przemieścić swoim czołgiem
     *          false - gracz nie może się przemieścić swoim czołgiem
     */
    bool canTankMove(const sf::Vector2f &velocity);

    /**
     * @brief Oblicza nachylenie terenu po przemieszczeniu się o wektor prędkości [x, y].
     * @param velocity - wektor prędkości
     * @return Nachylenie terenu w radianach po przemieszczeniu się o wektor prędkości [x, y]
     */
    float getLandAngle(const sf::Vector2f &velocity = sf::Vector2f(0.0, 0.0));

    /**
     * @brief Przesuwa pozycję czołgu oraz jego lufy.
     * @param velocity - wektor prędkości przesunięcia gracza
     */
    void moveTankPosition(const sf::Vector2f &velocity);

    /**
     * @brief Ustawia pozycję czołgu oraz jego lufy.
     * @param position - aktualna pozycja gracza
     */
    void setTankPosition(const sf::Vector2f &position);

    /**
     * @brief Usuwa pocisk i zadaje obrażenia trafionym graczom.
     */
    void shootReset();

    /**
     * @brief Oblicza prawidłową figurę czołgu.
     * @param Tank - obiekt klasy sf::Sprite dla którego obliczana jest figura
     * @return Prawidłowa figura czołgu
     */
    sf::RectangleShape getTankShape();

    /**
     * @brief Wyłącza widocznośc kursora gdy gracz zmienia nachylenie lufy.
     * @param window - okno gry
     */
    void setCursorVisibility(sf::RenderWindow &window);
    int health_; /**< Ilość punktów życia */

    TankMove moveDirection_;
private:
    unique_ptr<Interface> tankInterface_; /**< Interface gracza */
    TankState status_; /**< Status czołgu */

    //TankMove moveDirection_;

    bool freefall_; /**< Czy czołg spada */
    bool crosshairActive_; /**< Czy celownik aktywny */
    bool getEnemyCollision_; /**< Czy jest kolizja z przeciwnikiem */

    int shootPower_; /**< Siła strzału */

    float speed_; /**< Szybkość czołgu */
    float maxAngle_; /**< Maksymalny kąt pod który czołg podjedzie i z którego może zjechać */
    float timeLeft_; /**< Pozostały czas tury danego gracza */
    float velocityFreefall_; /**< Prędkość spadania */

    sf::Sprite tankSprite_; /**< Czołg */
    sf::Sprite cannonSprite_; /**< Lufa */
    sf::Sprite crosshairSprite_; /**< Celownik */
    sf::Texture tankTexture_; /**< Tekstura czołgu */
    sf::Texture cannonTexture_; /**< Tekstura lufy */
    sf::Texture crosshairTexture_; /**< Tekstura celownika */
    sf::SoundBuffer shootBuffer_; /**< Bufer dźwięku strzału */
    sf::Sound shootSound_; /**< Dźwięk strzału */
    sf::Vector2f velocity; /**< Wektor prędkości */
};
