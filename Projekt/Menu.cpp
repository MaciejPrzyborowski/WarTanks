#include "Menu.h"
#include "Application.h"

Menu::Menu() :
    isMouseActive_(false),
    gameSettings_{false, true, true, true}
{
    font_.loadFromFile(GameFontSrc);
    menuSelectSoundBuffer_.loadFromFile(SelectMenuSoundSrc);
    menuSelectSound_.setBuffer(menuSelectSoundBuffer_);
    menuSelectSound_.setVolume(1);
}

void Menu::reset(const bool &settings)
{
    if(settings)
    {
        gameSettings_[(int)GameSetting::FPS] = false;
        gameSettings_[(int)GameSetting::GameMusic] = true;
        gameSettings_[(int)GameSetting::MenuMusic] = true;
        gameSettings_[(int)GameSetting::SoundMusic] = true;
    }
    isMouseActive_ = false;
    setMenu(MenuType::Main);
}

void Menu::move(const MenuMove &direction)
{
    if(!((menuSelected_ == 0 && (int)direction < 0) || (menuSelected_ == menuOptions_.size() - 1 && (int)direction > 0)))
    {
        menuOptions_[menuSelected_].setFillColor(sf::Color::White);
        menuSelected_ += (int)direction;
        menuOptions_[menuSelected_].setFillColor(sf::Color(150, 150, 150));
        menuSelectSound_.play();
    }
}

void Menu::draw(sf::RenderTarget &window)
{
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

bool Menu::getMenuStatus()
{
    return !(menuType_ == MenuType::None);
}

bool Menu::getGameSettings(const GameSetting &gameSetting)
{
    return gameSettings_[int(gameSetting)];
}

void Menu::setMenu(const MenuType &menuType)
{
    menuSelected_ = 0;
    menuOptions_.clear();
    menuSelectOptions_.clear();
    menuSelectBackground_.clear();
    menuType_ = menuType;
    if(menuType != MenuType::None)
    {
        float CharakterSize;
        size_t StartPosition;
        vector<string> SettingNames;

        if(menuType == MenuType::Main)
        {
            CharakterSize = 0.1;
            StartPosition = 3;
            SettingNames = {"Graj", "Ustawienia", "Wyjscie"};
        }
        if(menuType == MenuType::Settings)
        {
            CharakterSize = 0.07;
            StartPosition = 2;
            SettingNames = {"Licznik FPS", "Muzyka w grze", "Muzyka w menu", "Dzwieki w menu", "Wstecz"};

            for(size_t i = 0, position = StartPosition; i < SettingNames.size() - 1; i++, position += 1)
            {
                sf::Text menuSelectOptions;
                sf::RectangleShape menuSelectBackground;

                menuSelectBackground.setPosition(0, WindowHeight * position / 10);
                menuSelectBackground.setFillColor(sf::Color(222, 222, 222, 50));
                menuSelectBackground.setSize(sf::Vector2f(WindowWidth, WindowHeight * 0.09));
                menuSelectBackground_.emplace_back(menuSelectBackground);

                menuSelectOptions.setFont(font_);
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

            menuOption.setFont(font_);
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

void Menu::getMenuChoice()
{
    if(menuType_ == MenuType::Main)
    {
        switch(menuSelected_)
        {
            case 0:
            {
                setMenu(MenuType::None);
                break;
            }
            case 1:
            {
                setMenu(MenuType::Settings);
                break;
            }
            case 2:
            {
                Application::quit();
                break;
            }
        }
    }
    else if(menuType_ == MenuType::Settings)
    {
        switch(menuSelected_)
        {
            case 4:
            {
                setMenu(MenuType::Main);
                break;
            }
            default:
            {
                setSettings((GameSetting)menuSelected_);
                break;
            }
        }
    }
}

bool Menu::getMenuMouse(const sf::Vector2f &mousePosition)
{
    if(menuOptions_[menuSelected_].getGlobalBounds().contains(mousePosition))
    {
        return true;
    }
    else
    {
        bool isMouseActive = false;
        for(size_t i = 0; i < menuOptions_.size(); i++)
        {
            if(menuOptions_[i].getGlobalBounds().contains(mousePosition))
            {
                if(menuSelected_ != i)
                {
                    menuSelectSound_.play();
                    menuOptions_[menuSelected_].setFillColor(sf::Color::White);
                    menuSelected_ = i;
                    menuOptions_[menuSelected_].setFillColor(sf::Color(150, 150, 150));
                }
                isMouseActive = true;
            }
        }
        return isMouseActive;
    }
}

void Menu::setSettings(const GameSetting &gameSetting)
{
    gameSettings_[(int)gameSetting] = !gameSettings_[(int)gameSetting];
    if(gameSettings_[(int)gameSetting])
    {
        if((int)gameSetting == 3)
        {
            menuSelectSound_.setVolume(1);
        }
        menuSelectOptions_[(int)gameSetting].setString("TAK");
        menuSelectOptions_[(int)gameSetting].setFillColor(sf::Color::Green);
    }
    else
    {
        if((int)gameSetting == 3)
        {
            menuSelectSound_.setVolume(0);
        }
        menuSelectOptions_[(int)gameSetting].setString("NIE");
        menuSelectOptions_[(int)gameSetting].setFillColor(sf::Color::Red);
    }
}

bool Menu::isMouseActive()
{
    return isMouseActive_;
}

void Menu::setMouseActive(sf::RenderWindow &window)
{
    isMouseActive_ = getMenuMouse(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
