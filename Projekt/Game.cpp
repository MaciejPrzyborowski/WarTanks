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

    gameBuffer_.loadFromFile(GameMusicSrc);
    gameMusic_.setBuffer(gameBuffer_);
    gameMusic_.setVolume(30);

}

void Game::run()
{
    menu_ = make_unique<Menu>();
    land_ = make_unique<Land>(4, 0.2);
    GameInterface_ = make_unique<Interface>();
    player1_ = make_unique<Tank>(1, TankTextureSrc1, *land_);
    player2_ = make_unique<Tank>(2, TankTextureSrc2, *land_);
    player1_->enemy = player2_.get();
    player2_->enemy = player1_.get();

    initialize(GameMenu);
    update();
}

void Game::initialize(GameState gameState)
{
    gameState_ = gameState;
    if(gameState == GameMenu)
    {
        menu_->reset(false);
        playGameMusic(false);
    }
    else if(gameState == GamePlay)
    {
        land_->generate();

        player1_ -> reset();
        player2_ -> reset();
        GameInterface_->reset();
        playGameMusic(menu_->getGameSettings(1));

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
                    window_ -> draw(GameInterface_ -> gameTime(elapsed.asSeconds()));
                }
                else if(playerHealth[0] > 0 || playerHealth[1] > 0)
                {
                    initialize(GameEndWinner);
                    loser_ = sf::Vector2f(GameInterface_->loser(playerHealth[0], player1_->returnPosition(), player2_->returnPosition()).x - 50, GameInterface_->loser(playerHealth[0], player1_->returnPosition(), player2_->returnPosition()).y - 90);
                    winner_ = sf::Vector2f(GameInterface_->winner(playerHealth[0], player1_->returnPosition(), player2_->returnPosition()).x - 50, GameInterface_->winner(playerHealth[0], player1_->returnPosition(), player2_->returnPosition()).y - 120);
                }
                else
                {
                    initialize(GameEndDraw);
                }
            }
            else
            {
                window_->draw(GameInterface_ -> gameEnd(playerHealth[0], playerHealth[1]));
                if(gameState_ == GameEndWinner)
                {
                    fireworks_ -> draw(elapsed.asSeconds(), winner_, *window_);
                    fire_ -> draw(elapsed.asSeconds(), loser_, *window_);
                }
                GameInterface_ -> backToMenuText(*window_, elapsed.asSeconds());
            }
        }
        if(menu_->getGameSettings(0))
        {
            window_->draw(GameInterface_ -> showFps(elapsed.asSeconds()));
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
 * Włącza muzyke w grze jeżeli opcja ta jest włączona w ustawieniach
 *
 * @param isMusicOn - sprawdza czy muzyka w grze jest włączona
 */
void Game::playGameMusic(const bool isMusicOn)
{
    if(isMusicOn && gameMusic_.getStatus() != sf::Music::Playing)
    {
        gameMusic_.play();
    }
    else if(!isMusicOn)
    {
        gameMusic_.stop();
    }
}
