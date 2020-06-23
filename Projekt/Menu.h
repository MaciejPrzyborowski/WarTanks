#pragma once

#include "Globals.h"

/**
 * @brief Enum MenuType
 */
enum class MenuType
{
    None, /**< Żadne nie jest wyrane */
    Main, /**< Memu główne */
    Settings /**< Ustawienia */
};

/**
 * @brief Klasa Menu
 */
class Menu
{
public:
    /**
     * @brief
     *
     */
    Menu();

    /**
     * @brief Resetuje układ menu do ustawień domyślnych.
     * @param settings - określa czy resetowi podlegają ustawienia gry
     *          true - resetuje ustawienia gry do domyślnych
     *          false - nie resetuje ustawień gry do domyślnych
     */
    void reset(const bool &settings);

    /**
     * @brief Zmienia aktualny wybór w menu. Funkcja przeznaczona tylko dla obsługi klawiatury.
     * @param direction - kierunek w którą stronę ma zostać dokonana zmiana
     *          -1 - w górę
     *          1 - w dół
     */
    void move(const int &direction);

    /**
     * @brief Wyświetla aktualne menu.
     * @param window - okno gry
     */
    void draw(sf::RenderTarget &window);

    /**
     * @brief Sprawdza ustawienia gry.
     * @param setting - ID ustawienia gry:
     *          0 - licznik FPS
     *          1 - muzyka w grze
     *          2 - muzyka w menu
     *          3 - dźwięki w menu
     * @return
     *          true - ustawienie jest włączone
     *          false - ustawienie jest wyłączone
     */
    bool getGameSettings(const int &setting);

    /**
     * @brief Sprawdza status menu.
     * @return
     *          true - menu jest aktywne
     *          false - menu nie jest aktywne
     */
    bool getMenuStatus();

    /**
     * @brief Ustawia dane w menu.
     * @param type - typ menu:
     *          None - brak menu
     *          Main - menu główne
     *          Settings - menu ustawień
     */
    void setMenu(const MenuType &type);

    /**
     * @brief Obsługuje wybór elementu z menu.
     * @return
     *          true - menu jest aktywne
     *          false - menu zostało zamknięte
     */
    bool getMenuChoice();

    /**
     * @brief Sprawdza czy myszka znajduje się aktualnie na wybranym elemencie. Funkcja dodatkowo ustawia element menu, na którym znajduje się myszka, jako aktywny.
     * @return
     *          true - myszka znajduje się na wybranym elemencie
     *          false - myszka nie znajduje się na wybranym elemencie
     */
    bool getMenuMouse(const sf::Vector2f &mousePosition);

    /**
     * @brief Zmienia ustawienia gry.
     * @param setting - ID ustawienia gry:
     *          0 - licznik FPS
     *          1 - muzyka w grze
     *          2 - muzyka w menu
     *          3 - dźwięki w menu
     */
    void setSettings(const int &setting);

    /**
     * @brief Sprawdza czy gracz poruszył myszką w menu.
     * @return
     *          true - gracz poruszył myszką
     *          false - gracz nie poruszył myszką
     */
    inline bool isMouseActive(){return isMouseActive_;};

    /**
     * @brief Jeżeli gracz najedzie myszką na opcje wyboru w menu to ustawi myszkę na aktywną
     * @param window - okno gry
     */
    void setMouseActive(sf::RenderWindow &window);

private:
    sf::Font font_; /**< Czcionka */
    sf::Sound menuSelectSound_; /**< Dźwięk wyboru danej opcji */
    sf::SoundBuffer menuSelectSoundBuffer_; /**< Bufer dźwięku wyboru danej opcji */

    MenuType menuType_; /**< Typ wybranego menu */
    size_t menuSelected_; /**< Indeks wybranej opcji */

    bool isMouseActive_; /**< Czy myszka jest aktywna */
    bool gameSettings_[4]; /**< Odpowiada za zmianę ustawień */

    vector<sf::Text> menuOptions_; /**< Wektor z opcjami w głównym menu */
    vector<sf::Text> menuSelectOptions_; /**< Wektor z opcjami w ustawieniach */
    vector<sf::RectangleShape> menuSelectBackground_; /**< Podświetlenie wybranej opcji w ustawieniach */
};
