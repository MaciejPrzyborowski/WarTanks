#include "Interface.h"

Interface::Interface()
{
    font_.loadFromFile(GameFontSrc);

    gameTime_.setFont(font_);
    gameTime_.setCharacterSize(20);
    gameTime_.setOutlineThickness(2);
    gameTime_.setOutlineColor(sf::Color::Black);
    gameTime_.setFillColor(sf::Color::White);
    gameTime_.setPosition(340, 5);

    gameEndText_.setFont(font_);
    gameEndText_.setCharacterSize(50);
    gameEndText_.setOutlineThickness(3);
    gameEndText_.setFillColor(sf::Color::White);
    gameEndText_.setPosition(190, 100);

    backToMenu_.setFont(font_);
    backToMenu_.setCharacterSize(20);
    backToMenu_.setOutlineThickness(3);
    backToMenu_.setOutlineColor(sf::Color::Black);
    backToMenu_.setFillColor(sf::Color::White);
    backToMenu_.setString("Kliknij enter aby wrocic do menu");
    backToMenu_.setPosition(255, 570);

    turn_.setFont(font_);
    turn_.setCharacterSize(20);
    turn_.setOutlineThickness(3);
    turn_.setOutlineColor(sf::Color::Black);
    turn_.setPosition(260, 570);

    turnTimeLeft_.setFont(font_);
    turnTimeLeft_.setCharacterSize(18);
    turnTimeLeft_.setOutlineThickness(2);
    turnTimeLeft_.setOutlineColor(sf::Color::Black);
    turnTimeLeft_.setPosition(290, 550);
    turnTimeLeft_.setFillColor(sf::Color::White);
}

Interface::Interface(int id)
{
    font_.loadFromFile(GameFontSrc);

    shootPowerBorder_.setSize(sf::Vector2f(100, 20));
    shootPowerBorder_.setPosition(350, 40);
    shootPowerBorder_.setOutlineThickness(3);
    shootPowerBorder_.setOutlineColor(sf::Color(50, 50, 50));
    shootPowerBorder_.setFillColor(sf::Color(0, 0, 0, 0));
    shootPowerFill_.setPosition(350,40);

    hpText_.setFont(font_);
    hpText_.setString("HP");
    hpText_.setOutlineThickness(1);
    hpText_.setOutlineColor(sf::Color::Black);
    hpText_.setCharacterSize(22);

    healthPointBorder_.setSize(sf::Vector2f(100, 20));
    healthPointBorder_.setOutlineThickness(3);
    healthPointBorder_.setOutlineColor(sf::Color(50, 50, 50));
    healthPointBorder_.setFillColor(sf::Color(0, 0, 0, 0));

    if(id == 1)
    {
        hpText_.setFillColor(sf::Color::Red);
        hpText_.setPosition(60, 26);
        healthPointBorder_.setPosition(20, 30);
        healthPointFill_.setPosition(20, 30);
    }
    else if(id == 2)
    {
        hpText_.setFillColor(sf::Color(0, 100, 255));
        hpText_.setPosition(720, 26);
        healthPointBorder_.setPosition(680, 30);
        healthPointFill_.setPosition(680, 30);
    }

    angle_.setFont(font_);
    angle_.setCharacterSize(18);
    angle_.setOutlineThickness(2);
    angle_.setOutlineColor(sf::Color::Black);
    angle_.setFillColor(sf::Color::White);
    angle_.setPosition(350, 65);
}

void Interface::drawPower(sf::RenderTarget &Window, int shootPower)
{
    shootPowerFill_.setSize(sf::Vector2f(shootPower, 20));
    shootPowerFill_.setFillColor(sf::Color(200 - shootPower, 2 * shootPower, 0));

    Window.draw(shootPowerFill_);
    Window.draw(shootPowerBorder_);
}

void Interface::drawHp(sf::RenderTarget &Window, int health)
{
    if(health < 0) health = 0;

    healthPointFill_.setSize(sf::Vector2f(health, 20));
    healthPointFill_.setFillColor(sf::Color(200 - health, 2* health, 0));

    Window.draw(healthPointFill_);
    Window.draw(healthPointBorder_);
    Window.draw(hpText_);
}

sf::Text Interface::showAngle(float angle)
{
    angle_.setString("Kat lufy: " + to_string((int)(angle)));
    return angle_;
}

void Interface::turnRed(sf::RenderTarget &Window, float timeLeft)
{
    turn_.setString("Kolej gracza czerwonego");
    turn_.setFillColor(sf::Color::Red);
    turnTimeLeft_.setString("Pozostaly czas: " + std::to_string((int)timeLeft));
    Window.draw(turn_);
    Window.draw(turnTimeLeft_);
}

void Interface::turnBlue(sf::RenderTarget &Window, float timeLeft)
{
    turn_.setString("Kolej gracza niebieskiego");
    turn_.setFillColor(sf::Color(0, 100, 255));
    turnTimeLeft_.setString("Pozostaly czas: " + std::to_string((int)timeLeft));
    Window.draw(turn_);
    Window.draw(turnTimeLeft_);
}

sf::Text Interface::gameTime(float time)
{
    totalTime_ += time;
    gameTime_.setString("Czas: " + std::to_string((int)totalTime_) + " sekund");
    return gameTime_;
}

sf::Text Interface::gameEnd(int hp1, int hp2)
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
        gameEndText_.setOutlineColor(sf::Color::Black);
        gameEndText_.setString("Remis!");
        showEndAnimations_ = false;
    }
    return gameEndText_;
}

void Interface::backToMenuText(sf::RenderTarget &Window, float elapsed)
{
    backToMenuTime += elapsed;
    if(backToMenuTime >= 2.0)
    {
        Window.draw(backToMenu_);
    }
}

bool Interface::checkPlayersHp(int hp1, int hp2)
{
    if(hp1 <= 0)
    {
        isGameEnd_ = true;
    }
    else if(hp2 <= 0)
    {
        isGameEnd_ = true;
    }
    return isGameEnd_;
}

sf::Vector2f Interface::winner(int hp1, int hp2, sf::Vector2f TankPos1, sf::Vector2f TankPos2)
{
    if(showEndAnimations_)
    {
        if(hp1 <= 0)
        {
            return TankPos2;
        }
        else if(hp2 <= 0)
        {
            return TankPos1;
        }
    }
    return sf::Vector2f(0.0, 0.0);
}

sf::Vector2f Interface::loser(int hp1, int hp2, sf::Vector2f TankPos1, sf::Vector2f TankPos2)
{
    if(showEndAnimations_)
    {
        if(hp1 <= 0)
        {
            return TankPos1;
        }
        else if(hp2 <= 0)
        {
            return TankPos2;
        }
    }
    return sf::Vector2f(0.0, 0.0);
}



