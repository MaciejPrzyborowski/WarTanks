#include "Land.h"
#include "Tank.h"
#include "Menu.h"
#include "Globals.h"

int main()
{
    sf::RenderWindow Window(sf::VideoMode(WindowWidth,WindowHeight), NazwaGry);

    Menu Menu;

    Land Land(4, 0.2);
    Tank Tank;

    sf::Texture GameBackground;
    GameBackground.loadFromFile("game_background.jpg");
    sf::Sprite GameSprite;
    GameSprite.setTexture(GameBackground);

    sf::Vector2u TextureSize2 = GameBackground.getSize();
    float scaleX2 = (float)WindowWidth/TextureSize2.x;
    float scaleY2 = (float)WindowHeight/TextureSize2.y;
    GameSprite.setScale(scaleX2, scaleY2);

    sf::Clock Clock;

    while(Window.isOpen())
    {
        sf::Event Event;

        while(Window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                Window.close();
            }
            else if(Event.type == sf::Event::KeyReleased)
            {
                if(Event.key.code == sf::Keyboard::Return)
                {
                    Land.Generate();
                    Tank.Reset();
                }
            }
            Menu.ShowSwitch(Event, Window);
        }

        Window.clear();
        if(Menu.IsActiveMenu())
        {
            Menu.ShowMenu(Window, Clock);
        }
        else
        {
            Window.draw(GameSprite);
            Land.Draw(Window);
            Tank.Draw(Window, Land);
        }
        Clock.restart();
        Window.display();
    }
    return 0;
}
