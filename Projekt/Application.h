#pragma once

#include "Globals.h"
#include "Game.h"

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
     */
    static sf::RenderWindow & getWindow();

    /**
     * @return Zwraca obiekt klasy Game
     */
    static Game & getGame();

private:

    static sf::RenderWindow window_; /**< Okno aplikacji */
    static Game game_; /**< Obiekt klasy Game */
};
