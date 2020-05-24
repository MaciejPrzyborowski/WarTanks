#include "Game.h"

Game::Game()
{
    window_ = make_unique<sf::RenderWindow>(sf::VideoMode(WindowWidth, WindowHeight), NazwaGry);
    window_->setFramerateLimit(WindowFPS);
}

void Game::Run()
{
    Initialize();
    Update();
}

void Game::Initialize()
{
    menu_ = make_unique<Menu>();
    land_ = make_unique<Land>(4, 0.2);
    player1_ = make_unique<Tank>(1, true, TankTextureSrc1, *land_);
    player2_ = make_unique<Tank>(2, false, TankTextureSrc2, *land_);

    GameBackground.loadFromFile(GameBackgroundTextureSrc);
    GameSprite.setTexture(GameBackground);
    GameSprite.setScale((float)WindowWidth/GameBackground.getSize().x, (float)WindowHeight/GameBackground.getSize().y);
}

void Game::Update()
{
    sf::Clock clock;
    while(window_->isOpen())
    {
        sf::Event Event;
        sf::Time elapsed = clock.restart();

        while(window_->pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                window_->close();
            }
            if(Event.type == sf::Event::KeyReleased)
            {
                if(Event.key.code == sf::Keyboard::Return)
                {
                    land_->Generate();
                    player1_->Reset();
                    player2_->Reset();
                }
            }
            player1_->passEvent(Event);
            player2_->passEvent(Event);
            menu_->ShowSwitch(Event, *window_);
        }
        if(player1_->isMoving())
        {
            player1_->move(elapsed.asSeconds());
        }
        if(player2_->isMoving())
        {
            player2_->move(elapsed.asSeconds());
        }
        window_->clear();
        if(menu_->IsActiveMenu())
        {
            menu_->ShowMenu(*window_, clock);
        }
        else
        {
            window_->draw(GameSprite);
            land_->draw(*window_);
            player1_->draw(*window_);
            player2_->draw(*window_);
        }
        window_->display();
    }
}
