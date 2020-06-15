#include "Tank.h"

Tank::Tank(const int playerID, const string &texture, Land &land_) :
    land(&land_),
    freefall_(false),
    crosshairActive_(false),
    status_(playerID == 1),
    playerID_(playerID),
    moveDirection_(0),
    shootPower_(50),
    health_(100),
    speed_(50.0),
    maxAngle_(75.0),
    timeLeft_(15.0),
    velocityFreefall_(0.0)
{
    tankInterface_ = make_unique<Interface>(playerID);
    tankTexture_.loadFromFile(texture);
    cannonTexture_.loadFromFile(BarrelTextureSrc);
    crosshairTexture_.loadFromFile(CrosshairTextureSrc);
    tankSprite_.setTexture(tankTexture_);
    cannonSprite_.setTexture(cannonTexture_);
    crosshairSprite_.setTexture(crosshairTexture_);

    shootBuffer_.loadFromFile(ShootSoundSrc);
    shootSound_.setBuffer(shootBuffer_);
    shootSound_.setVolume(10);

    tankSprite_.setOrigin(tankSprite_.getLocalBounds().width / 2, tankSprite_.getLocalBounds().height);
    cannonSprite_.setOrigin(0, cannonSprite_.getLocalBounds().height / 2);
}

/**
 * Resetuje parametry gracza do domyślnych
 */
void Tank::reset()
{
    freefall_ = false;
    crosshairActive_ = false;
    status_ = (playerID_ == 1);

    moveDirection_ = 0;
    shootPower_ = 50;

    health_ = 100;
    timeLeft_ = 15.0;
    velocityFreefall_ = 0.0;

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
    cannonSprite_.setRotation(-90);
}

/**
 * Tworzy pocisk w miejscu aktualnej pozycji celownika
 * Pocisk jest wystrzeliwany z mocą shootPower_ wymnożoną przez 5
 */
void Tank::shoot()
{
    if(!moveDirection_ && !crosshairActive_ && bullet_ == nullptr)
    {
        if(shootSound_.getStatus() != sf::Music::Playing)
        {
            shootSound_.play();
        }
        float BulletVelocity = (float)shootPower_ * 5.0;
        float CannonRotation = DegreeToRadian(cannonSprite_.getRotation());
        sf::Vector2f BulletRotation(cos(CannonRotation), sin(CannonRotation));
        bullet_ = make_unique<Bullet>(sf::Vector2f(cannonSprite_.getPosition().x + cannonSprite_.getLocalBounds().width * BulletRotation.x,
                                                   cannonSprite_.getPosition().y + cannonSprite_.getLocalBounds().width * BulletRotation.y),
                                      getTankShape(tankSprite_), getTankShape(enemy->tankSprite_), *land);
        bullet_->setVelocity(sf::Vector2f(BulletVelocity * BulletRotation.x, BulletVelocity * BulletRotation.y));
    }
}

/**
 * Obsługuje przemieszczenie czołgu
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 */
void Tank::moveTank(const float elapsed)
{
    if(moveDirection_)
    {
        sf::Vector2f velocity(0.0, 0.0);
        velocity.x = (speed_ * cos(DegreeToRadian(tankSprite_.getRotation()))) * moveDirection_ * elapsed;
        velocity.y = land->getLandHeight(tankSprite_.getPosition().x + velocity.x) - tankSprite_.getPosition().y;
        moveTankPosition(velocity);
    }
}

/**
 * Zmienia kąt nachylenia lufy
 *
 * @param window - okno gry
 */
void Tank::moveCannon(sf::RenderWindow &window)
{
    if(crosshairActive_)
    {
        sf::Vector2i rotatePosition;
        sf::Vector2f cannonPosition = cannonSprite_.getPosition();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        rotatePosition.x = mousePosition.x - cannonPosition.x;
        rotatePosition.y = mousePosition.y - cannonPosition.y;

        float angle = atan2f(rotatePosition.y, rotatePosition.x);
        crosshairSprite_.setPosition(cannonPosition);
        crosshairSprite_.move(cos(angle) * 100, sin(angle) * 100);
        cannonSprite_.setRotation(RadianToDegree(angle));
    }
}

