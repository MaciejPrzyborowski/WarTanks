#include "Game.h"

Game::Game() :
    winnerID_(Winner::None),
    taskCounter(0),
    fireworks_(nullptr),
    fire_(nullptr),
    menu_(nullptr),
    gameInterface_(nullptr),
    world(nullptr),
    land(nullptr)
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
    fireworksSound_.setLoop(true);
}

void Game::run()
{
    menu_ = make_unique<Menu>();
    world = make_unique<World>();
    gameInterface_ = make_unique<Interface>();

    land = dynamic_cast<Land *>(world -> addObject(ObjectType::Land));
    for(size_t i = 0; i < MaxPlayers; i++)
    {
        world -> addObject(ObjectType::Tank);
    }
    initialize(GameState::Menu);
}

void Game::initialize(const GameState &gameState)
{
    gameState_ = gameState;
    if(gameState == GameState::Menu)
    {
        winnerID_ = Winner::None;
        menu_ -> reset(false);

        playGameMusic(false);
        playFireworksSound(false);
        playMenuMusic(menu_ -> getGameSettings(GameSetting::MenuMusic));
    }
    else if(gameState == GameState::Play)
    {
        winnerID_ = Winner::None;
        world -> resetAll();
        gameInterface_ -> reset();

        playMenuMusic(false);
        playFireworksSound(false);
        playGameMusic(menu_ -> getGameSettings(GameSetting::GameMusic));
    }
    else if(gameState == GameState::EndWinner)
    {
        playMenuMusic(false);
        playGameMusic(false);
        playFireworksSound(true);

        fireworks_ = make_unique<Animation>(FireworksEndGameAnimationSrc, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
        fire_ = make_unique<Animation>(FireEndGameAnimationSrc, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
        for(const auto &object : world -> objects_)
        {
            auto tank = dynamic_cast<Tank *>(object.get());
            if(tank != nullptr)
            {
                if(winnerID_ == (Winner)tank -> getPlayerID())
                {
                    fireworks_ -> changePosition(tank -> getTankPosition() - sf::Vector2f(50, 100));
                }
                else
                {
                    fire_ -> changePosition(tank -> getTankPosition() - sf::Vector2f(50, 80));
                }
            }
        }
    }
}

void Game::passEvent(sf::RenderWindow &window, sf::Event &event)
{
    if(window.isOpen())
    {
        if(gameState_ == GameState::Menu)
        {
            if(menu_ -> getMenuStatus())
            {
                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        menu_ -> move(MenuMove::Up);
                    }
                    if(event.key.code == sf::Keyboard::Down)
                    {
                        menu_ -> move(MenuMove::Down);
                    }
                }
                if(event.type == sf::Event::MouseMoved)
                {
                    menu_ -> setMouseActive(window);
                }
                if((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) ||
                        (menu_ -> isMouseActive() && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased))
                {
                    menu_ -> getMenuChoice();
                }
                playMenuMusic(menu_ -> getGameSettings(GameSetting::MenuMusic));
            }
        }
        else if(gameState_ == GameState::Play)
        {
            for(auto &object : world -> objects_)
            {
                auto tankID = dynamic_cast<Tank *>(object.get());
                if(tankID != nullptr)
                {
                    if(tankID -> getStatus() == TankState::Active)
                    {
                        if(event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right))
                        {
                            tankID -> setMoveDirection(TankMove::None);
                        }
                        if(event.type == sf::Event::KeyPressed)
                        {
                            if(event.key.code == sf::Keyboard::Space)
                            {
                                tankID -> shoot();
                            }
                            if(event.key.code == sf::Keyboard::Up)
                            {
                                tankID -> moveShootPower(ShootPowerMove::LevelUp);
                            }
                            if(event.key.code == sf::Keyboard::Down)
                            {
                                tankID -> moveShootPower(ShootPowerMove::LevelDown);
                            }
                            if(event.key.code == sf::Keyboard::Left)
                            {
                                tankID -> setMoveDirection(TankMove::Left);
                            }
                            if(event.key.code == sf::Keyboard::Right)
                            {
                                tankID -> setMoveDirection(TankMove::Right);
                            }
                        }
                        if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                        {
                            tankID -> switchCursorVisibility(window);
                        }
                    }
                }
            }
        }
        else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
        {
            initialize(GameState::Menu);
        }
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
            world -> drawAll(window);
            if(gameState_ == GameState::Play)
            {
                world -> getCollisionAll();
                world -> stepAll(elapsed.asSeconds());
                for(const auto &object : world -> objects_)
                {
                    auto tank = dynamic_cast<Tank *>(object.get());
                    if(tank != nullptr)
                    {
                        tank -> update(elapsed.asSeconds(), window);
                    }
                }
                if(!taskCounter)
                {
                    for(const auto &object : world -> objects_)
                    {
                        auto tank = dynamic_cast<Tank *>(object.get());
                        if(tank != nullptr)
                        {
                            if(tank -> getPlayerHealth() <= 0)
                            {
                                winnerID_ = (Winner)((int)winnerID_ + ((int)Winner::Draw - (int)tank -> getPlayerID()));
                            }
                        }
                    }
                    if(winnerID_ == Winner::None)
                    {
                        for(const auto &object : world -> objects_)
                        {
                            auto tank = dynamic_cast<Tank *>(object.get());
                            if(tank != nullptr)
                            {
                                tank -> switchStatus(window);
                            }
                        }
                        taskCounter = 1;
                    }
                    else if(winnerID_ == Winner::Draw)
                    {
                        initialize(GameState::EndDraw);
                    }
                    else
                    {
                        initialize(GameState::EndWinner);
                    }
                }
                gameInterface_ -> drawGameTime(elapsed.asSeconds(), window);
            }
            else
            {
                if(gameState_ == GameState::EndWinner)
                {
                    if(fireworks_ -> changeAnimation(elapsed.asSeconds()) && fire_ -> changeAnimation(elapsed.asSeconds()))
                    {
                        fireworks_ -> draw(window);
                        fire_ -> draw(window);
                    }
                }
                gameInterface_ -> drawGameEnd(elapsed.asSeconds(), window);
            }
        }
        if(menu_ -> getGameSettings(GameSetting::FPS))
        {
            gameInterface_ -> drawFPS(elapsed.asSeconds(), window);
        }
    }
}

void Game::playMenuMusic(const bool &status)
{
    if(!status)
    {
        menuMusic_.stop();
    }
    else if(gameMusic_.getStatus() != sf::Music::Playing)
    {
        menuMusic_.play();
    }
}

void Game::playGameMusic(const bool &status)
{
    if(!status)
    {
        gameMusic_.stop();
    }
    else if(gameMusic_.getStatus() != sf::Music::Playing)
    {
        gameMusic_.play();
    }
}

void Game::playFireworksSound(const bool &status)
{
    if(!status)
    {
        fireworksSound_.stop();
    }
    else if(fireworksSound_.getStatus() != sf::Music::Playing)
    {
        fireworksSound_.play();
    }
}
