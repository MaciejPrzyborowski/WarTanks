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
     */
    void reset();

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
     * @brief Sprawdza status menu.
     * @return
     *          true - menu jest aktywne;
     *          false - menu nie jest aktywne
     */
    bool getStatus();

    /**
     * @brief Sprawdza czy myszka znajduje się na aktualnie wybranym elemencie.
     * @return
     *        true - myszka znajduje się na aktualnie wybranym elemencie;
     *        false - myszka nie znajduje się na aktualnie wybranym elemencie
     */
    bool getMouseStatus();

    /**
     * @brief Obsługuje wybór elementu z menu.
     */
    void getChoice();

    /**
     * @brief Ustawia element menu, na którym znajduje się myszka, jako aktywny.
     */
    void getMouse(const sf::Vector2f &mousePosition);

    /**
     * @brief Włącza lub wyłącza muzykę w menu.
     * @param status - określa czy ma włączyć czy wyłączyć muzykę
     */
    void playMusic(const bool &status);

    /**
     * @brief Ustawia głośność dźwięku wyboru elementu z menu
     * @param volume - wartość głośności
     */
    void setSelectVolume(const float &volume);

private:

    sf::Font font_; /**< Czcionka */
    sf::Sound music_; /**< Muzyka w menu */
    sf::Sound selectSound_; /**< Dźwięk wyboru danej opcji */
    sf::Sprite backgroundSprite_; /**< Tło menu */
    sf::Texture backgroundTexture_; /**< Tekstura tła menu */
    sf::SoundBuffer musicBuffer_; /**< Bufer muzyki w menu */
    sf::SoundBuffer selectSoundBuffer_; /**< Bufer dźwięku wyboru danej opcji */

    MenuType type_; /**< Typ aktualnego menu */
    size_t selected_; /**< Indeks wybranej opcji */

    bool isMouseActive_; /**< Określa czy myszka najeżdza na wybraną obcję */

    vector<sf::Text> options_; /**< Wektor z opcjami w głównym menu */
    vector<sf::Text> selectOptions_; /**< Wektor z opcjami w ustawieniach */
    vector<sf::RectangleShape> selectBackground_; /**< Tło wybranej opcji w ustawieniach */

    /**
     * @brief Ustawia dane w menu.
     * @param menuType - ustawienia gry
     * @param resetMenuSelect - określa czy ma resetować aktualny wybór w menu
     */
    void initialize(const MenuType &type, const bool &resetSelect = true);
};
