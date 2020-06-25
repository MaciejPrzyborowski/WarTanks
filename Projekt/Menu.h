#pragma once

#include "Globals.h"

/**
 * @brief Typ menu
 */
enum class MenuType
{
    None, /**< Brak menu */
    Main, /**< Menu główne */
    Settings /**< Menu ustawień */
};

/**
 * @brief Kierunek zmiany wyboru menu
 */
enum class MenuMove
{
    Up = -1, /**< W górę */
    Down = 1 /**< W dół */
};

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
 * @brief Klasa Menu
 */
class Menu
{
public:
    /**
     * @brief Konstruktor klasy Menu
     */
    Menu();

    /**
     * @brief Resetuje parametry menu do ustawień domyślnych.
     * @param settings - określa czy resetowi podlegają ustawienia gry
     */
    void reset(const bool &settings);

    /**
     * @brief Zmienia aktualny wybór w menu. Funkcja przeznaczona tylko dla obsługi klawiatury.
     * @param direction - kierunek zmiany wyboru menu
     */
    void move(const MenuMove &direction);

    /**
     * @brief Wyświetla aktualne menu.
     * @param window - okno gry
     */
    void draw(sf::RenderTarget &window);

    /**
     * @brief Sprawdza ustawienia gry.
     * @param setting - Ustawienia gry
     * @return
     *          true - ustawienie jest włączone;
     *          false - ustawienie jest wyłączone
     */
    bool getGameSettings(const GameSetting &gameSetting);

    /**
     * @brief Sprawdza status menu.
     * @return
     *          true - menu jest aktywne;
     *          false - menu nie jest aktywne
     */
    bool getMenuStatus();

    /**
     * @brief Ustawia dane w menu.
     * @param menuType - ustawienia gry
     */
    void setMenu(const MenuType &menuType);

    /**
     * @brief Obsługuje wybór elementu z menu.
     */
    void getMenuChoice();

    /**
     * @brief Sprawdza czy myszka znajduje się aktualnie na wybranym elemencie. Funkcja dodatkowo ustawia element menu, na którym znajduje się myszka, jako aktywny.
     * @return
     *          true - myszka znajduje się na wybranym elemencie;
     *          false - myszka nie znajduje się na wybranym elemencie
     */
    bool getMenuMouse(const sf::Vector2f &mousePosition);

    /**
     * @brief Zmienia ustawienia gry.
     * @param setting - ustawienia gry
     */
    void setSettings(const GameSetting &gameSetting);

    /**
     * @brief Sprawdza czy gracz poruszył myszką w menu.
     * @return
     *          true - gracz poruszył myszką;
     *          false - gracz nie poruszył myszką
     */
    bool isMouseActive();

    /**
     * @brief Jeżeli gracz najedzie myszką na opcje wyboru w menu to ustawi myszkę na aktywną
     * @param window - okno gry
     */
    void setMouseActive(sf::RenderWindow &window);

private:
    sf::Font font_; /**< Czcionka */
    sf::Sound menuSelectSound_; /**< Dźwięk wyboru danej opcji */
    sf::SoundBuffer menuSelectSoundBuffer_; /**< Bufer dźwięku wyboru danej opcji */

    MenuType menuType_; /**< Typ aktualnego menu */
    size_t menuSelected_; /**< Indeks wybranej opcji */

    bool isMouseActive_; /**< Określa czy myszka najeżdza na wybraną obcję */
    bool gameSettings_[4]; /**< Określa status ustawień gry */

    vector<sf::Text> menuOptions_; /**< Wektor z opcjami w głównym menu */
    vector<sf::Text> menuSelectOptions_; /**< Wektor z opcjami w ustawieniach */
    vector<sf::RectangleShape> menuSelectBackground_; /**< Tło wybranej opcji w ustawieniach */
};
