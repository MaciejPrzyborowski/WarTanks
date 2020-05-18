#include "Menu.h"

Menu::Menu()
{   
    Font.loadFromFile("game_font.ttf");
}

void Menu::MainMenu()
{
    vector<string> Names = {"Graj", "Ustawienia", "Wyjscie"};
    sf::Text Option;
    float pos = 0.2;
    for(size_t i = 0; i < Names.size(); i++)
    {
        pos += 0.1;
        Option.setFont(Font);
        Option.setString(Names[i]);
        Option.setFillColor(sf::Color::White);
        Option.setOutlineThickness(5);
        Option.setOutlineColor(sf::Color::Black);
        Option.setPosition(WindowWidth/20, WindowHeight * pos);
        Option.setCharacterSize(WindowHeight * 0.1);
        MainMenu_.emplace_back(Option);
    }
    MainMenu_[OptionSelected_].setFillColor(sf::Color(150,150,150));
}

void Menu::Settings()
{

    vector<string> Names = {"Licznik FPS", "Muzyka", "Dzwiek", "Sterowanie", "Wroc"};
    sf::Text Option;
    float pos = 0.1;


    sf::RectangleShape RectBg;
    for(size_t i = 0; i < Names.size(); i++)
    {
        pos += 0.1;
        Option.setFont(Font);
        Option.setString(Names[i]);
        Option.setFillColor(sf::Color::White);
        Option.setOutlineThickness(5);
        Option.setOutlineColor(sf::Color::Black);
        Option.setPosition(WindowWidth/20, WindowHeight * pos);
        Option.setCharacterSize(WindowHeight * 0.07);
        Settings_.emplace_back(Option);
        RectBg.setPosition(WindowWidth/25, WindowHeight * pos);
        RectBg.setFillColor(sf::Color(222,222,222,50));
        RectBg.setSize(sf::Vector2f(WindowWidth*0.9, WindowHeight*0.09));
        OptionBackground.emplace_back(RectBg);
    }
    Settings_[OptionSelected_].setFillColor(sf::Color(150,150,150));
}

void Menu::PlaySettings()
{
    vector<string> Names = {"Tryb offline", "Multiplayer", "Wroc"};
    sf::Text Option;
    float pos = 0.2;

    for(size_t i = 0; i < Names.size(); i++)
    {
        pos += 0.1;
        Option.setFont(Font);
        Option.setString(Names[i]);
        Option.setFillColor(sf::Color::White);
        Option.setOutlineThickness(5);
        Option.setOutlineColor(sf::Color::Black);
        Option.setPosition(WindowWidth/20, WindowHeight * pos);
        Option.setCharacterSize(WindowHeight * 0.1);
        PlaySettings_.emplace_back(Option);
    }
    PlaySettings_[OptionSelected_].setFillColor(sf::Color(150,150,150));
}

void Menu::ChoiceByMouse(sf::RenderWindow &Window, sf::Event &Event, sf::Sound &SelectSound)
{
    if(Event.type == sf::Event::MouseMoved)
    {
        IsMouseActive_ = true;
        sf::Vector2i MousePosition = sf::Mouse::getPosition(Window);
        if(MainMenuActive_)
        {
            for(size_t i = 0; i < MainMenu_.size(); i++)
            {
                MainMenu_[i].setFillColor(sf::Color::White);
                if(MainMenu_[i].getGlobalBounds().contains(Window.mapPixelToCoords(MousePosition)))
                {
                    if(OptionSelected_ != i) SelectSound.play();
                    OptionSelected_ = i;
                }
            }
            MainMenu_[OptionSelected_].setFillColor(sf::Color(150, 150, 150));
        }
        else if(SettingsActive_)
        {
            for(size_t i = 0; i < Settings_.size(); i++)
            {
                Settings_[i].setFillColor(sf::Color::White);
                if(Settings_[i].getGlobalBounds().contains(Window.mapPixelToCoords(MousePosition)))
                {
                    if(OptionSelected_ != i) SelectSound.play();
                    OptionSelected_ = i;
                }
            }
            Settings_[OptionSelected_].setFillColor(sf::Color(150, 150, 150));
        }
        else if(PlaySettingsActive_)
        {
            for(size_t i = 0; i < PlaySettings_.size(); i++)
            {
                PlaySettings_[i].setFillColor(sf::Color::White);
                if(PlaySettings_[i].getGlobalBounds().contains(Window.mapPixelToCoords(MousePosition)))
                {
                    if(OptionSelected_ != i) SelectSound.play();
                    OptionSelected_ = i;
                }
            }
            PlaySettings_[OptionSelected_].setFillColor(sf::Color(150, 150, 150));
        }
    }
    IsMouseActive_ = false;
}

void Menu::MoveUp(sf::Sound &SelectSound)
{
    if(MainMenuActive_ && OptionSelected_ != 0)
    {
        MainMenu_[OptionSelected_].setFillColor(sf::Color::White);
        OptionSelected_--;
        SelectSound.play();
        MainMenu_[OptionSelected_].setFillColor(sf::Color(150,150,150));
    }
    else if(SettingsActive_ && OptionSelected_ != 0)
    {
        Settings_[OptionSelected_].setFillColor(sf::Color::White);
        OptionSelected_--;
        SelectSound.play();
        Settings_[OptionSelected_].setFillColor(sf::Color(150,150,150));
    }
    else if(PlaySettingsActive_ && OptionSelected_ != 0)
    {
        PlaySettings_[OptionSelected_].setFillColor(sf::Color::White);
        OptionSelected_--;
        SelectSound.play();
        PlaySettings_[OptionSelected_].setFillColor(sf::Color(150,150,150));
    }
}

void Menu::MoveDown(sf::Sound &SelectSound)
{
    if(PlaySettingsActive_ && OptionSelected_ != PlaySettings_.size() - 1)
    {
        PlaySettings_[OptionSelected_].setFillColor(sf::Color::White);
        OptionSelected_++;
        SelectSound.play();
        PlaySettings_[OptionSelected_].setFillColor(sf::Color(150,150,150));
    }
    else if(MainMenuActive_ && OptionSelected_ != MainMenu_.size() - 1)
    {
        MainMenu_[OptionSelected_].setFillColor(sf::Color::White);
        OptionSelected_++;
        SelectSound.play();
        MainMenu_[OptionSelected_].setFillColor(sf::Color(150,150,150));
    }
    else if(SettingsActive_ && OptionSelected_ != Settings_.size() - 1)
    {
        Settings_[OptionSelected_].setFillColor(sf::Color::White);
        OptionSelected_++;
        SelectSound.play();
        Settings_[OptionSelected_].setFillColor(sf::Color(150,150,150));
    }
}

void Menu::ShowMenu(sf::RenderWindow &Window)
{
    for(auto &el: MainMenu_)
        Window.draw(el);
}

void Menu::ShowSettings(sf::RenderWindow &Window)
{
    Window.draw(OptionBackground[OptionSelected_]);
    for(auto &el: Settings_)
        Window.draw(el);
}

void Menu::ShowPlaySettings(sf::RenderWindow &Window)
{
    for(auto &el: PlaySettings_)
        Window.draw(el);
}



