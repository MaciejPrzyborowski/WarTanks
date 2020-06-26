#include "Interface.h"
#include "Application.h"

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

Interface::Interface(const int &playerID) :
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
    if(playerID == 1)
    {
        hpText_.setFillColor(sf::Color::Red);
        hpText_.setPosition(60, 26);
        healthPointBorder_ = setRectStyle(sf::Vector2f(100, 20), 3, sf::Vector2f(20, 30));
        healthPointFill_.setPosition(20, 30);
    }
    else if(playerID == 2)
    {
        hpText_.setFillColor(sf::Color(0, 100, 255));
        hpText_.setPosition(720, 26);
        healthPointBorder_ = setRectStyle(sf::Vector2f(100, 20), 3, sf::Vector2f(680, 30));
        healthPointFill_.setPosition(680, 30);
    }
}

void Interface::reset()
{
    backToMenuTime_ = 0.0;
    totalTime_ = 0.0;
}

void Interface::drawAngle(const float &angle, sf::RenderTarget &window)
{
    angle_.setPosition(sf::Vector2f((WindowWidth - angle_.getLocalBounds().width)/2, 65));
    angle_.setString("Kat lufy: " + to_string((int)(angle)));
    window.draw(angle_);
}

void Interface::drawFPS(const float &elapsed, sf::RenderTarget &window)
{
    fps_.setString(to_string((int)(1 / elapsed)) + " FPS");
    window.draw(fps_);
}

void Interface::drawGameEnd(const float &elapsed, sf::RenderTarget &window)
{
    if((backToMenuTime_ += elapsed) >= 2.0)
    {
        window.draw(backToMenu_);
    }
    if(Application::getGame().winnerID_ == WinnerType::Red)
    {
        gameEndText_.setOutlineColor(sf::Color::Red);
        gameEndText_.setString("Czerwony wygrywa!");
    }
    else if(Application::getGame().winnerID_ == WinnerType::Blue)
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

void Interface::drawGameTime(const float &elapsed, sf::RenderTarget &window)
{
    totalTime_ += elapsed;
    gameTime_.setString("Czas: " + to_string((int)totalTime_) + " sekund");
    gameTime_.setPosition(sf::Vector2f((WindowWidth - gameTime_.getLocalBounds().width) / 2, 5));
    window.draw(gameTime_);
}

void Interface::drawHealth(const int &health, sf::RenderTarget &window)
{
    healthPointFill_.setSize(sf::Vector2f(health, 20));
    healthPointFill_.setFillColor(sf::Color(200 - health, 2 * health, 0));

    window.draw(healthPointFill_);
    window.draw(healthPointBorder_);
    window.draw(hpText_);
}

void Interface::drawShootPower(const int &shootPower, sf::RenderTarget &window)
{
    shootPowerFill_.setSize(sf::Vector2f(shootPower, 20));
    shootPowerFill_.setFillColor(sf::Color(200 - shootPower, 2 * shootPower, 0));
    window.draw(shootPowerFill_);
    window.draw(shootPowerBorder_);
}

void Interface::drawTurn(const int &id, const float &timeLeft, sf::RenderTarget &window)
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

sf::Text Interface::setTextStyle(const int &size, const int &thickness, const string &contents, const sf::Vector2f &position, const sf::Color &fillColor, const sf::Color &borderColor)
{
    sf::Text formattedText;
    formattedText.setFont(font_);
    formattedText.setCharacterSize(size);
    formattedText.setOutlineThickness(thickness);
    formattedText.setFillColor(fillColor);
    formattedText.setOutlineColor(borderColor);
    formattedText.setPosition(position);
    formattedText.setString(contents);
    return formattedText;
}

sf::RectangleShape Interface::setRectStyle(const sf::Vector2f &size, const int &thickness, const sf::Vector2f &position, const sf::Color &fillColor, const sf::Color &borderColor)
{
    sf::RectangleShape formattedRect;
    formattedRect.setSize(size);
    formattedRect.setOutlineThickness(thickness);
    formattedRect.setPosition(position);
    formattedRect.setFillColor(fillColor);
    formattedRect.setOutlineColor(borderColor);
    return formattedRect;
}
