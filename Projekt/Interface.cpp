#include "Interface.h"

Interface::Interface() :
    totalTime_(0.0),
    backToMenuTime_(0.0)
{
    font_.loadFromFile(GameFontSrc);
    backToMenu_ = setTextStyle(20, 3, "Kliknij enter aby wrocic do menu");
    backToMenu_.setPosition(sf::Vector2f((WindowWidth - backToMenu_.getLocalBounds().width) / 2, 570));
    fps_ = setTextStyle(15, 1, "", sf::Vector2f(2, 2));
    gameTime_ = setTextStyle(20, 2);
    gameEndText_ = setTextStyle(50, 3);
}

Interface::Interface(const int id) :
    totalTime_(0.0),
    backToMenuTime_(0.0)
{
    font_.loadFromFile(GameFontSrc);
    angle_ = setTextStyle(18, 2);
    hpText_ = setTextStyle(22, 1, "HP", sf::Vector2f(0, 0));
    shootPowerBorder_ = setRectStyle(sf::Vector2f(100, 20), 3, sf::Vector2f(350, 40));
    shootPowerFill_.setPosition(350, 40);
    turn_ = setTextStyle(20, 3);
    turnTimeLeft_ = setTextStyle(18, 2);
    if(id == 1)
    {
        hpText_.setFillColor(sf::Color::Red);
        hpText_.setPosition(60, 26);
        healthPointBorder_ = setRectStyle(sf::Vector2f(100, 20), 3, sf::Vector2f(20, 30));
        healthPointFill_.setPosition(20, 30);
    }
    else if(id == 2)
    {
        hpText_.setFillColor(sf::Color(0, 100, 255));
        hpText_.setPosition(720, 26);
        healthPointBorder_ = setRectStyle(sf::Vector2f(100, 20), 3, sf::Vector2f(680, 30));
        healthPointFill_.setPosition(680, 30);
    }
}

/**
 * Resetuje parametry interface do wartości domyślnych
 */
void Interface::reset()
{
    winnerID_ = Winner::None;
    backToMenuTime_ = 0.0;
    totalTime_ = 0.0;
}

/**
 * Wyświetla napis z kątem nachylenia lufy
 *
 * @param angle - kąt nachylenia lufy
 * @param window - okno gry
 */
void Interface::drawAngle(const float angle, sf::RenderTarget &window)
{
    angle_.setPosition(sf::Vector2f((WindowWidth - angle_.getLocalBounds().width)/2, 65));
    angle_.setString("Kat lufy: " + to_string((int)(angle)));
    window.draw(angle_);
}

/**
 * Wyświetla licznik FPS (liczba klatek na sekundę)
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 * @param window - okno gry
 */
void Interface::drawFPS(const float elapsed, sf::RenderTarget &window)
{
    fps_.setString(to_string((int)(1 / elapsed)) + " FPS");
    window.draw(fps_);
}

/**
 * Wyświetla aktualny czas gry
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 * @param window - okno gry
 */
void Interface::drawGameTime(const float elapsed, sf::RenderTarget &window)
{
    totalTime_ += elapsed;
    gameTime_.setString("Czas: " + to_string((int)totalTime_) + " sekund");
    gameTime_.setPosition(sf::Vector2f((WindowWidth - gameTime_.getLocalBounds().width) / 2, 5));
    window.draw(gameTime_);
}

/**
 * Wyświetla pasek poziomu życia gracza
 *
 * @param health - poziom życia gracza
 * @param window - okno gry
 */
void Interface::drawHealth(int health, sf::RenderTarget &window)
{
    if(health < 0)
    {
        health = 0;
    }
    healthPointFill_.setSize(sf::Vector2f(health, 20));
    healthPointFill_.setFillColor(sf::Color(200 - health, 2 * health, 0));

    window.draw(healthPointFill_);
    window.draw(healthPointBorder_);
    window.draw(hpText_);
}

/**
 * Wyświetla pasek siły wystrzału pocisku
 *
 * @param shootPower - siła wystrzału pocisku gracza
 * @param window - okno gry
*/
void Interface::drawShootPower(const int shootPower, sf::RenderTarget &window)
{
    shootPowerFill_.setSize(sf::Vector2f(shootPower, 20));
    shootPowerFill_.setFillColor(sf::Color(200 - shootPower, 2 * shootPower, 0));
    window.draw(shootPowerFill_);
    window.draw(shootPowerBorder_);
}

/**
 * Wyświetla napis, który gracz jest aktualnie aktywny
 * Nad napisem wyświetlony jest pozostały czas na oddanie strzału
 *
 * @param id - identyfikator gracza
 * @param timeLeft - pozostały czas na oddanie strzału
 * @param window - okno gry
 */
