#include "Application.h"

void Application::run()
{
    window_.create(sf::VideoMode(WindowWidth, WindowHeight), NazwaGry);
    window_.setFramerateLimit(WindowFPS);
    window_.setActive(true);
    game_.run();
    sf::Clock clock;
    while(window_.isOpen())
    {
        sf::Event event;
        sf::Time elapsed = clock.restart();
        while(window_.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                window_.close();
            }
            else
            {
                game_.passEvent(window_, event);
            }
        }
        window_.clear();
        game_.updateAll(window_, elapsed);
        window_.display();
    }
}

void Application::quit()
{
    window_.close();
}

sf::RenderWindow &Application::getWindow()
{
    return window_;
}

Game &Application::getGame()
{
    return game_;
}

sf::RenderWindow Application::window_;
Game Application::game_;
