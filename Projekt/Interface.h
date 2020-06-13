#pragma once

#include "Globals.h"

class Interface
{
public:
    Interface();
    Interface(int id);

    void drawPower(sf::RenderTarget &Window, int shootPower);
    void drawHp(sf::RenderTarget &Window, int health);
    void backToMenuText(sf::RenderTarget &Window, float elapsed);

    void turnRed(sf::RenderTarget &Window, float timeLeft);
    void turnBlue(sf::RenderTarget &Window, float timeLeft);
    sf::Text showAngle(float angle);
    sf::Text gameTime(float time);
    sf::Text gameEnd(int hp1, int hp2);

    sf::Vector2f winner(int hp1, int hp2, sf::Vector2f TankPos1, sf::Vector2f TankPos2);
    sf::Vector2f loser(int hp1, int hp2, sf::Vector2f TankPos1, sf::Vector2f TankPos2);

    bool checkPlayersHp(int hp1, int hp2);
    inline bool showAnimations_() {return showEndAnimations_;};

private:
    sf::RectangleShape shootPowerBorder_;
    sf::RectangleShape shootPowerFill_;
    sf::RectangleShape healthPointBorder_;
    sf::RectangleShape healthPointFill_;

    sf::Font font_;

    sf::Text hpText_;
    sf::Text turn_;
    sf::Text angle_;
    sf::Text gameTime_;
    sf::Text gameEndText_;
    sf::Text backToMenu_;
    sf::Text turnTimeLeft_;

    bool isGameEnd_ = false;
    bool showEndAnimations_ = true;

    float totalTime_ = 0.0;
    float backToMenuTime = 0.0;


};
