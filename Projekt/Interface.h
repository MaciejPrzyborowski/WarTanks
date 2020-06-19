#pragma once

#include "Globals.h"

enum class Winner
{
    None,
    Red,
    Blue
};

class Interface
{
public:
    Interface();
    Interface(const int &id);

    void reset();
    void drawAngle(const float &angle, sf::RenderTarget &window);
    void drawFPS(const float &elapsed, sf::RenderTarget &window);
    void drawGameEnd(const float &elapsed, sf::RenderTarget &window);
    void drawGameTime(const float &elapsed, sf::RenderTarget &window);
    void drawHealth(const int &health, sf::RenderTarget &window);
    void drawShootPower(const int &shootPower, sf::RenderTarget &window);
    void drawTurn(const int &id, const float &timeLeft, sf::RenderTarget &window);

    vector<sf::Vector2f> checkWinner(const int *health, const sf::Vector2f &tankPosition1, const sf::Vector2f &tankPosition2);

    sf::Text setTextStyle(const int &size, const int &thickness, const string &contents = "",
                          const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Color &fillColor = sf::Color::White,
                          const sf::Color &borderColor = sf::Color::Black);
    sf::RectangleShape setRectStyle(const sf::Vector2f &size, const int &thickness, const sf::Vector2f &position,
                                    const sf::Color &fillColor = sf::Color(0, 0, 0, 0),
                                    const sf::Color &borderColor = sf::Color(50, 50, 50));

private:
    sf::Font font_;
    sf::Text angle_;
    sf::Text backToMenu_;
    sf::Text fps_;
    sf::Text gameEndText_;
    sf::Text gameTime_;
    sf::Text hpText_;
    sf::Text turn_;
    sf::Text turnTimeLeft_;
    Winner winnerID_;

    float totalTime_;
    float backToMenuTime_;

    sf::RectangleShape shootPowerBorder_;
    sf::RectangleShape shootPowerFill_;
    sf::RectangleShape healthPointBorder_;
    sf::RectangleShape healthPointFill_;
};
