#include "Interface.h"

Interface::Interface()
{
    font.loadFromFile(GameFont);
    gameTime_.setFont(font);
    gameTime_.setCharacterSize(20);
    gameTime_.setOutlineThickness(2);
    gameTime_.setOutlineColor(sf::Color::Black);
    gameTime_.setFillColor(sf::Color::White);
    gameTime_.setPosition(340, 5);

    gameEndText_.setFont(font);
    gameEndText_.setCharacterSize(50);
    gameEndText_.setOutlineThickness(3);
    gameEndText_.setFillColor(sf::Color::White);
    gameEndText_.setPosition(190, 100);

    backToMenu_.setFont(font);
    backToMenu_.setCharacterSize(20);
    backToMenu_.setOutlineThickness(3);
    backToMenu_.setOutlineColor(sf::Color::Black);
    backToMenu_.setFillColor(sf::Color::White);
    backToMenu_.setString("Kliknij enter aby wrocic do menu");
    backToMenu_.setPosition(255, 570);
}

Interface::Interface(int id_)
{
    shootPowerBorder.setSize(sf::Vector2f(100, 20));
    shootPowerBorder.setPosition(350, 40);
    shootPowerBorder.setOutlineThickness(3);
    shootPowerBorder.setOutlineColor(sf::Color(50, 50, 50));
    shootPowerBorder.setFillColor(sf::Color(0, 0, 0, 0));
    shootPowerFill.setPosition(350,40);

    font.loadFromFile(GameFont);
    hpText_.setFont(font);
    hpText_.setString("HP");
    hpText_.setOutlineThickness(1);
    hpText_.setOutlineColor(sf::Color::Black);
    hpText_.setCharacterSize(22);

    healthPointBorder.setSize(sf::Vector2f(100, 20));
    healthPointBorder.setOutlineThickness(3);

    healthPointBorder.setFillColor(sf::Color(0, 0, 0, 0));
    if(id_ == 1)
    {
        hpText_.setFillColor(sf::Color::Red);
        healthPointBorder.setOutlineColor(sf::Color(50, 50, 50));
        hpText_.setPosition(60, 26);
        healthPointBorder.setPosition(20, 30);
        healthPointFill.setPosition(20, 30);
    }
    else if(id_ == 2)
    {
        hpText_.setFillColor(sf::Color::Blue);
        healthPointBorder.setOutlineColor(sf::Color(50, 50, 50));
        hpText_.setPosition(720, 26);
        healthPointBorder.setPosition(680, 30);
        healthPointFill.setPosition(680, 30);
    }

    turn_.setFont(font);
    turn_.setCharacterSize(20);
    turn_.setOutlineThickness(3);
    turn_.setOutlineColor(sf::Color::Black);
    turn_.setPosition(290, 570);

    angle_.setFont(font);
    angle_.setCharacterSize(18);
    angle_.setOutlineThickness(2);
    angle_.setOutlineColor(sf::Color::Black);
    angle_.setFillColor(sf::Color::White);
    angle_.setPosition(350, 65);
}

void Interface::drawPower(sf::RenderTarget &Window, int shootPower_)
{
    shootPowerFill.setSize(sf::Vector2f(shootPower_, 20));
    shootPowerFill.setFillColor(sf::Color(200 - shootPower_, 2 * shootPower_, 0));

    Window.draw(shootPowerFill);
    Window.draw(shootPowerBorder);
}

void Interface::drawHp(sf::RenderTarget &Window, int health_)
{
    if(health_ < 0) health_ = 0;

    healthPointFill.setSize(sf::Vector2f(health_, 20));
    healthPointFill.setFillColor(sf::Color(200 - health_, 2* health_, 0));

    Window.draw(healthPointFill);
    Window.draw(healthPointBorder);
    Window.draw(hpText_);
}

sf::Text Interface::showAngle(float angle)
{
    angle_.setString("Kat lufy: " + to_string((int)(angle)));
    return angle_;
}

sf::Text Interface::turnRed()
{
    turn_.setString("Kolej gracza czerwonego");
    turn_.setFillColor(sf::Color::Red);
    return turn_;
}

sf::Text Interface::turnBlue()
{
    turn_.setString("Kolej gracza niebieskiego");
    turn_.setFillColor(sf::Color::Blue);
    return turn_;
}

sf::Text Interface::gameTime(float time_)
{
    totalTime_ += time_;
    gameTime_.setString("Czas: " + std::to_string((int)totalTime_) + " sekund");
    return gameTime_;
}

sf::Text Interface::gameEnd(int hp1, int hp2)
{
    if(hp1 <= 0 && hp2 > 0)
    {
        gameEndText_.setOutlineColor(sf::Color::Blue);
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

void Interface::backToMenuText(float elapsed, sf::RenderTarget &Window)
{
    backToMenuTime += elapsed;
    if(backToMenuTime >= 3.0)
    {
        Window.draw(backToMenu_);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            cout << "JAK KURWA ZROBIE TO SIE COFNIE" << endl;
        }
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

sf::Vector2f Interface::Winner(int hp1, int hp2, sf::Vector2f TankPos1, sf::Vector2f TankPos2)
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

sf::Vector2f Interface::Loser(int hp1, int hp2, sf::Vector2f TankPos1, sf::Vector2f TankPos2)
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



