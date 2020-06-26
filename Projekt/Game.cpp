#include "Game.h"

Game::Game() :
    taskCounter(0),
    gameSettings_{false, true, true, true},
    winnerID_(WinnerType::None),
    fireworks_(nullptr),
    fire_(nullptr),
    gameInterface_(nullptr),
    menu_(nullptr),
    world(nullptr),
    land(nullptr)
{
    backgroundTexture_.loadFromFile(GameBackgroundTextureSrc);
    backgroundSprite_.setTexture(backgroundTexture_);
    backgroundSprite_.setScale((float)WindowWidth/backgroundTexture_.getSize().x, (float)WindowHeight/backgroundTexture_.getSize().y);

    musicBuffer_.loadFromFile(GameMusicSrc);
    music_.setBuffer(musicBuffer_);
    music_.setVolume(30);
    music_.setLoop(true);
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
        winnerID_ = WinnerType::None;
        menu_ -> reset();

        playGameMusic(false);
        playFireworksSound(false);
    }
    else if(gameState == GameState::Play)
    {
        winnerID_ = WinnerType::None;
        world -> resetAll();
        gameInterface_ -> reset();

        playFireworksSound(false);
        playGameMusic(getSettings(GameSetting::GameMusic));
    }
    else if(gameState == GameState::EndWinner)
    {
        playGameMusic(false);
        playFireworksSound(true);

        fireworks_ = make_unique<Animation>(FireworksEndGameAnimationSrc, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
        fire_ = make_unique<Animation>(FireEndGameAnimationSrc, sf::IntRect(0, 0, 100, 100), 100, 50, true, 1.0);
        for(const auto &object : *(world -> getObjects()))
        {
            auto tank = dynamic_cast<Tank *>(object.get());
            if(tank != nullptr)
            {
                if(winnerID_ == (WinnerType)tank -> getPlayerID())
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
            if(menu_ -> getStatus())
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
                    menu_ -> getMouse(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                }
                if((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) ||
                        (menu_ -> getMouseStatus() && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased))
                {
                    menu_ -> getChoice();
                }
            }
        }
        else if(gameState_ == GameState::Play)
        {
            for(auto &object : *(world -> getObjects()))
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
            if(menu_ -> getStatus())
            {
                menu_ -> draw(window);
            }
        }
        else
        {
            window.draw(backgroundSprite_);
            world -> drawAll(window);
            if(gameState_ == GameState::Play)
            {
                world -> getCollisionAll();
                world -> stepAll(elapsed.asSeconds());
                for(const auto &object : *(world -> getObjects()))
                {
                    auto tank = dynamic_cast<Tank *>(object.get());
                    if(tank != nullptr)
                    {
                        tank -> update(elapsed.asSeconds(), window);
                    }
                }
                if(!taskCounter)
                {
                    for(const auto &object : *(world -> getObjects()))
                    {
                        auto tank = dynamic_cast<Tank *>(object.get());
                        if(tank != nullptr)
                        {
                            if(tank -> getPlayerHealth() <= 0)
                            {
                                winnerID_ = (WinnerType)((int)winnerID_ + ((int)WinnerType::Draw - (int)tank -> getPlayerID()));
                            }
                        }
                    }
                    if(winnerID_ == WinnerType::None)
                    {
                        for(const auto &object : *(world -> getObjects()))
                        {
                            auto tank = dynamic_cast<Tank *>(object.get());
                            if(tank != nullptr)
                            {
                                tank -> switchStatus(window);
                            }
                        }
                        taskCounter = 1;
                    }
                    else if(winnerID_ == WinnerType::Draw)
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
        if(getSettings(GameSetting::FPS))
        {
            gameInterface_ -> drawFPS(elapsed.asSeconds(), window);
        }
    }
}

bool Game::getSettings(const GameSetting &gameSetting)
{
    return gameSettings_[int(gameSetting)];
}

void Game::setSettings(const GameSetting &gameSetting)
{
    gameSettings_[(int)gameSetting] = !gameSettings_[(int)gameSetting];
    if(gameSettings_[(int)gameSetting])
    {
        if(gameSetting == GameSetting::MenuMusic)
        {
            menu_ -> playMusic(true);
        }
        else if(gameSetting == GameSetting::SoundMusic)
        {
            menu_ -> setSelectVolume(1);
        }
    }
    else if(gameSetting == GameSetting::MenuMusic)
    {
        menu_ -> playMusic(false);
    }
    else if(gameSetting == GameSetting::SoundMusic)
    {
        menu_ -> setSelectVolume(0);
    }
}

void Game::playGameMusic(const bool &status)
{
    if(!status)
    {
        music_.stop();
    }
    else if(music_.getStatus() != sf::Music::Playing)
    {
        music_.play();
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
