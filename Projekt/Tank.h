#pragma once

#include "Globals.h"
#include "Bullet.h"
#include "Land.h"
#include "Interface.h"

class Tank
{
public:
    Tank(const int playerID, const bool active, const string &texture, Land &land_);
    void Reset();
    void shoot();
    void moveTank(const float elapsed);
    void moveCannon(sf::RenderWindow &window);
    void moveShootPower(const int direction);
    void passEvent(sf::Event &event, sf::RenderWindow &window);
    void update(const float elapsed, sf::RenderWindow &window);
    void draw(const float elapsed, sf::RenderTarget &window);
    void step(const float elapsed);

    int getStatus();
    void switchStatus(sf::RenderWindow &window);

    Tank *enemy;

    inline int returnHp() {return health_;};
    inline sf::Vector2f returnPosition() {return TankSprite.getPosition();};
    inline Interface returnTankInterface() { return tankInterface_; };

private:
    Land *land;
    Interface tankInterface_;
    unique_ptr<Bullet> bullet_;

    bool freefall_;
    bool crosshairActive_;

    int status_;
    int playerID_;
    int moveDirection_;
    int shootPower_;
    int health_;

    float speed_;
    float maxAngle_;
    float timeLeft_;
    float velocityFreefall_;

    sf::Sprite TankSprite;
    sf::Sprite CannonSprite;
    sf::Sprite CrosshairSprite;
    sf::Texture TankTexture;
    sf::Texture CannonTexture;
    sf::Texture CrosshairTexture;

    bool canCannonMove();
    bool canTankMove(const sf::Vector2f &velocity);
    bool getCollision(const sf::Vector2f &velocity);

    float getLandAngle(const sf::Vector2f &velocity = sf::Vector2f(0.0, 0.0));

    void moveTankPosition(const sf::Vector2f &velocity);
    void setTankPosition(const sf::Vector2f &position);
    void shootReset();

    sf::RectangleShape getTankShape(const sf::Sprite &Tank);
};
