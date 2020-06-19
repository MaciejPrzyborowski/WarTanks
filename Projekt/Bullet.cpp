#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f &position, const sf::RectangleShape &client, const sf::RectangleShape &target, Land &land_) :
    land(&land_),
    status_(BulletState::Active),
    clientExploded_(false),
    targetExploded_(false),
    explodeSize_(30),
    client_(client),
    target_(target),
    acceleration_(0, Gravity),
    velocity_(0, 0)
{
    bullet_.setRadius(4.0);
    bullet_.setFillColor(sf::Color::Red);
    bullet_.setOrigin(bullet_.getRadius(), bullet_.getRadius());
    bullet_.setPosition(position);

    explodeSoundBuffer_.loadFromFile(ExplodeSoundSrc);
    explodeSound_.setBuffer(explodeSoundBuffer_);
    explodeSound_.setVolume(10);
}

/**
 * Przesuwa pocisk o wektor velocity_ zgodnie z upływem czasu
 *
 * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
 */
void Bullet::move(const float &elapsed)
{
    if(status_ == BulletState::Active)
    {
        if(bullet_.getPosition().x < 0 || bullet_.getPosition().x > WindowWidth || bullet_.getPosition().y >= WindowHeight)
        {
            status_ = BulletState::InActive;
        }
        else if(intersects(bullet_, target_) || intersects(bullet_, client_) || bullet_.getPosition().y + bullet_.getRadius() >= land->getLandHeight(bullet_.getPosition().x))
        {
            explode();
        }
        velocity_ += acceleration_ * elapsed;
        bullet_.move(velocity_ * elapsed);
    }
}

/**
 * Wywołuje funkcję przesunięcia i wyświetlenia pocisku oraz jego wybuchu
 *
 * @param window - okno gry
 */
void Bullet::draw(sf::RenderTarget &window)
{
    sf::Time elapsed = clock_.restart();
    if(explode_)
    {
        if(explode_->getStatus())
        {
            explode_->draw(elapsed.asSeconds(), bullet_.getPosition() - sf::Vector2f{(float)explodeSize_, (float)explodeSize_}, window);
        }
        else
        {
            status_ = BulletState::InActive;
        }
    }
    else
    {
        move(elapsed.asSeconds());
        window.draw(bullet_);
    }
}

/**
 * Wykonuje eksplozję w miejscu kolizji
 */
void Bullet::explode()
{
    status_ = BulletState::Explode;
    sf::CircleShape explosionBullet = bullet_;
    explosionBullet.setOrigin(explodeSize_, explodeSize_);
    explosionBullet.setRadius(explodeSize_);
    if(intersects(explosionBullet, target_))
    {
        targetExploded_ = true;
    }
    if(intersects(explosionBullet, client_))
    {
        clientExploded_ = true;
    }
    if(explodeSound_.getStatus() != sf::Music::Playing)
    {
        explodeSound_.play();
    }
    land->destroyCircle(bullet_.getPosition().x, bullet_.getPosition().y, explodeSize_);
    explode_ = make_unique<Animation>(ExplosionTextureSrc, sf::IntRect(0, 0, 60, 60), 60, 30, false, 1.0);
}

/**
 * Sprawdza czy pocisk trafił w gracza
 *
 * @param target
 *              0 - osoba, która stworzyła pocisk
 *              1 - przeciwnik
 *
 * @return
 *        true - pocisk trafił gracza
 *        false - pocisk nie trafił gracza
 */
bool Bullet::getStatusExplosion(const int &target)
{
    if(target == 0)
    {
        return clientExploded_;
    }
    return targetExploded_;
}

/**
 * Sprawdza status pocisku
 *
 * @return
 *         BulletState::InActive - pocisk nie jest aktywny
 *         BulletState::Active - pocisk jest aktywny, porusza i wyświetla się
 *         BulletState::Explode - pocisk exploduje w trafionym punkcie
 */
BulletState Bullet::getStatus()
{
    return status_;
}

/**
 * Ustawia przyśpieszenie pocisku
 *
 * @param acceleration - przyśpieszenie pocisku dla współrzędnych (x, y)
 */
void Bullet::setAcceleration(const sf::Vector2f &acceleration)
{
    acceleration_ = acceleration;
}

/**
 * Ustawia prędkość pocisku
 *
 * @param acceleration - prędkość pocisku dla współrzędnych (x, y)
 */
void Bullet::setVelocity(const sf::Vector2f &velocity)
{
    velocity_ = velocity;
}

/**
 * Sprawdza czy pocisk uderzył w gracza
 *
 * @param bullet - dane pocisku
 * @param Tank - dane gracza
 *
 * @return
 *          true - pocisk uderzył w gracza
 *          false - pocisk nie uderzył w gracza
 */
bool Bullet::intersects(const sf::CircleShape &bullet, const sf::RectangleShape &Tank)
{
    sf::Vector2f BulletDistance;
    BulletDistance.x = fabs(bullet.getPosition().x - Tank.getPosition().x);
    BulletDistance.y = fabs(bullet.getPosition().y - Tank.getPosition().y);
    double CornerDistance = powf((BulletDistance.x - Tank.getLocalBounds().width / 2), 2) +
            powf((BulletDistance.y - Tank.getLocalBounds().height / 2), 2);

    if((BulletDistance.x <= Tank.getLocalBounds().width / 2)
            && (bullet.getRadius() && BulletDistance.y <= Tank.getLocalBounds().height / 2 + bullet.getRadius()))
    {
        return true;
    }
    return (CornerDistance <= powf((bullet.getRadius()), 2));
}
