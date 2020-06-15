#include "Interface.h"

Interface::Interface(): totalTime_(0.0), backToMenuTime(0.0), showEndAnimations_(true)
{
    font_.loadFromFile(GameFontSrc);
    gameTime_ = setTextStyle(20, 2, sf::Vector2f(340, 5), "");
    gameEndText_ = setTextStyle(50, 3, sf::Vector2f(190,100), "Remis!");
    backToMenu_ = setTextStyle(20, 3, sf::Vector2f(255, 570), "Kliknij enter aby wrocic do menu");
    fps_ = setTextStyle(15, 1, sf::Vector2f(2, 2), "");
}

Interface::Interface(const int id): totalTime_(0.0), backToMenuTime(0.0), showEndAnimations_(true)
{
    font_.loadFromFile(GameFontSrc);

    shootPowerBorder_ = setRectStyle(sf::Vector2f(100, 20), 3, sf::Vector2f(350, 40));
    shootPowerFill_.setPosition(350,40);

    turn_ = setTextStyle(20, 3, sf::Vector2f(260, 570), "");
    turnTimeLeft_ = setTextStyle(18, 2, sf::Vector2f(290, 550), "");
    hpText_ = setTextStyle(22, 1, sf::Vector2f(0, 0), "HP");
    angle_ = setTextStyle(18, 2, sf::Vector2f(350, 65), "");

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
 * Rysuje pasek siły strzału
 *
 * @param Window - okno gry
 * @param shootPower - siła strzału danego gracza
*/
void Interface::drawPower(sf::RenderTarget &Window, int shootPower)
{
    shootPowerFill_.setSize(sf::Vector2f(shootPower, 20));
    shootPowerFill_.setFillColor(sf::Color(200 - shootPower, 2 * shootPower, 0));

    Window.draw(shootPowerFill_);
    Window.draw(shootPowerBorder_);
}

/**
 * Rysune pasek stanu życia
 *
 * @param Window - okno gry
 * @param health - poziom życia gracza
 */
void Interface::drawHp(sf::RenderTarget &Window, int health)
{
    if(health < 0) health = 0;

    healthPointFill_.setSize(sf::Vector2f(health, 20));
    healthPointFill_.setFillColor(sf::Color(200 - health, 2* health, 0));

    Window.draw(healthPointFill_);
    Window.draw(healthPointBorder_);
    Window.draw(hpText_);
}

/**
 * Ustawia napis z kątem nachylenia lufy
 *
 * @param angle - kąt nachylenia
 * @return zwraca obiekt klasy sf::Text odpowiadający za kąt nachylenia
 */
sf::Text Interface::drawAngle(const float angle)
{
    angle_.setString("Kat lufy: " + to_string((int)(angle)));
    return angle_;
}

/**
 * Ustawia napis z liczbą klatek w grze
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 * @return zwraca obiekt klasy sf::Text odpowiadający za liczbę klatek w grze
 */
sf::Text Interface::showFps(float elapsed)
{
    fps_.setString(std::to_string((int)(1/elapsed)) + " FPS");
    return fps_;
}

/**
 * Ustawia początkowe wartości zmiennych
 */
void Interface::reset()
{
    totalTime_ = 0.0;
    backToMenuTime = 0.0;
    showEndAnimations_ = true;
}

/**
 * Ustawia napis związany z długością czasu gry
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 * @return zwraca obiekt klasy sf::Text odpowiadający za czas gry
 */
sf::Text Interface::gameTime(const float &elapsed)
{
    totalTime_ += elapsed;
    gameTime_.setString("Czas: " + std::to_string((int)totalTime_) + " sekund");
    return gameTime_;
}

/**
 * Ustawia napis końcowy gry gdy któryś z graczy straci wszystkie punkty życia
 * @param hp1 - punkty życia gracza 1
 * @param hp2 - punkty życia gracza 2
 * @return zwraca obiekt klasy sf::Text odpowiadający za napis na zakończenie gry
 */
sf::Text Interface::gameEnd(const int &hp1, const int &hp2)
{
    if(hp1 <= 0 && hp2 > 0)
    {
        gameEndText_.setOutlineColor(sf::Color(0, 100, 255));
        gameEndText_.setString("Niebieski wygrywa!");

    }
    else if(hp2 <= 0 && hp1 > 0)
    {
        gameEndText_.setOutlineColor(sf::Color::Red);
        gameEndText_.setString("Czerwony wygrywa!");
    }
    else if(hp1 <= 0 && hp2 <= 0)
    {
        gameEndText_.setPosition(325, 100);
        showEndAnimations_ = false;
    }
    return gameEndText_;
}

/**
 * Po zakończeniu gry wyświetla napis "Kliknij enter aby wrocic do menu"
 * @param Window - okno gry
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 */
void Interface::backToMenuText(sf::RenderTarget &Window, float elapsed)
{
    backToMenuTime += elapsed;
    if(backToMenuTime >= 2.0)
    {
        Window.draw(backToMenu_);
    }
}

/**
 * Sprawdza i wyświetla którego gracza jest kolej
 * @param Window - okno gry
 * @param timeLeft - pozostały czas do sterowania czołgiem dla danego gracza
 * @param id - identyfikator gracza
 */
void Interface::drawTurn(sf::RenderTarget &Window, const float timeLeft, const int id)
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
    turnTimeLeft_.setString("Pozostaly czas: " + std::to_string((int)timeLeft));
    Window.draw(turn_);
    Window.draw(turnTimeLeft_);
}

/**
 * Ustawia styl dla obiektu klast sf::Text
 * @param size - rozmiar czcionki
 * @param thickness - grubość obramowania tekstu
 * @param position - wektor z pozycją tekstu
 * @param contents - treść napisu
 * @param fillColor - kolor tekstu
 * @param borderColor - kolor obramowania
 * @return zwraca sformatowany obiekt klast sf::Text
 */
sf::Text Interface::setTextStyle(const int size, const int thickness, const sf::Vector2f position, const std::string &contents, sf::Color fillColor, sf::Color borderColor)
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
 * @param size - wektor z rozmiarem prostokąta
 * @param thickness - grubość obramowania
 * @param position - wektor z pozycją obiektu
 * @param fillColor - kolor wypełnienia prostokąta
 * @param borderColor - kolor obramowania
 * @return zwraca sformatowany obiekt klasy sf::Text
 */
sf::RectangleShape Interface::setRectStyle(const sf::Vector2f size, const int thickness, const sf::Vector2f position, sf::Color fillColor, sf::Color borderColor)
{
    sf::RectangleShape rectToSet;
    rectToSet.setSize(size);
    rectToSet.setOutlineThickness(thickness);
    rectToSet.setPosition(position);
    rectToSet.setFillColor(fillColor);
    rectToSet.setOutlineColor(borderColor);
    return rectToSet;
}
