#include "Game.h"

Game::Game()
{
    gameBackgroundTexture_.loadFromFile(GameBackgroundTextureSrc);
    gameBackgroundSprite_.setTexture(gameBackgroundTexture_);
    gameBackgroundSprite_.setScale((float)WindowWidth/gameBackgroundTexture_.getSize().x, (float)WindowHeight/gameBackgroundTexture_.getSize().y);
    menuBackgroundTexture_.loadFromFile(MenuBackgroundTextureSrc);
    menuBackgroundSprite_.setTexture(menuBackgroundTexture_);
    menuBackgroundSprite_.setScale((float)WindowWidth / menuBackgroundTexture_.getSize().x, (float)WindowHeight / menuBackgroundTexture_.getSize().y);

    menuMusicBuffer_.loadFromFile(MenuMusicSrc);
    menuMusic_.setBuffer(menuMusicBuffer_);
    menuMusic_.setVolume(5);
    menuMusic_.setLoop(true);
    gameBuffer_.loadFromFile(GameMusicSrc);
    gameMusic_.setBuffer(gameBuffer_);
    gameMusic_.setVolume(30);
    gameMusic_.setLoop(true);
    fireworksBuffer_.loadFromFile(FireWorksSoundSrc);
    fireworksSound_.setBuffer(fireworksBuffer_);
    fireworksSound_.setVolume(5);
    srand(time(NULL));
}

void Game::run()
{
    land = dynamic_cast<Land *>(world.addObject(ObjectType::Land));
    world.addObject(ObjectType::Tank);
    world.addObject(ObjectType::Tank);

    GameInterface_ = make_unique<Interface>();
    menu_ = make_unique<Menu>();

    initialize(GameState::Menu);
}

void Game::initialize(const GameState &gameState)
{
    gameState_ = gameState;
    if(gameState == GameState::Menu)
    {
        menu_ -> reset(false);
        playGameMusic(false);
        playMenuMusic(menu_->getGameSettings(GameSetting::MenuMusic));
        fireworksSound_.stop();
    }
    else if(gameState == GameState::Play)
    {
        world.resetAll();
        GameInterface_->reset();
        playGameMusic(menu_->getGameSettings(GameSetting::GameMusic));
        playMenuMusic(false);
        fireworks_ = make_unique<Animation>(FireworksEndGameAnimationSrc, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
        fire_ = make_unique<Animation>(FireEndGameAnimationSrc, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
    }
}

void Game::passEvent(sf::RenderWindow &window, sf::Event &event)
{
    if(gameState_ == GameState::Menu)
    {
        if(menu_->getMenuStatus())
        {
            controll_.menuPassEvent(event, window, menu_);
            playMenuMusic(menu_->getGameSettings(GameSetting::MenuMusic));
        }
        else
        {
            initialize(GameState::Play);
        }
    }
    else if(gameState_ == GameState::Play)
    {
        for(auto &object : world.objects_)
        {
            auto tankID = dynamic_cast<Tank *>(object.get());
            if(tankID)
            {
                controll_.tankPassEvent(event, window, tankID);
            }
        }
    }
    else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
    {
        initialize(GameState::Menu);
    }
}

void Game::update(sf::RenderWindow &window, sf::Time &elapsed)
{
    if(window.isOpen())
    {
        if(gameState_ == GameState::Menu)
        {
            if(menu_ -> getMenuStatus())
            {
                window.draw(menuBackgroundSprite_);
                menu_ -> draw(window);
            }
            else
            {
                initialize(GameState::Play);
            }
        }
        else
        {
            window.draw(gameBackgroundSprite_);
            world.drawAll(window);
            world.getCollisionAll();
            int playerHealth[2];
            for(auto &object : world.objects_)
            {
                auto tankID = dynamic_cast<Tank *>(object.get());
                if(tankID)
                {
                    playerHealth[tankID->playerID_ - 1] = tankID->returnHp();
                }
            }
            if(gameState_ == GameState::Play)
            {
                if(playerHealth[0] > 0 && playerHealth[1] > 0)
                {
                    world.stepAll(elapsed.asSeconds());
                    for(auto &object : world.objects_)
                    {
                        auto tankID = dynamic_cast<Tank *>(object.get());
                        if(tankID)
                        {
                            tankID->update(elapsed.asSeconds(), window);
                            if(tankID -> getStatus() == TankState::Switch)
                            {
                                tankID -> switchStatus(window);
                                for(auto &object2 : world.objects_)
                                {
                                    auto tankID2 = dynamic_cast<Tank *>(object2.get());
                                    if(tankID2 && tankID2 != tankID)
                                    {
                                        tankID2 -> switchStatus(window);
                                    }
                                }
                            }
                        }
                    }
                    GameInterface_ -> drawGameTime(elapsed.asSeconds(), window);
                }
                else if(playerHealth[0] > 0 || playerHealth[1] > 0)
                {
                    initialize(GameState::EndWinner);
                    //vector<sf::Vector2f> position = GameInterface_ -> checkWinner(playerHealth, player1_->returnPosition(), player2_->returnPosition());
                    //winner_ = position[0];
                    //loser_ = position[1];
                }
                else
                {
                    initialize(GameState::EndDraw);
                }
            }
            else
            {
                GameInterface_ -> drawGameEnd(elapsed.asSeconds(), window);
                if(gameState_ == GameState::EndWinner)
                {
                    playGameMusic(false);
                    playFireworksSound();
                    fireworks_ -> draw(elapsed.asSeconds(), winner_, window);
                    fire_ -> draw(elapsed.asSeconds(), loser_, window);
                }
            }
        }
        if(menu_->getGameSettings(GameSetting::FPS))
        {
            GameInterface_ -> drawFPS(elapsed.asSeconds(), window);
        }
    }
}

void Game::playMenuMusic(const bool &isMenuMusicOn)
{
    if(isMenuMusicOn && menuMusic_.getStatus() != sf::Music::Playing)
    {
        menuMusic_.play();
    }
    else if(!isMenuMusicOn)
    {
        menuMusic_.stop();
    }
}

void Game::playGameMusic(const bool &isGameMusicOn)
{
    if(isGameMusicOn && gameMusic_.getStatus() != sf::Music::Playing)
    {
        gameMusic_.play();
    }
    else if(!isGameMusicOn)
    {
        gameMusic_.stop();
    }
}

void Game::playFireworksSound()
{
    if(fireworksSound_.getStatus() != sf::Music::Playing)
    {
        fireworksSound_.play();
    }
}
