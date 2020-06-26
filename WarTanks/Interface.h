#pragma once

#include "Globals.h"

/**
 * @brief Klasa Interface
 */
class Interface
{
public:

    /**
     * @brief Konstruktor klasy Interface
     */
    Interface();

    /**
     * @param id - identyfikator gracza
     */
    Interface(const int &playerID);

    /**
     * @brief Resetuje parametry interface do wartości domyślnych.
     */
    void reset();

    /**
     * @brief Wyświetla napis z kątem nachylenia lufy.
     * @param angle - kąt nachylenia lufy
     * @param window - okno gry
     */
    void drawAngle(const float &angle, sf::RenderTarget &window);

    /**
     * @brief Wyświetla liczbę klatek na sekundę
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     * @param window - okno gry
     */
    void drawFPS(const float &elapsed, sf::RenderTarget &window);

    /**
     * @brief Wyświetla napis, który gracz wygrał grę. Dodatkowo po 2 sekundach wyswietla napis "Kliknij enter aby wrócić do menu".
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     * @param window - okno gry
     */
    void drawGameEnd(const float &elapsed, sf::RenderTarget &window);

    /**
     * @brief Wyświetla aktualny czas gry.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     * @param window - okno gry
     */
    void drawGameTime(const float &elapsed, sf::RenderTarget &window);

    /**
     * @brief Wyświetla pasek poziomu życia gracza.
     * @param health - poziom życia gracza
     * @param window - okno gry
     */
    void drawHealth(const int &health, sf::RenderTarget &window);

    /**
     * @brief Wyświetla pasek siły wystrzału pocisku.
     * @param shootPower - siła wystrzału pocisku
     * @param window - okno gry
     */
    void drawShootPower(const int &shootPower, sf::RenderTarget &window);

    /**
     * @brief Wyświetla napis, który gracz jest aktualnie aktywny. Nad tym napisem wyświetlony jest pozostały czas na oddanie strzału.
     * @param id - identyfikator gracza
     * @param timeLeft - pozostały czas na oddanie strzału
     * @param window - okno gry
     */
    void drawTurn(const int &id, const float &timeLeft, sf::RenderTarget &window);

    /**
     * @brief Ustawia styl dla obiektu klasy sf::Text.
     * @param size - rozmiar czcionki
     * @param thickness - grubość obramowania tekstu
     * @param position - wektor z pozycją tekstu
     * @param contents - treść napisu
     * @param fillColor - kolor tekstu
     * @param borderColor - kolor obramowania
     * @return zwraca sformatowany obiekt klast sf::Text
     */
    sf::Text setTextStyle(const int &size, const int &thickness, const string &contents = "", const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Color &fillColor = sf::Color::White, const sf::Color &borderColor = sf::Color::Black);

    /**
     * @brief Ustawia styl dla obiektu klasy sf::RectangleShape.
     * @param size - wektor z rozmiarem prostokąta
     * @param thickness - grubość obramowania
     * @param position - wektor z pozycją obiektu
     * @param fillColor - kolor wypełnienia prostokąta
     * @param borderColor - kolor obramowania
     * @return zwraca sformatowany obiekt klasy sf::Text
     */
    sf::RectangleShape setRectStyle(const sf::Vector2f &size, const int &thickness, const sf::Vector2f &position, const sf::Color &fillColor = sf::Color(0, 0, 0, 0), const sf::Color &borderColor = sf::Color(50, 50, 50));

private:

    sf::Font font_; /**< Czcionka */

    sf::Text angle_; /**< Napis zawierający kąt nachylenia lufy */
    sf::Text backToMenu_; /**< Napis pojawiający się na koniec gry, informujący aby wrócić do menu */
    sf::Text fps_; /**< Napis zawierający ilość klatek na sekundę */
    sf::Text gameEndText_; /**< Napis pojawiający się na koniec gry, informujący o zwycięzcy */
    sf::Text gameTime_; /**< Napis zawierający czas gry */
    sf::Text hpText_; /**< Napis "HP" */
    sf::Text turn_; /**< Napis informujący, którego gracza jest teraz kolej */
    sf::Text turnTimeLeft_; /**< Napis z pozostałym czasem tury danego gracza */

    float totalTime_; /**< Całkowity czas gry */
    float backToMenuTime_; /**< Upłynięty czas od zakończenia gry */

    sf::RectangleShape healthPointBorder_; /**< Obramowanie paska stanu HP */
    sf::RectangleShape healthPointFill_; /**< Pasek stanu HP */
    sf::RectangleShape shootPowerBorder_; /**< Obramowanie paska siły strzału */
    sf::RectangleShape shootPowerFill_; /**< Pasek siły strzału */
};
