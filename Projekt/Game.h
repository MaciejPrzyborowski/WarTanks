#pragma once

#include "Tank.h"
#include "Menu.h"
#include "Globals.h"
#include "Interface.h"
#include "Animation.h"
#include "World.h"
#include "Controll.h"

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

/**
 * @brief Klasa Game
 */
class Game
{
public:
    /**
     * @brief
     *
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
    void updateAll(sf::RenderWindow &window, sf::Time &elapsed);
    /**
     * @brief Włącza muzykę w menu jeżeli opcja ta jest włączona w ustawieniach.
     * @param isMenuMusicOn - sprawdza czy muzyka w menu jest włączona
     */
    void playMenuMusic(const bool &isMenuMusicOn);

    /**
     * @brief Włącza muzykę w grze jeżeli opcja ta jest włączona w ustawieniach.
     * @param isGameMusicOn - sprawdza czy muzyka w grze jest włączona
     */
    void playGameMusic(const bool &isGameMusicOn);

    /**
     * @brief Włącza dźwięk fajerwerków na koniec gry.
     */
    void playFireworksSound();

    void addWorldObj(WorldObject *wo){ world.addObject(wo); }
    inline void incCounter() { ++taskCounter; }
    inline void decCounter() { --taskCounter; }

private:

    int taskCounter = 0;
    unique_ptr<Animation> fireworks_; /**< Animacja fajerwerków */
    unique_ptr<Animation> fire_; /**< Animacja strzału */
    unique_ptr<Menu> menu_; /**< Menu */
    unique_ptr<Interface> GameInterface_; /**< Interface gry */
    World world; /**< Elementy gry */

    Controll controll_; /**< Kontroler gracza */
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
