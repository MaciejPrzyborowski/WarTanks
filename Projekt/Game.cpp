#include "Game.h"

Game::Game()
{
    window_ = make_unique<sf::RenderWindow>(sf::VideoMode(WindowWidth, WindowHeight), NazwaGry);
    window_->setFramerateLimit(WindowFPS);
    window_->setActive(true);
    gameBackgroundTexture_.loadFromFile(GameBackgroundTextureSrc);
    gameBackgroundSprite_.setTexture(gameBackgroundTexture_);
    gameBackgroundSprite_.setScale((float)WindowWidth/gameBackgroundTexture_.getSize().x, (float)WindowHeight/gameBackgroundTexture_.getSize().y);
    menuBackgroundTexture_.loadFromFile(MenuBackgroundTextureSrc);
    menuBackgroundSprite_.setTexture(menuBackgroundTexture_);
    menuBackgroundSprite_.setScale((float)WindowWidth / menuBackgroundTexture_.getSize().x, (float)WindowHeight / menuBackgroundTexture_.getSize().y);
}

void Game::run()
{
    menu_ = make_unique<Menu>();

    initialize(GameMenu);
    update();
}

void Game::initialize(GameState gameState)
{
    gameState_ = gameState;
    if(gameState == GameMenu)
    {
        menu_->setMenu(MenuMain);
    }
    else if(gameState == GamePlay)
    {
        land_ = make_unique<Land>(4, 0.2);
        land_->generate();

        player1_ = make_unique<Tank>(1, true, TankTextureSrc1, *land_);
        player2_ = make_unique<Tank>(2, false, TankTextureSrc2, *land_);
        player1_->enemy = player2_.get();
        player2_->enemy = player1_.get();

        GameInterface_ = make_unique<Interface>();
        fireworks_ = make_unique<Animation>(FireworksEndGameAnimationSrc, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
        fire_ = make_unique<Animation>(FireEndGameAnimationSrc, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
    }
}

void Game::passEvent(sf::Event &Event)
{
    if(Event.type == sf::Event::Closed)
    {
        window_->close();
    }
    else if(gameState_ == GameMenu)
    {
        if(menu_->getStatus())
        {
            menu_->passEvent(Event, *window_);
        }
        else
        {
            initialize(GamePlay);
        }
    }
    else if(gameState_ == GamePlay)
    {
        if(!GameInterface_->checkPlayersHp(playerHp1_, playerHp2_))
        {
            player1_->passEvent(Event, *window_);
            player2_->passEvent(Event, *window_);
        }
        else if(Event.type == sf::Event::KeyReleased)
        {
            if(Event.key.code == sf::Keyboard::Return)
            {
                initialize(GameMenu);
            }
        }
    }
}

void Game::updateAll(sf::Time elapsed)
{
    if(window_->isOpen())
    {
        window_->clear();
        if(gameState_ == GameMenu)
        {
            if(menu_->getStatus())
            {
                window_ -> draw(menuBackgroundSprite_);
                menu_->draw(*window_);
            }
            else
            {
                initialize(GamePlay);
            }
        }
        else if(gameState_ == GamePlay)
        {
            playerHp1_ = player1_->returnHp();
            playerHp2_ = player2_->returnHp();
            playerPos1_ = player1_->returnPosition();
            playerPos2_ = player2_->returnPosition();
            window_->clear();
            window_ -> draw(gameBackgroundSprite_);
            land_ -> step(elapsed.asSeconds());
            land_ -> draw(*window_);
            player1_ -> update(elapsed.asSeconds(), *window_);
            player2_ -> update(elapsed.asSeconds(), *window_);

            if(!GameInterface_->checkPlayersHp(playerHp1_, playerHp2_))
            {
                if(player1_ -> getStatus() == 2 || player2_ -> getStatus() == 2)
                {
                    player1_ -> switchStatus(*window_);
                    player2_ -> switchStatus(*window_);
                }
                if(player1_->getStatus() == 1)
                {
                    GameInterface_->turnRed(*window_, player1_->returnTimeLeft());
                }
                else if(player2_->getStatus() == 1)
                {
                    GameInterface_->turnBlue(*window_, player2_->returnTimeLeft());
                }
                window_->draw(GameInterface_->gameTime(elapsed.asSeconds()));
                player1_->returnTankInterface().drawHp(*window_, playerHp1_);
                player2_->returnTankInterface().drawHp(*window_, playerHp2_);
            }
            else
            {
                window_->draw(GameInterface_->gameEnd(playerHp1_, playerHp2_));

                if(GameInterface_->showAnimations_())
                {
                    fireworks_->draw(elapsed.asSeconds(), sf::Vector2f(GameInterface_->winner(playerHp1_, playerHp2_, playerPos1_, playerPos2_).x - 50, GameInterface_->winner(playerHp1_, playerHp2_, playerPos1_, playerPos2_).y - 120), *window_);
                    fire_->draw(elapsed.asSeconds(), sf::Vector2f(GameInterface_->loser(playerHp1_, playerHp2_, playerPos1_, playerPos2_).x - 50, GameInterface_->loser(playerHp1_, playerHp2_, playerPos1_, playerPos2_).y - 90), *window_);
                }
                GameInterface_->backToMenuText(*window_, elapsed.asSeconds());
            }
        }
        window_ -> display();
    }
}

void Game::update()
{
    sf::Clock clock;
    while(window_->isOpen())
    {
        sf::Event Event;
        sf::Time elapsed = clock.restart();
        while(window_->pollEvent(Event))
        {
            passEvent(Event);
        }
        updateAll(elapsed);
    }
}
