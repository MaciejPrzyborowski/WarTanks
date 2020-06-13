#pragma once

#include "Globals.h"

class Interface
{
public:
    Interface();
    Interface(int id_);
    void drawPower(sf::RenderTarget &Window, int shootPower_);
    void drawHp(sf::RenderTarget &Window, int health_);

    sf::Text turnRed();
    sf::Text turnBlue();
    sf::Text showAngle(float angle);
    sf::Text gameTime(float time_);
    sf::Text gameEnd(int hp1, int hp2);
    void backToMenuText(float elapsed, sf::RenderTarget &Window);

    sf::Vector2f Winner(int hp1, int hp2, sf::Vector2f TankPos1, sf::Vector2f TankPos2);
    sf::Vector2f Loser(int hp1, int hp2, sf::Vector2f TankPos1, sf::Vector2f TankPos2);

    bool checkPlayersHp(int hp1, int hp2);
    inline bool showAnimations_() {return showEndAnimations_;};

private:
    sf::RectangleShape shootPowerBorder;
    sf::RectangleShape shootPowerFill;

    sf::RectangleShape healthPointBorder;
    sf::RectangleShape healthPointFill;

    sf::Font font;
    sf::Text hpText_;
    sf::Text turn_;
    sf::Text angle_;

    bool isGameEnd_ = false;
    bool showEndAnimations_ = true;

    float totalTime_ = 0.0;
    float backToMenuTime = 0.0;

    sf::Text gameTime_;
    sf::Text gameEndText_;
    sf::Text backToMenu_;
};
