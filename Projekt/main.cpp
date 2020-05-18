#include <Land.h>
#include <Menu.h>
#include <Tank.h>
#include <Globals.h>

int main()
{
    //sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    //sf::RenderWindow window(desktop, NazwaGry, sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(WindowWidth,WindowHeight), NazwaGry);
    window.setFramerateLimit(120);
    sf::SoundBuffer Buffer;
    Buffer.loadFromFile("menu_music.wav");
    sf::Sound BackgroundMusic;
    BackgroundMusic.setBuffer(Buffer);
    BackgroundMusic.setVolume(10);

    sf::SoundBuffer Buffer2;
    Buffer2.loadFromFile("select_sound.wav");
    sf::Sound SelectSound;
    SelectSound.setBuffer(Buffer2);
    SelectSound.setVolume(1);

    Menu Menu;

    sf::Texture MenuBackground;
    MenuBackground.loadFromFile("menu_background.jpg");
    sf::Sprite Sprite;
    Sprite.setTexture(MenuBackground);
    sf::Vector2u TextureSize = MenuBackground.getSize();
    float scaleX = (float)WindowWidth/TextureSize.x;
    float scaleY = (float)WindowHeight/TextureSize.y;
    Sprite.setScale(scaleX, scaleY);

    Land Land(4, 0.2);
    Tank Tank;
    sf::Clock Clock;
    Menu.MainMenu();
    Menu.Settings();
    Menu.PlaySettings();

    sf::Texture GameBackground;
    GameBackground.loadFromFile("game_background.jpg");
    sf::Sprite GameSprite;
    GameSprite.setTexture(GameBackground);
    sf::Vector2u TextureSize2 = MenuBackground.getSize();
    float scaleX2 = (float)WindowWidth/TextureSize2.x;
    float scaleY2 = (float)WindowHeight/TextureSize2.y;
    GameSprite.setScale(scaleX2, scaleY2);

    while(window.isOpen())
    {
        sf::Event Event;

        while(window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(Menu.GetMenuStatus())
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    Menu.MoveUp(SelectSound);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    Menu.MoveDown(SelectSound);
                }
                if(Event.type == sf::Event::KeyReleased || sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(Event.key.code == sf::Keyboard::Return || sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        switch(Menu.GetIndex())
                        {
                        case 0:
                            Menu.PlaySettingsActive();
                            break;
                        case 1:
                            Menu.SettingsActive();
                            break;
                        case 2:
                            window.close();
                            break;
                        }
                    }
                }
                Menu.ChoiceByMouse(window, Event, SelectSound);
            }

            else if(Menu.GetPlaySettingsStatus())
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    Menu.MoveUp(SelectSound);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    Menu.MoveDown(SelectSound);
                }
                if(Event.type == sf::Event::KeyReleased || sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(Event.key.code == sf::Keyboard::Return || sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        switch(Menu.GetIndex())
                        {
                        case 0:
                            Menu.HideMenu();
                            Land.Generate();
                            Tank.Reset();
                            break;
                        case 1:
                            Menu.HideMenu();
                            Land.Generate();
                            break;
                        case 2:
                            Menu.MainMenuActive();
                            break;
                        }
                    }
                }
                Menu.ChoiceByMouse(window, Event, SelectSound);
            }

            else if(Menu.GetSettingsStatus())
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    Menu.MoveUp(SelectSound);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    Menu.MoveDown(SelectSound);
                }
                if(Event.type == sf::Event::KeyReleased || sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(Event.key.code == sf::Keyboard::Return || sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        switch(Menu.GetIndex())
                        {
                        case 0:
                            std::cout << "FPS" << std::endl;
                            break;
                        case 1:
                            std::cout << "Muzyka" << std::endl;
                            break;
                        case 2:
                            std::cout << "Dzwiek" << std::endl;
                            break;
                        case 3:
                            std::cout << "Sterowanie" << std::endl;
                            break;
                        case 4:
                            Menu.MainMenuActive();
                            break;
                        }
                    }
                }
                Menu.ChoiceByMouse(window, Event, SelectSound);
            }
            else if(Event.type == sf::Event::KeyReleased)
            {
                if(Event.key.code == sf::Keyboard::Return)
                {
                    Land.Generate();
                    Tank.Reset();
                }
            }

        }

        window.clear();

        window.draw(GameSprite);
        Land.Draw(window);
        Tank.Draw(window, Land);

        if((Menu.GetMenuStatus() || Menu.GetSettingsStatus() || Menu.GetPlaySettingsStatus()))
        {
            window.draw(Sprite);
            if(BackgroundMusic.getStatus() != sf::SoundStream::Playing)
            {
                BackgroundMusic.play();
            }
        }
        else
        {
            BackgroundMusic.stop();
        }

        if(Menu.GetMenuStatus()) Menu.ShowMenu(window);
        if(Menu.GetSettingsStatus()) Menu.ShowSettings(window);
        if(Menu.GetPlaySettingsStatus()) Menu.ShowPlaySettings(window);

        window.display();
    }

    return 0;
}

