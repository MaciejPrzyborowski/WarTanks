#include "Menu.h"
#include "Application.h"

Menu::Menu() :
    isMouseActive_(false)
{
    font_.loadFromFile(GameFontSrc);
    backgroundTexture_.loadFromFile(MenuBackgroundTextureSrc);
    backgroundSprite_.setTexture(backgroundTexture_);
    backgroundSprite_.setScale((float)WindowWidth / backgroundTexture_.getSize().x, (float)WindowHeight / backgroundTexture_.getSize().y);

    selectSoundBuffer_.loadFromFile(SelectMenuSoundSrc);
    selectSound_.setBuffer(selectSoundBuffer_);
    selectSound_.setVolume(1);
    musicBuffer_.loadFromFile(MenuMusicSrc);
    music_.setBuffer(musicBuffer_);
    music_.setVolume(5);
    music_.setLoop(true);
}

void Menu::initialize(const MenuType &type, const bool &resetSelect)
{
    if(resetSelect)
    {
        selected_ = 0;
    }
    options_.clear();
    selectOptions_.clear();
    selectBackground_.clear();
    type_ = type;
    if(type != MenuType::None)
    {
        float CharakterSize;
        size_t StartPosition;
        vector<string> SettingNames;

        if(type == MenuType::Main)
        {
            CharakterSize = 0.1;
            StartPosition = 3;
            SettingNames = {"Graj", "Ustawienia", "Wyjscie"};
        }
        if(type == MenuType::Settings)
        {
            CharakterSize = 0.07;
            StartPosition = 2;
            SettingNames = {"Licznik FPS", "Muzyka w grze", "Muzyka w menu", "Dzwieki w menu", "Wstecz"};

            for(size_t i = 0, position = StartPosition; i < SettingNames.size() - 1; i++, position += 1)
            {
                sf::Text selectOptions;
                sf::RectangleShape selectBackground;

                selectBackground.setPosition(0, WindowHeight * position / 10);
                selectBackground.setFillColor(sf::Color(222, 222, 222, 50));
                selectBackground.setSize(sf::Vector2f(WindowWidth, WindowHeight * 0.09));
                selectBackground_.emplace_back(selectBackground);

                selectOptions.setFont(font_);
                selectOptions.setString(Application::getGame().getSettings((GameSetting)i) ? "TAK" : "NIE");
                selectOptions.setFillColor(i < sizeof(GameSetting) ? Application::getGame().getSettings((GameSetting)i) ? sf::Color::Green : sf::Color::Red : sf::Color::Transparent);
                selectOptions.setOutlineThickness(5);
                selectOptions.setOutlineColor(sf::Color::Black);
                selectOptions.setPosition(WindowWidth / 1.25, WindowHeight * position / 10);
                selectOptions.setCharacterSize(WindowHeight * CharakterSize);
                selectOptions_.emplace_back(selectOptions);
            }
        }
        for(size_t i = 0, position = StartPosition; i < SettingNames.size(); i++, position += 1)
        {
            sf::Text option;
            option.setFont(font_);
            option.setString(SettingNames[i]);
            option.setFillColor(sf::Color::White);
            option.setOutlineThickness(5);
            option.setOutlineColor(sf::Color::Black);
            option.setPosition(WindowWidth / 20, WindowHeight * position / 10);
            option.setCharacterSize(WindowHeight * CharakterSize);
            options_.emplace_back(option);
        }
        options_[selected_].setFillColor(sf::Color(150, 150, 150));
    }
}

void Menu::reset()
{
    isMouseActive_ = false;
    initialize(MenuType::Main);
    playMusic(Application::getGame().getSettings(GameSetting::MenuMusic));
}

void Menu::move(const MenuMove &direction)
{
    if(!((selected_ == 0 && (int)direction < 0) || (selected_ == options_.size() - 1 && (int)direction > 0)))
    {
        options_[selected_].setFillColor(sf::Color::White);
        selected_ += (int)direction;
        options_[selected_].setFillColor(sf::Color(150, 150, 150));
        selectSound_.play();
    }
}

void Menu::draw(sf::RenderTarget &window)
{
    window.draw(backgroundSprite_);
    if(options_.size() > 0)
    {
        for(auto &el: options_)
        {
            window.draw(el);
        }
    }
    if(selectOptions_.size() > 0)
    {
        for(auto &el: selectOptions_)
        {
            window.draw(el);
        }
        if(selectBackground_.size() > selected_)
        {
            window.draw(selectBackground_[selected_]);
        }
    }
}

bool Menu::getStatus()
{
    return !(type_ == MenuType::None);
}

bool Menu::getMouseStatus()
{
    return isMouseActive_;
}

void Menu::getChoice()
{
    if(type_ == MenuType::Main)
    {
        switch(selected_)
        {
            case 0:
            {
                initialize(MenuType::None);

                playMusic(false);
                Application::getGame().initialize(GameState::Play);
                break;
            }
            case 1:
            {
                initialize(MenuType::Settings);
                break;
            }
            case 2:
            {
                Application::quit();
                break;
            }
        }
    }
    else if(type_ == MenuType::Settings)
    {
        switch(selected_)
        {
            case 4:
            {
                initialize(MenuType::Main);
                break;
            }
            default:
            {
                Application::getGame().setSettings((GameSetting)selected_);
                initialize(MenuType::Settings, false);
                break;
            }
        }
    }
}

void Menu::getMouse(const sf::Vector2f &mousePosition)
{
    bool isMouseActive = false;
    if(options_[selected_].getGlobalBounds().contains(mousePosition))
    {
        isMouseActive = true;
    }
    else
    {
        for(size_t i = 0; i < options_.size(); i++)
        {
            if(options_[i].getGlobalBounds().contains(mousePosition))
            {
                if(selected_ != i)
                {
                    selectSound_.play();
                    options_[selected_].setFillColor(sf::Color::White);
                    selected_ = i;
                    options_[selected_].setFillColor(sf::Color(150, 150, 150));
                }
                isMouseActive = true;
            }
        }
    }
    isMouseActive_ = isMouseActive;
}

void Menu::playMusic(const bool &status)
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

void Menu::setSelectVolume(const float &volume)
{
    selectSound_.setVolume(volume);
}
