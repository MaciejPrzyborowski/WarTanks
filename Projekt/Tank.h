#pragma once

#include "Globals.h"
#include "Bullet.h"
#include "Land.h"

class Tank
{
public:
    Tank(const int playerID, const bool active, const string &texture, Land &land_);
    void Reset();
    void Fire();
    void moveTank(const float elapsed);
    void moveCannon(sf::RenderWindow &window);
    void changeShootPower(const int direction);
    void passEvent(sf::Event &event, sf::RenderWindow &window);
    void update(const float elapsed, sf::RenderWindow &window);
    void draw(const float elapsed, sf::RenderTarget &window);

    void switchStatus();
    bool getStatus();
    bool getCrosshairStatus();
    bool isTankMoving();
    bool isCannonMoving();
    int shootActive_ = 0;

private:
    Land *land;
    unique_ptr<Bullet> bullet_;

    bool active_;
    bool crosshairActive_ = false;

    int playerID_;
    int moveDirection_ = 0;
    int shootPower_ = 50;
    float speed_ = 50.0;
    float maxAngle_ = 72.5;

    sf::Sprite TankSprite;
    sf::Sprite CannonSprite;
    sf::Sprite CrosshairSprite;
    sf::Texture TankTexture;
    sf::Texture CannonTexture;
    sf::Texture CrosshairTexture;
    sf::RectangleShape shootPowerBox;
    sf::RectangleShape shootPowerFill;

    bool canTankMove(const sf::Vector2f &velocity);

    void moveTankPosition(const sf::Vector2f &velocity);
    void setTankPosition(const sf::Vector2f &position);
    void setTankRotation(const sf::Vector2f &position);
};
