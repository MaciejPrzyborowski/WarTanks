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
    menu_ = make_unique<Menu>();
    land_ = make_unique<Land>(4, 0.2);
    GameInterface_ = make_unique<Interface>();
    player1_ = make_unique<Tank>(1, TankTextureSrc1, *land_);
    player2_ = make_unique<Tank>(2, TankTextureSrc2, *land_);
    player1_ -> enemy = player2_.get();
    player2_ -> enemy = player1_.get();
    initialize(GameMenu);
    update();
}

void Game::initialize(GameState gameState)
{
    gameState_ = gameState;
    if(gameState == GameMenu)
    {
        menu_ -> reset(false);
        playGameMusic(false);
        playMenuMusic(menu_->getGameSettings(2));
        fireworksSound_.stop();
    }
    else if(gameState == GamePlay)
    {
        land_->generate();

        player1_ -> reset();
        player2_ -> reset();
        GameInterface_->reset();
        playGameMusic(menu_->getGameSettings(1));
        playMenuMusic(false);
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
        if(menu_->getMenuStatus())
        {
            menu_->passEvent(Event, *window_);
            playMenuMusic(menu_->getGameSettings(2));
        }
        else
        {
            initialize(GamePlay);
        }
    }
    else if(gameState_ == GamePlay)
    {
        player1_->passEvent(Event, *window_);
        player2_->passEvent(Event, *window_);
    }
    else if(Event.type == sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Return)
    {
        initialize(GameMenu);
    }
}

void Game::updateAll(sf::Time elapsed)
{
    if(window_ -> isOpen())
    {
        window_ -> clear();
        if(gameState_ == GameMenu)
        {
            if(menu_->getMenuStatus())
            {
                window_ -> draw(menuBackgroundSprite_);
                menu_->draw(*window_);
            }
            else
            {
                initialize(GamePlay);
            }
        }
        else
        {
            window_ -> draw(gameBackgroundSprite_);
            land_ -> draw(*window_);
            player1_ -> draw(*window_);
            player2_ -> draw(*window_);
            int playerHealth[2] = {player1_ -> returnHp(), player2_ -> returnHp()};
            if(gameState_ == GamePlay)
            {
                if(playerHealth[0] > 0 && playerHealth[1] > 0)
                {
                    land_ -> step(elapsed.asSeconds());
                    player1_ -> update(elapsed.asSeconds(), *window_);
                    player2_ -> update(elapsed.asSeconds(), *window_);
                    if(player1_ -> getStatus() == 2 || player2_ -> getStatus() == 2)
                    {
                        player1_ -> switchStatus(*window_);
                        player2_ -> switchStatus(*window_);
                    }
                    GameInterface_ -> drawGameTime(elapsed.asSeconds(), *window_);
                }
                else if(playerHealth[0] > 0 || playerHealth[1] > 0)
                {
                    initialize(GameEndWinner);
                    vector<sf::Vector2f> position = GameInterface_ -> checkWinner(playerHealth, player1_->returnPosition(), player2_->returnPosition());
                    winner_ = position[0];
                    loser_ = position[1];
                }
                else
                {
                    initialize(GameEndDraw);
                }
            }
            else
            {
                GameInterface_ -> drawGameEnd(elapsed.asSeconds(), *window_);
                if(gameState_ == GameEndWinner)
                {
                    playGameMusic(false);
                    playFireworksSound();
                    fireworks_ -> draw(elapsed.asSeconds(), winner_, *window_);
                    fire_ -> draw(elapsed.asSeconds(), loser_, *window_);
                }
            }
        }
        if(menu_->getGameSettings(0))
        {
            GameInterface_ -> drawFPS(elapsed.asSeconds(), *window_);
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

/**
 * Włącza muzykę w menu jeżeli opcja ta jest włączona w ustawieniach
 *
 * @param isMenuMusicOn - sprawdza czy muzyka w menu jest włączona
 */
void Game::playMenuMusic(bool isMenuMusicOn)
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

/**
 * Włącza muzykę w grze jeżeli opcja ta jest włączona w ustawieniach
 *
 * @param isGameMusicOn - sprawdza czy muzyka w grze jest włączona
 */
void Game::playGameMusic(const bool isGameMusicOn)
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

/**
 * Włącza dźwięk fajerwerków na koniec gry
 */
void Game::playFireworksSound()
{
    if(fireworksSound_.getStatus() != sf::Music::Playing)
    {
        fireworksSound_.play();
    }
}
