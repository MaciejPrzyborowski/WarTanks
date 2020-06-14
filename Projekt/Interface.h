#pragma once

#include "Globals.h"

class Interface
{
public:
    Interface();
    Interface(const int id);

    void drawPower(sf::RenderTarget &Window, const int shootPower);
    void drawHp(sf::RenderTarget &Window, int health);
    void backToMenuText(sf::RenderTarget &Window, const float elapsed);
    void turnRed(sf::RenderTarget &Window, const float timeLeft);
    void turnBlue(sf::RenderTarget &Window, const float timeLeft);
    void reset();

    void playGameMusic(bool isMusicOn);

    sf::Text setTextStyle(const int size, const int thickness, const sf::Vector2f position, const std::string &contents, const sf::Color fillColor = sf::Color::White, const sf::Color borderColor = sf::Color::Black);
    sf::RectangleShape setRectStyle(const sf::Vector2f size, const int thickness, const sf::Vector2f position, const sf::Color fillColor = sf::Color(0, 0, 0, 0), const sf::Color borderColor = sf::Color(50, 50, 50));

    sf::Text showAngle(const float angle);
    sf::Text gameTime(const float &time);
    sf::Text gameEnd(const int &hp1, const int &hp2);
    sf::Text showFps(float elapsed);

    inline sf::Vector2f winner(const int &hp1, const sf::Vector2f &TankPos1, const sf::Vector2f &TankPos2) {return (hp1 <= 0) ? TankPos2 : TankPos1;};
    inline sf::Vector2f loser(const int &hp1, const sf::Vector2f &TankPos1, const sf::Vector2f &TankPos2) {return (hp1 <= 0) ? TankPos1 : TankPos2;};

    inline bool checkPlayersHp(const int &hp1, const int &hp2) {return (hp1 <= 0 || hp2 <=0) ? true : false;};
    inline bool showAnimations_() {return showEndAnimations_;};



private:
    float totalTime_;
    float backToMenuTime;
    bool showEndAnimations_;

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
    sf::Text fps_;

    sf::Sound gameMusic_;
    sf::SoundBuffer gameBuffer_;
};
