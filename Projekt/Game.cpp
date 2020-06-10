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
    player1_->enemy = player2_.get();
    player2_->enemy = player1_.get();

    backgroundTexture_.loadFromFile(GameBackgroundTextureSrc);
    backgroundSprite_.setTexture(backgroundTexture_);
    backgroundSprite_.setScale((float)WindowWidth/backgroundTexture_.getSize().x, (float)WindowHeight/backgroundTexture_.getSize().y);
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
                if(Event.key.code == sf::Keyboard::Q)
                {
                    player1_ -> switchStatus(player2_ -> getTankSprite(), *window_);
                    player2_ -> switchStatus(player1_ -> getTankSprite(), *window_);
                }
            }
            player1_->passEvent(Event, *window_);
            player2_->passEvent(Event, *window_);
            menu_->ShowSwitch(Event, *window_);
        }
        window_->clear();
        if(menu_->IsActiveMenu())
        {
            menu_->ShowMenu(*window_, clock);
        }
        else
        {
            window_ -> draw(backgroundSprite_);
            land_ -> step(elapsed.asSeconds());
            land_ -> draw(*window_);
            player1_ -> update(elapsed.asSeconds(), *window_);
            player2_ -> update(elapsed.asSeconds(), *window_);
            if(player1_ -> getStatus() == 2 || player2_ -> getStatus() == 2)
            {
                player1_ -> switchStatus(player2_ -> getTankSprite(), *window_);
                player2_ -> switchStatus(player1_ -> getTankSprite(), *window_);
            }
        }
        window_ -> display();
    }
}