/**
 * Zmienia siłę wystrzału pocisku
 *
 * @param direction - kierunek zmiany siły wystrzału pocisku
 *                1 - zwiększenie siły wystrzału pocisku
 *               -1 - zmniejszenie siły wystrzału pocisku
 *
 */
void Tank::moveShootPower(const int direction)
{
    if(!((shootPower_ == 0 && direction < 0) || (shootPower_ == 100 && direction > 0)))
    {
        shootPower_ += direction;
    }
}

/**
 * Obsługuje zdarzenia wykonane przez gracza
 * Obsługiwana jest klawiatura oraz myszka gracza
 *
 * @param event - obiekt wszystkich zdarzeń
 * @param window - okno gry
 */
void Tank::passEvent(sf::Event &event, sf::RenderWindow &window)
{
    if(status_ == 1)
    {
        if(event.type == sf::Event::KeyReleased)
        {
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
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Space)
            {
                shoot();
            }
            if(event.key.code == sf::Keyboard::Up)
            {
                moveShootPower(1);
            }
            if(event.key.code == sf::Keyboard::Down)
            {
                moveShootPower(-1);
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
            if(canCannonMove())
            {
                crosshairActive_ = !crosshairActive_;
                window.setMouseCursorVisible(!crosshairActive_);
            }
        }
    }
}

/**
 * Aktualizuje dane gracza
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 * @param window - okno gry
 */
void Tank::update(const float elapsed, sf::RenderWindow &window)
{
    step(elapsed);
    tankInterface_ -> drawHealth(health_, window);
    if(status_ == 1)
    {
        if(bullet_ == nullptr)
        {
            if((timeLeft_ -= elapsed) <= 0)
            {
                status_ = 2;
            }
        }
        moveTank(elapsed);
        moveCannon(window);
        tankInterface_ -> drawShootPower(shootPower_, window);
        tankInterface_ -> drawTurn(playerID_, timeLeft_, window);
        tankInterface_ -> drawAngle(360 - cannonSprite_.getRotation(), window);
    }
}

/**
 * Wyświetla czołg i jego elementy
 *
 * @param window - okno gry
 */
void Tank::draw(sf::RenderTarget &window)
{
    window.draw(cannonSprite_);
    window.draw(tankSprite_);
    if(status_ == 1)
    {
        if(bullet_)
        {
            if(bullet_ -> getStatus())
            {
                bullet_ -> draw(window);
            }
            else
            {
                shootReset();
            }
        }
        else if(crosshairActive_)
        {
            window.draw(crosshairSprite_);
        }
    }
}

/**
 * Obsługuje grawitacje gracza
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 */
void Tank::step(const float elapsed)
{
    sf::Vector2f TankPosition = tankSprite_.getPosition();
    int landHeight = land -> getLandHeight(tankSprite_.getPosition().x);
    if(TankPosition.y < landHeight)
    {
        freefall_ = true;
        velocityFreefall_ += Gravity * elapsed;

        sf::Vector2f velocity(0.0, 0.0);
        velocity.y = velocityFreefall_ * elapsed;
        if(TankPosition.y + velocity.y >= landHeight)
        {
            velocity.y = landHeight - TankPosition.y + 1;
        }
        tankSprite_.move(velocity);
        cannonSprite_.move(velocity);
        tankSprite_.setRotation(getLandAngle());
    }
    else if(freefall_)
    {
        velocityFreefall_ = 0.0;
        freefall_ = false;
    }
}

/**
 * Zwraca status gracza
 *
 * @return
 *        0 - gracz nie może nic wykonać
 *        1 - gracz może wykonać wszystkie rzeczy
 *        2 - gracz oczekuje na zmianę kolejki
 */
int Tank::getStatus()
{
    return status_;
}

/**
 * Zmienia status gracza
 *
 * @param window - okno gry
 */
void Tank::switchStatus(sf::RenderWindow &window)
{
    timeLeft_ = 15.0;
    if(status_ == 0)
    {
        status_ = 1;
    }
    else
    {
        status_ = 0;
    }
    if(bullet_)
    {
        bullet_.reset();
    }
    moveDirection_ = 0;
    if(crosshairActive_)
    {
        crosshairActive_ = false;
        window.setMouseCursorVisible(true);
    }
}

