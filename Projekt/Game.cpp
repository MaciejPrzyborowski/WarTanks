#include "Game.h"

Game::Game()
{
    window_ = make_unique<sf::RenderWindow>(sf::VideoMode(WindowWidth, WindowHeight), NazwaGry);
    window_->setFramerateLimit(WindowFPS);
    window_->setActive(true);
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

    fireworks_ = make_unique<Animation>(FireworksEndGameAnimation, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
    fire_ = make_unique<Animation>(FireEndGameAnimation, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
    backgroundTexture_.loadFromFile(GameBackgroundTextureSrc);
    backgroundSprite_.setTexture(backgroundTexture_);
    backgroundSprite_.setScale((float)WindowWidth/backgroundTexture_.getSize().x, (float)WindowHeight/backgroundTexture_.getSize().y);
}

void Game::Update()
{
    sf::Clock clock;
    while(window_->isOpen())
    {
        playerHp1_ = player1_->returnHp();
        playerHp2_ = player2_->returnHp();
        playerPos1_ = player1_->returnPosition();
        playerPos2_ = player2_->returnPosition();
        sf::Event Event;
        sf::Time elapsed = clock.restart();
        while(window_->pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                window_->close();
            }
            else
            {
                if(Event.type == sf::Event::KeyReleased)
                {
                    if(Event.key.code == sf::Keyboard::Return)
                    {
                        land_->Generate();
                        player1_->Reset();
                        player2_->Reset();
                    }
                }

                if(!GameInterface.checkPlayersHp(playerHp1_, playerHp2_))
                {
                    player1_->passEvent(Event, *window_);
                    player2_->passEvent(Event, *window_);
                }
                if(menu_->getStatus())
                {
                    menu_->passEvent(Event, *window_);
                }
            }
        }
        if(window_->isOpen())
        {
            window_->clear();
            if(menu_->getStatus())
            {
                menu_->draw(*window_);
            }
            else
            {
                window_ -> draw(backgroundSprite_);
                land_ -> step(elapsed.asSeconds());
                land_ -> draw(*window_);
                player1_ -> update(elapsed.asSeconds(), *window_);
                player2_ -> update(elapsed.asSeconds(), *window_);

                if(!GameInterface.checkPlayersHp(playerHp1_, playerHp2_))
                {
                    if(player1_ -> getStatus() == 2 || player2_ -> getStatus() == 2)
                    {
                        player1_ -> switchStatus(*window_);
                        player2_ -> switchStatus(*window_);
                    }
                    if(player1_->getStatus() == 1)
                    {
                        window_->draw(GameInterface.turnRed());
                    }
                    else if(player2_->getStatus() == 1)
                    {
                        window_->draw(GameInterface.turnBlue());
                    }
                    window_->draw(GameInterface.gameTime(elapsed.asSeconds()));
                    player1_->returnTankInterface().drawHp(*window_, playerHp1_);
                    player2_->returnTankInterface().drawHp(*window_, playerHp2_);
                }
                else
                {
                    window_->draw(GameInterface.gameEnd(playerHp1_, playerHp2_));

                    if(GameInterface.showAnimations_())
                    {
                        fireworks_->draw(elapsed.asSeconds(), sf::Vector2f(GameInterface.Winner(playerHp1_, playerHp2_, playerPos1_, playerPos2_).x - 50, GameInterface.Winner(playerHp1_, playerHp2_, playerPos1_, playerPos2_).y - 120), *window_);
                        fire_->draw(elapsed.asSeconds(), sf::Vector2f(GameInterface.Loser(playerHp1_, playerHp2_, playerPos1_, playerPos2_).x - 50, GameInterface.Loser(playerHp1_, playerHp2_, playerPos1_, playerPos2_).y - 90), *window_);
                    }
                    GameInterface.backToMenuText(elapsed.asSeconds(), *window_);
                }
            }
            window_ -> display();
        }
    }
}