void Interface::drawTurn(const int id, const float timeLeft, sf::RenderTarget &window)
{
    if(id == 1)
    {
        turn_.setString("Kolej gracza czerwonego");
        turn_.setFillColor(sf::Color::Red);
    }
    else if(id == 2)
    {
        turn_.setString("Kolej gracza niebieskiego");
        turn_.setFillColor(sf::Color(0, 100, 255));
    }
    turn_.setPosition(sf::Vector2f((WindowWidth - turn_.getLocalBounds().width) / 2, 570));
    turnTimeLeft_.setString("Pozostaly czas: " + to_string((int)timeLeft));
    turnTimeLeft_.setPosition(sf::Vector2f((WindowWidth - turnTimeLeft_.getLocalBounds().width) / 2, 550));
    window.draw(turn_);
    window.draw(turnTimeLeft_);
}

/**
 * Wyświetla napis, który gracz wygrał grę
 * Dodatkowo po 2 sekundach wyświetla napis "Kliknij enter aby wrocic do menu"
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 * @param window - okno gry
 */
void Interface::drawGameEnd(const float elapsed, sf::RenderTarget &window)
{
    if((backToMenuTime_ += elapsed) >= 2.0)
    {
        window.draw(backToMenu_);
    }
    if(winnerID_ == Winner::Red)
    {
        gameEndText_.setOutlineColor(sf::Color::Red);
        gameEndText_.setString("Czerwony wygrywa!");
    }
    else if(winnerID_ == Winner::Blue)
    {
        gameEndText_.setOutlineColor(sf::Color(0, 100, 255));
        gameEndText_.setString("Niebieski wygrywa!");
    }
    else
    {
        gameEndText_.setOutlineColor(sf::Color::Black);
        gameEndText_.setString("Remis!");
        gameEndText_.setPosition(325, 100);
    }
    gameEndText_.setPosition(sf::Vector2f((WindowWidth - gameEndText_.getLocalBounds().width)/2, 100));
    window.draw(gameEndText_);
}

/**
 * Sprawdza, który z graczy wygrał grę
 *
 * @param health - wektor poziomów życia graczy
 *           [0] - poziom życia pierwszego gracza
 *           [1] - poziom życia drugiego gracza
 * @param tankPosition1 - pozycja pierwszego gracza
 * @param tankPosition2 - pozycja drugiego gracza
 *
 * @return wektor pozycji dwóch graczy dopasowana do animacji końcowych
 *         [0] - współrzędne wygranej pozycji
 *         [1] - współrzędne przegranej pozycji
 */
vector<sf::Vector2f> Interface::checkWinner(const int health[2], const sf::Vector2f &tankPosition1, const sf::Vector2f &tankPosition2)
{
    vector<sf::Vector2f> position;
    if(health[0] > 0)
    {
        winnerID_ = Winner::Red;
    }
    else
    {
        winnerID_ = Winner::Blue;
    }
    position.emplace_back((health[0] > 0 ? tankPosition1 : tankPosition2) - sf::Vector2f(50.0, 120.0));
    position.emplace_back((health[0] > 0 ? tankPosition2 : tankPosition1) - sf::Vector2f(50.0, 90.0));
    return position;
}

/**
 * Ustawia styl dla obiektu klast sf::Text
 *
 * @param size - rozmiar czcionki
 * @param thickness - grubość obramowania tekstu
 * @param position - wektor z pozycją tekstu
 * @param contents - treść napisu
 * @param fillColor - kolor tekstu
 * @param borderColor - kolor obramowania
 *
 * @return zwraca sformatowany obiekt klast sf::Text
 */
sf::Text Interface::setTextStyle(const int size, const int thickness, const string &contents, const sf::Vector2f position, const sf::Color fillColor, const sf::Color borderColor)
{
    sf::Text textToSet;
    textToSet.setFont(font_);
    textToSet.setCharacterSize(size);
    textToSet.setOutlineThickness(thickness);
    textToSet.setFillColor(fillColor);
    textToSet.setOutlineColor(borderColor);
    textToSet.setPosition(position);
    textToSet.setString(contents);
    return textToSet;
}

/**
 * Ustawia styl dla obiektu klasy sf::RectangleShape
 *
 * @param size - wektor z rozmiarem prostokąta
 * @param thickness - grubość obramowania
 * @param position - wektor z pozycją obiektu
 * @param fillColor - kolor wypełnienia prostokąta
 * @param borderColor - kolor obramowania
 *
 * @return zwraca sformatowany obiekt klasy sf::Text
 */
sf::RectangleShape Interface::setRectStyle(const sf::Vector2f size, const int thickness, const sf::Vector2f position, const sf::Color fillColor, const sf::Color borderColor)
{
    sf::RectangleShape rectToSet;
    rectToSet.setSize(size);
    rectToSet.setOutlineThickness(thickness);
    rectToSet.setPosition(position);
    rectToSet.setFillColor(fillColor);
    rectToSet.setOutlineColor(borderColor);
    return rectToSet;
}
