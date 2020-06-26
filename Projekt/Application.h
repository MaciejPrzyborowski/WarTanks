#pragma once

#include "Globals.h"
#include "Game.h"

/**
 * @brief Klasa Application
 */
class Application
{
public:

    /**
     * @brief Konstruktor klasy Application
     */
    Application() = delete;

    /**
     * @brief Uruchamia okno aplikacji
     */
    static void run();

    /**
     * @brief Zamyka okno aplikacji
     */
    static void quit();

    /**
     * @brief Zwraca okno aplikacji
     * @return Zwraca wskaźnik do okna aplikacji
     */
    static sf::RenderWindow & getWindow();

    /**
     * @brief Zwraca obiekt klasy Game
     * @return Zwraca wskaźnik do obiektu klasy Game
     */
    static Game & getGame();

private:

    static sf::RenderWindow window_; /**< Okno aplikacji */
    static Game game_; /**< Obiekt klasy Game */
};
