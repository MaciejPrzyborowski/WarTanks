#include "Controll.h"
#include "Application.h"

Controll::Controll()
{

}

void Controll::menuPassEvent(const sf::Event &event, sf::RenderWindow &window, unique_ptr<Menu> &menu)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Up)
        {
            menu->move(-1);
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            menu->move(1);
        }
    }
    if(event.type == sf::Event::MouseMoved)
    {
        menu->setMouseActive(window);
    }
    if((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) ||
            (menu->isMouseActive() && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased))
    {
        if(!menu->getMenuChoice())
        {
            window.close();
        }
    }
}

void Controll::tankPassEvent(const sf::Event &event, sf::RenderWindow &window, WorldObject *object)
{
    auto tankID = dynamic_cast<Tank *>(object);
    if(tankID->getStatus() == TankState::Active)
    {
        if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Left)
            {
                if(tankID->moveDirection_ == TankMove::Left)
                {
                    tankID->moveDirection_ = TankMove::None;
                }
            }
            if(event.key.code == sf::Keyboard::Right)
            {
                if(tankID->moveDirection_ == TankMove::Right)
                {
                    tankID->moveDirection_ = TankMove::None;
                }
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
                tankID->moveShootPower(1);
            }
            if(event.key.code == sf::Keyboard::Down)
            {
                tankID->moveShootPower(-1);
            }
            if(event.key.code == sf::Keyboard::Left)
            {
                tankID->moveDirection_ = TankMove::Left;
            }
            if(event.key.code == sf::Keyboard::Right)
            {
                tankID->moveDirection_ = TankMove::Right;
            }
        }
        if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            tankID->setCursorVisibility(window);
        }
    }
}
