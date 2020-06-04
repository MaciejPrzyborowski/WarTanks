#include "Tank.h"

Tank::Tank(const int playerID, const bool active, const string &texture, Land &land_) :
    shootActive_(0),
    land(&land_),
    active_(active),
    freefall_(false),
    crosshairActive_(false),
    playerID_(playerID),
    moveDirection_(0),
    shootPower_(50),
    speed_(50.0),
    maxAngle_(75),
    velocityFreefall({0.0, 0.0})
{
    TankTexture.loadFromFile(texture);
    CannonTexture.loadFromFile(BarrelTextureSrc);
    CrosshairTexture.loadFromFile(CrosshairTextureSrc);
    TankSprite.setTexture(TankTexture);
    CannonSprite.setTexture(CannonTexture);
    CrosshairSprite.setTexture(CrosshairTexture);

    TankSprite.setOrigin(TankSprite.getLocalBounds().width / 2, TankSprite.getLocalBounds().height);
    CannonSprite.setOrigin(0, CannonSprite.getLocalBounds().height / 2);

    shootPowerBox.setSize(sf::Vector2f(100, 20));
    shootPowerBox.setPosition(350, 30);
    shootPowerBox.setOutlineThickness(3);
    shootPowerBox.setOutlineColor(sf::Color::White);
    shootPowerBox.setFillColor(sf::Color(0, 0, 0, 0));

    shootPowerFill.setSize(sf::Vector2f(50,20));
    shootPowerFill.setPosition(350,30);
    shootPowerFill.setFillColor(sf::Color(255,70,0));
}

void Tank::Reset()
{
    sf::Vector2f StartPosition(0, 0);
    StartPosition.x = rand() % 150;
    if(playerID_ == 1)
    {
        StartPosition.x += 50;
    }
    else
    {
        StartPosition.x += 400;
    }
    StartPosition.y = land->getLandHeight(StartPosition.x);
    setTankPosition(StartPosition);
    CannonSprite.setRotation(-90);
}

void Tank::Fire()
{
    if(!shootActive_ && !crosshairActive_)
    {
        float BulletVelocity = (float)shootPower_ * 5.0;
        float CannonRotation = DegreeToRadian(CannonSprite.getRotation());
        sf::Vector2f BulletRotation(cos(CannonRotation), sin(CannonRotation));
        bullet_ = make_unique<Bullet>(sf::Vector2f(CannonSprite.getPosition().x + CannonSprite.getLocalBounds().width * BulletRotation.x,
                                                   CannonSprite.getPosition().y + CannonSprite.getLocalBounds().width * BulletRotation.y), *land);
        bullet_->setVelocity(sf::Vector2f(BulletVelocity * BulletRotation.x, BulletVelocity * BulletRotation.y));
        shootActive_ = 1;
    }
}

/**
 * Zmienia siłę wystrzału pocisku
 */
void Tank::changeShootPower(const int direction)
{
    if(!((shootPower_ == 0 && direction < 0) || (shootPower_ == 100 && direction > 0)))
    {
        shootPower_ += direction;
        shootPowerFill.setSize(sf::Vector2f(shootPower_, 20));
    }
}

/**
 * Obsługuje przemieszczenie czołgu
 */
void Tank::moveTank(const float elapsed)
{
    if(isTankMoving())
    {
        sf::Vector2f velocity(0.0, 0.0);
        velocity.x = (speed_ * cos(DegreeToRadian(TankSprite.getRotation()))) * moveDirection_ * elapsed;
        velocity.y = land->getLandHeight(TankSprite.getPosition().x + velocity.x) - TankSprite.getPosition().y;
        if(canTankMove(velocity))
        {
            moveTankPosition(velocity);
        }
    }
}

/**
 * Obsługuje przemieszczenie lufy
 */
void Tank::moveCannon(sf::RenderWindow &window)
{
    if(isCannonMoving())
    {
        sf::Vector2i rotatePosition;
        sf::Vector2f cannonPosition = CannonSprite.getPosition();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        rotatePosition.x = mousePosition.x - cannonPosition.x;
        rotatePosition.y = mousePosition.y - cannonPosition.y;

        float angle = atan2f(rotatePosition.y, rotatePosition.x);
        CrosshairSprite.setPosition(cannonPosition);
        CrosshairSprite.move(cos(angle) * 100, sin(angle) * 100);
        CannonSprite.setRotation(RadianToDegree(angle));
    }
}

/**
 * Przesuwa pozycję czołgu oraz jego lufy
 */
void Tank::moveTankPosition(const sf::Vector2f &velocity)
{
    TankSprite.move(velocity);
    CannonSprite.move(velocity);
    setTankRotation(sf::Vector2f(TankSprite.getPosition().x, TankSprite.getPosition().y));
}

/**
 * Ustawia pozycję czołgu oraz jego lufy
 */
