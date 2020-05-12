#include <Land.h>
#include <menu.h>
#include <Tank.h>
#include <Globals.h>

int main()
{
    sf::SoundBuffer Buffer;
    Buffer.loadFromFile("menu_music.wav");
    sf::Sound BackGroundMusic;
    BackGroundMusic.setBuffer(Buffer);
    //sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    //sf::RenderWindow window(desktop, NazwaGry, sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(800, 600), NazwaGry);
    float x = window.getSize().x;
    menu Menu;
    Land Land(4, 0.2);
    Tank Tank;

    sf::Clock clock;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Up)
                    Menu.MoveUp();
                if(event.key.code == sf::Keyboard::Down)
                    Menu.MoveDown();
                if(event.key.code == sf::Keyboard::Return)
                {
                    switch(Menu.ReturnIndex())
                    {
                    case 0:
                        Menu.HideMenu();
                        Land.Generate();
                        Tank.Reset();
                        Menu.PlayOption();
                        break;
                    case 1:
                        std::cout << "Opcje" << std::endl;
                        break;
                    case 2:
                        window.close();
                    }
                }
            }

            if(BackGroundMusic.getStatus() != sf::SoundStream::Playing)
            {
                BackGroundMusic.play();
                BackGroundMusic.setVolume(10);
            }
        }
        //sf::Time elapsed = clock.restart();
        window.clear();
        Land.Draw(window);
        Tank.Draw(window, Land);
        Menu.ShowMenu(window, x);
        window.display();
    }
    return 0;
}
