#pragma once

#include "Globals.h"
#include "World.h"
#include "Interface.h"

#include "Menu.h"
#include "Animation.h"

/**
 * @brief Enum GameState
 */
enum class GameState
{
    Menu, /**< Menu */
    Play, /**< Gra */
    EndWinner, /**< Wygrał jeden z graczy */
    EndDraw /**< Remis */
};

enum class Winner
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
     * @brief W zależności od statusu gry ustawia funkcję potrzebne do poprawnego uruchomienia menu lub gry.
     * @param gameState - status gry
     *          Menu - gracz jest w menu
     *          Play - gracz rozpoczął grę
     *          EndWinner - koniec gry - 1 z graczy wygrał
     *          EndDraw - koniec gry - remis
     */
    void initialize(const GameState &gameState);

    /**
     * @brief Obsługuje zdarzenia wykonywane przez gracza.
     * @param Event - obiekt wszystkich zdarzeń
     */
    void passEvent(sf::RenderWindow &window, sf::Event &Event);

    /**
     * @brief Aktualizuje na bieżąco wszystkie elementy gry.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void update(sf::RenderWindow &window, sf::Time &elapsed);
    /**
     * @brief Włącza muzykę w menu jeżeli opcja ta jest włączona w ustawieniach.
     * @param isMenuMusicOn - sprawdza czy muzyka w menu jest włączona
     */
    void playMenuMusic(const bool &status);

    /**
     * @brief Włącza muzykę w grze jeżeli opcja ta jest włączona w ustawieniach.
     * @param isGameMusicOn - sprawdza czy muzyka w grze jest włączona
     */
    void playGameMusic(const bool &status);

    /**
     * @brief Włącza dźwięk fajerwerków na koniec gry.
     */
    void playFireworksSound(const bool &status);

    /**
     * @brief Niszczy teren w kształcie okręgu.
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @param radius - promień okręgu do zniszczenia
     */
    inline void destroyLand(int x, int y, int radius){return land->destroyCircle(x, y, radius);}

    /**
     * @brief Oblicza kąt nachylenia powierzchni w punkcie (x, y). Tworzy kwadrat o boku 3 o środku w punkcie (x, y), następnie w całym kwadracie sumuje odległość od (x, y) dla istniejącego terenu.
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return Kąt nachylenia powierzchni w punkcie (x, y) w radianach
     */
    inline float getLandAngleRadian(int x, int y){return land->getAngleRadian(x, y);}

    /**
     * @brief Oblicza kąt nachylenia powierzchni w punkcie (x, y).
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return Kąt nachylenia powierzchni w punkcie (x, y) w stopniach
     */
    inline float getLandAngleDegree(int x, int y){return land->getAngleDegree(x, y);}

    /**
     * @brief Oblicza wysokość terenu w punkcie x.
     * @param x - współrzędna x
     * @return Wysokość terenu w punkcie x
     */
    inline int getLandHeight(int x){ return land->getHeight(x); }

    /**
     * @brief Dodaje nowy obiekt do gry.
     * @param object - obiekt, który ma zostać dodany do gry
     */
    inline void addWorldObj(WorldObject *object){ world->addObject(object); }

    /**
     * @brief Zwiększa licznik zadań do wykonania.
     */
    inline void incCounter() { ++taskCounter; }

    /**
     * @brief Zmniejsza licznik zadań do wykonania
     */
    inline void decCounter() { --taskCounter; }
    Winner winnerID_;

private:
    int taskCounter = 0; /**< Licznik zadań */
    unique_ptr<Animation> fireworks_; /**< Animacja fajerwerków */
    unique_ptr<Animation> fire_; /**< Animacja strzału */
    unique_ptr<Menu> menu_; /**< Menu */
    unique_ptr<Interface> gameInterface_; /**< Interface gry */
    unique_ptr<World> world; /**< Elementy gry */
    unique_ptr<Land>::pointer land; /**< Teren gry */

    GameState gameState_; /**< Status gry */

    sf::Vector2f winner_, loser_; /**< Wektor z pozycją wygranego, przegranego */

    sf::Texture gameBackgroundTexture_; /**< Tekstura tła gry */
    sf::Sprite gameBackgroundSprite_; /**< Tło gry */
    sf::Texture menuBackgroundTexture_; /**< Tekstura tła menu */
    sf::Sprite menuBackgroundSprite_; /**< Tło menu */

    sf::Sound menuMusic_; /**< Muzyka w menu */
    sf::Sound gameMusic_; /**< Muzyka w grze */
    sf::Sound fireworksSound_; /**< Dźwięk fajerwerków */
    sf::SoundBuffer menuMusicBuffer_; /**< Bufer muzyki w menu */
    sf::SoundBuffer gameBuffer_; /**< Bufer muzyki w grze */
    sf::SoundBuffer fireworksBuffer_; /**< Bufer dźwięku fajerwerek */
};
