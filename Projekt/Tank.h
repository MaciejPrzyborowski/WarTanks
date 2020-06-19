#pragma once

#include "Globals.h"
#include "Bullet.h"
#include "Land.h"
#include "Interface.h"

enum class TankState
{
    InActive,
    Active,
    Switch
};

enum class TankMove
{
    None,
    Left,
    Right
};

class Tank
{
public:
    Tank(const int &playerID, const string &texture, Land &land_);
    void reset();
    void shoot();
    void moveTank(const float &elapsed);
    void moveCannon(sf::RenderWindow &window);
    void moveShootPower(const int &direction);
    void passEvent(const sf::Event &event, sf::RenderWindow &window);
    void update(const float &elapsed, sf::RenderWindow &window);
    void draw(sf::RenderTarget &window);
    void step(const float &elapsed);

    TankState getStatus();

    void switchStatus(sf::RenderWindow &window);

    Tank *enemy;
    inline int returnHp() {return health_;};
    inline sf::Vector2f returnPosition() {return tankSprite_.getPosition();};

private:
    Land *land;
    unique_ptr<Bullet> bullet_;
    unique_ptr<Interface> tankInterface_;
    TankState status_;
    TankMove moveDirection_;

    bool freefall_;
    bool crosshairActive_;

    int playerID_;
    int shootPower_;
    int health_;

    float speed_;
    float maxAngle_;
    float timeLeft_;
    float velocityFreefall_;

    sf::Sprite tankSprite_;
    sf::Sprite cannonSprite_;
    sf::Sprite crosshairSprite_;
    sf::Texture tankTexture_;
    sf::Texture cannonTexture_;
    sf::Texture crosshairTexture_;
    sf::SoundBuffer shootBuffer_;
    sf::Sound shootSound_;

    bool canCannonMove();
    bool canTankMove(const sf::Vector2f &velocity);
    bool getEnemyCollision(const sf::Vector2f &velocity);

    float getLandAngle(const sf::Vector2f &velocity = sf::Vector2f(0.0, 0.0));

    void moveTankPosition(const sf::Vector2f &velocity);
    void setTankPosition(const sf::Vector2f &position);
    void shootReset();

    sf::RectangleShape getTankShape(const sf::Sprite &Tank);
};
