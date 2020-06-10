#include "Animation.h"

Animation::Animation(sf::Vector2f position)
{
    texture.loadFromFile(name);
    explosion.setRadius(30);
    explosion.setOrigin(explosion.getOrigin().x + 30, explosion.getOrigin().y + 30);
    explosion.setTexture(&texture);
    explosion.setTextureRect(coords);
    explosion.setPosition(position);
}

void Animation::Explode(float elapsed, sf::RenderTarget &window)
{
    if(!isExplosionEnd)
    {
        time += elapsed;

        if(time >= 0.1f)
        {
            coords.left += 60;
            time -= 0.1;
        }
        explosion.setTextureRect(coords);
        if(coords.left == 480)
        {
            isExplosionEnd = true;
            coords.left = 0;
        }
        window.draw(explosion);
    }
}
