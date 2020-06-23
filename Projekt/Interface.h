#pragma once

#include "Globals.h"

/**
 * @brief Enum Winner
 */
enum class Winner
{
    None, /**< Nikt nie wygrał */
    Red, /**< Wygrał gracz czerwony */
    Blue /**< Wygrał gracz niebieski */
};

/**
 * @brief Klasa Interface
 */
class Interface
{
public:

    /**
     * @brief
     *
     */
    Interface();

    /**
     * @param id - numer id gracza
     *          1 - gracz 1, kolor czerwony
     *          2 - gracz 2, kolor niebieski
     */
    Interface(const int &id);

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
     * @brief Wyświetla liczbę klatek na sekundę.
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
     * @brief Wyświetla napis, który gracz jest aktualnie aktywny. Nad tym napisem wświetla pozostały czas na oddanie strzału.
     * @param id - numer id gracza
     * @param timeLeft - pozostały czas na oddanie strzału
     * @param window - okno gry
     */
    void drawTurn(const int &id, const float &timeLeft, sf::RenderTarget &window);

    /**
     * @brief Sprawdza, który z graczy wygrał grę.
     * @param health - wektor poziomów życia graczy
     *         [0] - poziom życia pierwszego gracza
     *         [1] - poziom życia drugiego gracza
     * @param tankPosition1 - pozycja pierwszego gracza
     * @param tankPosition2 - pozycja drugiego gracza
     * @return wektor pozycji dwóch graczy dopasowana do animacji końcowych
     *         [0] - współrzędne wygranej pozycji
     *         [1] - współrzędne przegranej pozycji
     */
    vector<sf::Vector2f> checkWinner(const int *health, const sf::Vector2f &tankPosition1, const sf::Vector2f &tankPosition2);

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
    sf::Text angle_; /**< Kąt do wyświetlenia */
    sf::Text backToMenu_; /**< Napis pojawiający się na koniec gry, informujący aby wrócić do menu */
    sf::Text fps_; /**< FPS do wyświetlenia */
    sf::Text gameEndText_; /**< Napis pojawiający się na koniec gry, informujący o zwyciężcy */
    sf::Text gameTime_; /**< Czas gry do wyświetlenia */
    sf::Text hpText_; /**< Napis "HP" do wyświetlenia */
    sf::Text turn_; /**< Napis informujący, którego gracza jest teraz kolej */
    sf::Text turnTimeLeft_; /**< Napis z pozostałym czasem tury danego gracza */
    Winner winnerID_; /**< Wynik gry */

    float totalTime_; /**< Całkowity czas gry */
    float backToMenuTime_; /**< Określa po jakim czasie, po zakończeniu gry ma się pojawić napis "Kliknij enter aby wrócić do menu" */

    sf::RectangleShape shootPowerBorder_; /**< Obramowanie paska siły strzału */
    sf::RectangleShape shootPowerFill_; /**< Pasek siły strzału */
    sf::RectangleShape healthPointBorder_; /**< Obramowanie paska stanu HP */
    sf::RectangleShape healthPointFill_; /**< Pasek stanu HP */
};
