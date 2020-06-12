#include "Menu.h"

Menu::Menu() :
    isMouseActive_(false),
    gameSettings_{false, true, true, true}
{
    Font.loadFromFile("game_font.ttf");
    MenuSelectSoundBuffer.loadFromFile(SelectMenuSoundSrc);
    MenuSelectSound.setBuffer(MenuSelectSoundBuffer);
    MenuSelectSound.setVolume(1);
    MenuMusicBuffer.loadFromFile(MenuMusicSrc);
    MenuMusic.setBuffer(MenuMusicBuffer);
    MenuMusic.setVolume(5);
    MenuMusic.play();
    BackgroundTexture.loadFromFile(MenuBackgroundTextureSrc);
    BackgroundSprite.setTexture(BackgroundTexture);
    BackgroundSprite.setScale((float)WindowWidth / BackgroundTexture.getSize().x, (float)WindowHeight / BackgroundTexture.getSize().y);
    this->setMenu(MenuMain);
}

/**
 * Zmienia aktualny wybór w menu
 */
void Menu::move(int direction)
{
    if(!((menuSelected_ == 0 && direction < 0) || (menuSelected_ == menuOptions_.size() - 1 && direction > 0)))
    {
        menuOptions_[menuSelected_].setFillColor(sf::Color::White);
        menuSelected_ += direction;
        menuOptions_[menuSelected_].setFillColor(sf::Color(150, 150, 150));
        MenuSelectSound.play();
    }
}

/**
 * Obsługuje zdarzenia wykonane przez gracza
 */
void Menu::passEvent(sf::Event &event, sf::RenderWindow &window)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Up)
        {
            move(-1);
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            move(1);
        }
    }
    if((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) ||
            (isMouseActive_ && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased))
    {
        if(menuType_ == MenuMain)
        {
            switch(menuSelected_)
            {
                case 0:
                {
                    setMenu(MenuPlay);
                    break;
                }
                case 1:
                {
                    setMenu(MenuSettings);
                    break;
                }
                case 2:
                {
                    window.close();
                }
            }
        }
        else if(menuType_ == MenuPlay)
        {
            switch(menuSelected_)
            {
                case 0:
                {
                    setMenu(MenuNone);
                    MenuMusic.stop();
                    break;
                }
                case 1:
                {
                    setMenu(MenuNone);
                    MenuMusic.stop();
                    break;
                }
                case 2:
                {
                    setMenu(MenuMain);
                }
            }
        }
        else if(menuType_ == MenuSettings)
        {
            switch(menuSelected_)
            {
                case 4:
                {
                    setMenu(MenuMain);
                    break;
                }
                default:
                {
                    setClientSetting(menuSelected_);
                    break;
                }
            }
        }
    }
    if(event.type == sf::Event::MouseMoved)
    {
        bool isActive = false;
        sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
        for(size_t i = 0; i < menuOptions_.size(); i++)
        {
            if(menuOptions_[i].getGlobalBounds().contains(window.mapPixelToCoords(MousePosition)))
            {
                if(menuSelected_ != i)
                {
                    MenuSelectSound.play();
                    menuOptions_[menuSelected_].setFillColor(sf::Color::White);
                    menuSelected_ = i;
                    menuOptions_[menuSelected_].setFillColor(sf::Color(150, 150, 150));
                }
                isActive = true;
            }
        }
        isMouseActive_ = isActive;
    }
}

/**
 * Wyświetla menu
 */
void Menu::draw(sf::RenderTarget &window)
{
    window.draw(BackgroundSprite);
    if(menuOptions_.size() > 0)
    {
        for(auto &el: menuOptions_)
        {
            window.draw(el);
        }
    }
    if(menuSelectOptions_.size() > 0)
    {
        for(auto &el: menuSelectOptions_)
        {
            window.draw(el);
        }
        if(menuSelectBackground_.size() > menuSelected_)
        {
            window.draw(menuSelectBackground_[menuSelected_]);
        }
    }
}

