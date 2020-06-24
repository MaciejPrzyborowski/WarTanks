#include "Controll.h"
#include "Application.h"

Controll::Controll()
{

}

void Controll::menuPassEvent(const sf::Event &event, sf::RenderWindow &window, unique_ptr<Menu> &menu)
{
    if(window.isOpen())
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Up)
            {
                menu->move(MenuMove::Up);
            }
            if(event.key.code == sf::Keyboard::Down)
            {
                menu->move(MenuMove::Down);
            }
        }
        if(event.type == sf::Event::MouseMoved)
        {
            menu->setMouseActive(window);
        }
        if((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) ||
                (menu->isMouseActive() && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased))
        {
            menu->getMenuChoice();
        }
    }
}

void Controll::tankPassEvent(const sf::Event &event, sf::RenderWindow &window, WorldObject *object)
{
    if(window.isOpen())
    {
        auto tankID = dynamic_cast<Tank *>(object);
        if(tankID->getStatus() == TankState::Active)
        {
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                {
                    tankID->setMoveDirection(TankMove::None);
                }
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    tankID->shoot();
                }
                if(event.key.code == sf::Keyboard::Up)
                {
                    tankID->moveShootPower(ShootPowerMove::LevelUp);
                }
                if(event.key.code == sf::Keyboard::Down)
                {
                    tankID->moveShootPower(ShootPowerMove::LevelDown);
                }
                if(event.key.code == sf::Keyboard::Left)
                {
                    tankID->setMoveDirection(TankMove::Left);
                }
                if(event.key.code == sf::Keyboard::Right)
                {
                    tankID->setMoveDirection(TankMove::Right);
                }
            }
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                tankID->switchCursorVisibility(window);
            }
        }
    }
}
