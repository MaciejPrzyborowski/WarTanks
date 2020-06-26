#pragma once

#include "Globals.h"
#include "World.h"
#include "Interface.h"

#include "Menu.h"
#include "Animation.h"

/**
 * @brief Ustawienia gry
 */
enum class GameSetting
{
    FPS, /**< Licznik FPS */
    GameMusic, /**< Muzyka w grze */
    MenuMusic, /**< Muzyka w menu */
    SoundMusic /**< Dźwięki w menu */
};

/**
 * @brief Stan gry
 */
enum class GameState
{
    Menu, /**< Menu */
    Play, /**< Gra */
    EndWinner, /**< Wygrał jeden z graczy */
    EndDraw /**< Remis */
};

/**
 * @brief Rodzaj wygranej gry
 */
enum class WinnerType
{
    None,
    Red,
    Blue,
    Draw
};

/**
 * @brief Klasa Game
 */
class Game
{
public:

    /**
     * @brief Konstruktor klasy Game
     */
    Game();

    /**
     * @brief Odpala grę.
     */
    void run();

    /**
     * @brief Initializuje poszczególne stany gry.
     * @param gameState - stan gry
     */
    void initialize(const GameState &gameState);

    /**
     * @brief Obsługuje zdarzenia wykonane przez gracza.
     * @param event - obiekt wszystkich zdarzeń
     */
    void passEvent(sf::RenderWindow &window, sf::Event &Event);

    /**
     * @brief Aktualizuje na bieżąco wszystkie elementy gry oraz je wyświetla.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void update(sf::RenderWindow &window, sf::Time &elapsed);

    /**
     * @brief Sprawdza ustawienia gry.
     * @param setting - Ustawienia gry
     * @return
     *          true - ustawienie jest włączone;
     *          false - ustawienie jest wyłączone
     */
    bool getSettings(const GameSetting &gameSetting);

    /**
     * @brief Zmienia ustawienia gry.
     * @param setting - ustawienia gry
     */
    void setSettings(const GameSetting &gameSetting);

    /**
     * @brief Włącza lub wyłącza muzykę w grze.
     * @param status - określa czy ma włączyć czy wyłączyć muzykę
     */
    void playGameMusic(const bool &status);

    /**
     * @brief Włącza lub wyłącza dźwięk fajerwerków.
     * @param status - określa czy ma włączyć czy wyłączyć muzykę
     */
    void playFireworksSound(const bool &status);

    /**
     * @brief Usuwa teren w kształcie koła o środku w punkcie (x, y) i promieniu r.
     * @param x - współrzędna x dla środka koła
     * @param y - współrzędna y dla środka koła
     * @param r - promień koła
     */
    inline void destroyLand(const int &x, const int &y, const int &r) { return land -> destroyCircle(x, y, r); }

    /**
     * @brief Oblicza kąt nachylenia powierzchni w punkcie (x, y).
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return Kąt nachylenia powierzchni w punkcie (x, y) w stopniach
     */
    inline float getLandAngleDegree(const int &x, const int &y) { return land -> getAngleDegree(x, y); }

    /**
     * @brief Oblicza kąt nachylenia powierzchni w punkcie (x, y). Tworzy kwadrat o boku 3 o środku w punkcie (x, y), następnie w całym kwadracie sumuje odległość od (x, y) dla istniejącego terenu.
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return Kąt nachylenia powierzchni w punkcie (x, y) w radianach
     */
    inline float getLandAngleRadian(const int &x, const int &y) { return land -> getAngleRadian(x, y); }

    /**
     * @brief Oblicza wysokość terenu w punkcie x.
     * @param x - współrzędna x
     * @return Wysokość terenu w punkcie x
     */
    inline int getLandHeight(const int &x) { return land -> getHeight(x); }

    /**
     * @brief Dodaje nowy obiekt do gry
     * @param object - obiekt elementu gry
     * @return Wskaźnik stworzonego obiektu
     */
    inline WorldObject * addWorldObj(WorldObject *object){ return world -> addObject(object); }

    /**
     * @brief Dodaje nowy obiekt do gry
     * @param objectType - typ dodawanego obiektu
     * @return Wskaźnik stworzonego obiektu
     */
    inline WorldObject * addWorldObj(const ObjectType &objectType){ return world -> addObject(objectType); }

    /**
     * @brief Zwiększa licznik zadań do wykonania.
     */
    inline void incCounter() { ++taskCounter; }

    /**
     * @brief Zmniejsza licznik zadań do wykonania
     */
    inline void decCounter() { --taskCounter; }

    /**
     * @brief Określa zwycięzcę gry
     * @return Zwraca aktualnego zwycięzcę gry
     */
    inline WinnerType getWinnerID() { return winnerID_; };

private:

    int taskCounter = 0; /**< Licznik zadań */
    bool gameSettings_[4]; /**< Określa status ustawień gry */
    GameState gameState_; /**< Aktualny stan gry */
    WinnerType winnerID_; /**< Aktualny zwycięzca gry */

    unique_ptr<Animation> fireworks_; /**< Animacja fajerwerków */
    unique_ptr<Animation> fire_; /**< Animacja strzału */
    unique_ptr<Interface> gameInterface_; /**< Interface gry */
    unique_ptr<Menu> menu_; /**< Menu */
    unique_ptr<World> world; /**< Elementy gry */
    unique_ptr<Land>::pointer land; /**< Teren gry */

    sf::Sound music_; /**< Muzyka w grze */
    sf::Sound fireworksSound_; /**< Dźwięk fajerwerków */
    sf::Sprite backgroundSprite_; /**< Tło gry */
    sf::Texture backgroundTexture_; /**< Tekstura tła gry */
    sf::SoundBuffer musicBuffer_; /**< Bufer muzyki w grze */
    sf::SoundBuffer fireworksBuffer_; /**< Bufer dźwięku fajerwerek */
};