void Tank::setTankPosition(const sf::Vector2f &position)
{
    TankSprite.setPosition(position);
    CannonSprite.setPosition(position - sf::Vector2f(0, TankSprite.getLocalBounds().height/2));
    setTankRotation(sf::Vector2f(position));
}

/**
 * Ustawia kąt nachylenia czołgu
 */
void Tank::setTankRotation(const sf::Vector2f &position)
{
    float landAngle = land->getAngleDegree(position.x, position.y);
    TankSprite.setRotation(landAngle);
}

/**
 * Sprawdza czy czołg może przemieścić się o wektor [x, y]
 */
bool Tank::canTankMove(const sf::Vector2f &velocity)
{
    if(getStatus() && (velocity.y >= 0 || fabs(TankSprite.getRotation()) <= maxAngle_ || fabs(TankSprite.getRotation()) >= 360.0 - maxAngle_))
    {
        return true;
    }
    return false;
}

/**
 * Sprawdza czy czołg może wykonać jakąś czynność
 */
bool Tank::getStatus()
{
    return active_;
}

/**
 * Sprawdza czy czołg może wykonać jakąś czynność
 */
bool Tank::getCrosshairStatus()
{
    return crosshairActive_;
}

/**
 * Sprawdza czy czołg się przemieszcza
 */
bool Tank::isTankMoving()
{
    if(active_ && !crosshairActive_ && !shootActive_)
    {
        if(moveDirection_)
        {
            return true;
        }
    }
    else if(moveDirection_)
    {
        moveDirection_ = 0;
    }
    return false;
}

/**
 * Sprawdza czy lufa się przemieszcza
 */
bool Tank::isCannonMoving()
{
    if(getStatus() && crosshairActive_)
    {
        return true;
    }
    return false;
}

/**
 * Obsługa zdarzeń wykonanych przez gracza
 */
void Tank::passEvent(sf::Event &event, sf::RenderWindow &window)
{
    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Q)
        {
            active_ = !active_;
            crosshairActive_ = false;
        }
        if(event.key.code == sf::Keyboard::Left)
        {
            if(moveDirection_ == -1)
            {
                moveDirection_ = 0;
            }
        }
        if(event.key.code == sf::Keyboard::Right)
        {
            if(moveDirection_ == 1)
            {
                moveDirection_ = 0;
            }
        }
    }
    if(active_)
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Space)
            {
                Fire();
            }
            if(event.key.code == sf::Keyboard::Up)
            {
                changeShootPower(1);
            }
            if(event.key.code == sf::Keyboard::Down)
            {
                changeShootPower(-1);
            }
            if(event.key.code == sf::Keyboard::Left)
            {
                moveDirection_ = -1;
            }
            if(event.key.code == sf::Keyboard::Right)
            {
                moveDirection_ = 1;
            }
        }
        if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            crosshairActive_ = !crosshairActive_;
            window.setMouseCursorVisible(!crosshairActive_);
        }
    }
}

/**
 * Aktualizuje dane gracza
 */
void Tank::update(const float elapsed, sf::RenderWindow &window)
{
    step(elapsed);
    if(active_)
    {
        moveTank(elapsed);
        moveCannon(window);
    }
}

/**
 * Wyświetla czołg z jego lufą
 */
void Tank::draw(const float elapsed, sf::RenderTarget &window)
{
    window.draw(CannonSprite);
    window.draw(TankSprite);
    if(active_)
    {
        window.draw(shootPowerBox);
        window.draw(shootPowerFill);
        if(shootActive_ == 1)
        {
            if(bullet_->isActive())
            {
                bullet_->draw(window);
                bullet_->move(elapsed);
            }
            else
            {
                bullet_.reset();
                shootActive_ = 2;
            }
        }
        if(isCannonMoving())
        {
            window.draw(CrosshairSprite);
        }
    }
}

/**
 * Obsługuje grawitacje
 */
void Tank::step(const float elapsed)
{
    int h = land->getLandHeight(TankSprite.getPosition().x);
    if(TankSprite.getPosition().y < h)
    {
        freefall_ = true;
        velocityFreefall.y += Gravity * elapsed;
        sf::Vector2f velocity;
        velocity.y = velocityFreefall.y * elapsed;
        if(TankSprite.getPosition().y + velocity.y >= h)
        {
            velocity.y = h - TankSprite.getPosition().y + 1;
            setTankRotation(sf::Vector2f(TankSprite.getPosition().x, TankSprite.getPosition().y + velocity.y));
            velocityFreefall.y = 0.0;
            freefall_ = false;
        }
        TankSprite.move(velocity);
        CannonSprite.move(velocity);
    }
}

void Tank::switchStatus()
{
    active_ = !active_;
    setTankRotation(sf::Vector2f(TankSprite.getPosition().x, TankSprite.getPosition().y));
    shootActive_ = 0;
}