/**
 * Sprawdza czy gracz może zmienić położenie lufy
 *
 * @return
 *        true - gracz może zmienić położenie lufy
 *        false - gracz nie może zmienić położenia lufy
 */
bool Tank::canCannonMove()
{
    if(status_ == 1 && !freefall_ && !moveDirection_ && bullet_ == nullptr)
    {
        return true;
    }
    return false;
}

/**
 * Sprawdza czy czołg może przemieścić się o wektor [x, y]
 *
 * @param velocity - wektor prędkości
 * @return
 *        true - gracz może się przemieścić swoim czołgiem
 *        false - gracz nie może się przemieścić swoim czołgiem
 */
bool Tank::canTankMove(const sf::Vector2f &velocity)
{
    if(status_ == 1 && !freefall_ && !crosshairActive_ && bullet_ == nullptr && fabs(getLandAngle(velocity)) <= maxAngle_
            && !getEnemyCollision(velocity) && tankSprite_.getPosition().x + velocity.x > 0 && tankSprite_.getPosition().x + velocity.x < WindowWidth)
    {
        return true;
    }
    return false;
}

/**
 * Sprawdza czy czołg ma kolizję z przeciwnikiem po przemieszczeniu się o wektor [x, y]
 *
 * @param velocity - wektor prędkosci
 * @return
 *        true - jest kolizja z przeciwnikiem
 *        false - nie ma kolicji z przeciwnikiem
 */
bool Tank::getEnemyCollision(const sf::Vector2f &velocity)
{
    if(!tankSprite_.getGlobalBounds().intersects(enemy -> tankSprite_.getGlobalBounds()))
    {
        sf::Sprite tempTankSprite = tankSprite_;
        tempTankSprite.move(velocity);
        tempTankSprite.setRotation(getLandAngle(velocity));
        if(tempTankSprite.getGlobalBounds().intersects(enemy -> tankSprite_.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

/**
 * Oblicza nachylenie terenu po przemieszczeniu się o wektor prędkości [x, y]
 *
 * @param velocity - wektor prędkości
 *
 * @return Nachylenie terenu w radianach po przemieszczeniu się o wektor prędkości [x, y]
 */
float Tank::getLandAngle(const sf::Vector2f &velocity)
{
    sf::Sprite tempTankSprite = tankSprite_;
    tempTankSprite.move(velocity);
    return land->getAngleDegree(tempTankSprite.getPosition().x, tempTankSprite.getPosition().y);
}

/**
 * Przesuwa pozycję czołgu oraz jego lufy
 *
 * @param velocity - wektor prędkości przesunięcia gracza
 */
void Tank::moveTankPosition(const sf::Vector2f &velocity)
{
    if(canTankMove(velocity))
    {
        tankSprite_.move(velocity);
        cannonSprite_.move(velocity);
        tankSprite_.setRotation(getLandAngle());
    }
}

/**
 * Ustawia pozycję czołgu oraz jego lufy
 *
 * @param position - aktualna pozycja gracza
 */
void Tank::setTankPosition(const sf::Vector2f &position)
{
    tankSprite_.setPosition(position);
    cannonSprite_.setPosition(position - sf::Vector2f(0, tankSprite_.getLocalBounds().height / 2));
    tankSprite_.setRotation(getLandAngle());
}

/**
 * Usuwa pocisk i zadaje obrażenia trafionym graczom
 */
void Tank::shootReset()
{
    if(bullet_)
    {
        if(bullet_->getStatusExplosion(0))
        {
            health_ -= 25;
        }
        if(bullet_->getStatusExplosion(1))
        {
            enemy->health_ -= 25;
        }
        bullet_.reset();
        status_ = 2;
    }
}

/**
 * Oblicza prawidłową figurę czołgu
 *
 * @param Tank - obiekt klasy sf::Sprite dla którego obliczana jest figura
 *
 * @return Prawidłowa figura czołgu
 */
sf::RectangleShape Tank::getTankShape(const sf::Sprite &Tank)
{
    sf::RectangleShape TankShape(sf::Vector2f(Tank.getLocalBounds().width, Tank.getLocalBounds().height));
    TankShape.setPosition(Tank.getPosition().x, Tank.getPosition().y - Tank.getLocalBounds().height / 2);
    return TankShape;
}