/**
 * Zwraca status menu
 */
bool Menu::getStatus()
{
    return !(menuType_ == MenuNone);
}

/**
 * Zmienia ustawienia gracza
 */
void Menu::setClientSetting(int setting)
{
    gameSettings_[setting] = !gameSettings_[setting];
    if(gameSettings_[setting])
    {
        if(setting == 2)
        {
            MenuMusic.play();
        }
        else if(setting == 3)
        {
            MenuSelectSound.setVolume(1);
        }
        menuSelectOptions_[setting].setString("TAK");
        menuSelectOptions_[setting].setFillColor(sf::Color::Green);
    }
    else
    {
        if(setting == 2)
        {
            MenuMusic.stop();
        }
        else if(setting == 3)
        {
            MenuSelectSound.setVolume(0);
        }
        menuSelectOptions_[setting].setString("NIE");
        menuSelectOptions_[setting].setFillColor(sf::Color::Red);
    }
}

/**
 * Aktualizuje dane menu
 */
void Menu::setMenu(MenuType type)
{
    menuSelected_ = 0;
    menuOptions_.clear();
    menuSelectOptions_.clear();
    menuSelectBackground_.clear();
    menuType_ = type;
    if(type != MenuNone)
    {
        float CharakterSize;
        size_t StartPosition;
        vector<string> SettingNames;

        if(type == MenuMain)
        {
            CharakterSize = 0.1;
            StartPosition = 3;
            SettingNames = {"Graj", "Ustawienia", "Wyjscie"};
        }
        if(type == MenuPlay)
        {
            CharakterSize = 0.1;
            StartPosition = 3;
            SettingNames = {"Tryb Offline", "Tryb MultiPlayer", "Wroc"};
        }
        if(type == MenuSettings)
        {
            CharakterSize = 0.07;
            StartPosition = 2;
            SettingNames = {"Licznik FPS", "Muzyka w grze", "Muzyka w menu", "Dodatkowe dzwieki", "Wroc"};

            for(size_t i = 0, position = StartPosition; i < SettingNames.size() - 1; i++, position += 1)
            {
                sf::Text menuSelectOptions;
                sf::RectangleShape menuSelectBackground;

                menuSelectBackground.setPosition(0, WindowHeight * position / 10);
                menuSelectBackground.setFillColor(sf::Color(222, 222, 222, 50));
                menuSelectBackground.setSize(sf::Vector2f(WindowWidth, WindowHeight * 0.09));
                menuSelectBackground_.emplace_back(menuSelectBackground);

                menuSelectOptions.setFont(Font);
                menuSelectOptions.setString(gameSettings_[i] ? "TAK" : "NIE");
                menuSelectOptions.setFillColor(i < sizeof(gameSettings_) ? gameSettings_[i] ? sf::Color::Green : sf::Color::Red : sf::Color::Transparent);
                menuSelectOptions.setOutlineThickness(5);
                menuSelectOptions.setOutlineColor(sf::Color::Black);
                menuSelectOptions.setPosition(WindowWidth / 1.25, WindowHeight * position / 10);
                menuSelectOptions.setCharacterSize(WindowHeight * CharakterSize);
                menuSelectOptions_.emplace_back(menuSelectOptions);
            }
        }
        for(size_t i = 0, position = StartPosition; i < SettingNames.size(); i++, position += 1)
        {
            sf::Text menuOption;

            menuOption.setFont(Font);
            menuOption.setString(SettingNames[i]);
            menuOption.setFillColor(sf::Color::White);
            menuOption.setOutlineThickness(5);
            menuOption.setOutlineColor(sf::Color::Black);
            menuOption.setPosition(WindowWidth / 20, WindowHeight * position / 10);
            menuOption.setCharacterSize(WindowHeight * CharakterSize);
            menuOptions_.emplace_back(menuOption);
        }
        menuOptions_[menuSelected_].setFillColor(sf::Color(150, 150, 150));
    }
}
