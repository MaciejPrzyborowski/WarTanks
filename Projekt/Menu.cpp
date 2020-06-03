#include "Menu.h"

Menu::Menu()
{
    Font.loadFromFile("game_font.ttf");
    Buffer.loadFromFile("menu_music.wav");

    BackgroundMusic.setBuffer(Buffer);
    BackgroundMusic.setVolume(1);

    Buffer2.loadFromFile("select_sound.wav");
    SelectSound.setBuffer(Buffer2);
    SelectSound.setVolume(1);

    MenuBackground.loadFromFile("menu_background.jpg");
    Sprite.setTexture(MenuBackground);

    sf::Vector2u TextureSize = MenuBackground.getSize();
    float scaleX = (float)WindowWidth/TextureSize.x;
    float scaleY = (float)WindowHeight/TextureSize.y;
    Sprite.setScale(scaleX, scaleY);

    if(BackgroundMusic.getStatus() != sf::SoundStream::Playing)
        BackgroundMusic.play();

    this->MainMenu();
    this->Settings();
    this->PlaySettings();
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
    OptionSelected_ = 0;

    MainMenu_[OptionSelected_].setFillColor(sf::Color(150,150,150));
}

void Menu::Settings()
{
    vector<string> Names = {"Licznik FPS", "Muzyka", "Dzwiek", "Sterowanie", "Wroc"};
    vector<string> SetNames = {"WYLACZONY", "WLACZONA", "WLACZONY", "WSAD", ""};
    sf::Text Option;
    sf::Text Set;

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
        SettingsMenu_.emplace_back(Option);

        RectBg.setPosition(0, WindowHeight * pos);
        RectBg.setFillColor(sf::Color(222,222,222,50));
        RectBg.setSize(sf::Vector2f(WindowWidth, WindowHeight*0.09));
        OptionBackground.emplace_back(RectBg);
    }

    pos = 0.1;

    for(size_t i = 0; i < SetNames.size(); i++)
    {
        pos += 0.1;
        Set.setFont(Font);
        Set.setString(SetNames[i]);
        Set.setFillColor(sf::Color::White);
        Set.setOutlineThickness(5);
        Set.setOutlineColor(sf::Color::Black);
        Set.setPosition(WindowWidth/1.5, WindowHeight * pos);
        Set.setCharacterSize(WindowHeight * 0.07);
        Settings_.emplace_back(Set);
    }

    if(!FPS) Settings_[0].setFillColor(sf::Color::Red); else Settings_[0].setFillColor(sf::Color::Green);
    if(GMusic) Settings_[1].setFillColor(sf::Color::Green); else Settings_[1].setFillColor(sf::Color::Red);
    if(GSound) Settings_[2].setFillColor(sf::Color::Green); else Settings_[2].setFillColor(sf::Color::Red);

    OptionBackground[OptionBackground.size()-1].setFillColor(sf::Color::Transparent);
    OptionSelected_ = 0;

    SettingsMenu_[OptionSelected_].setFillColor(sf::Color(150,150,150));
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
        PlaySettingsMenu_.emplace_back(Option);
    }
    OptionSelected_ = 0;
    PlaySettingsMenu_[OptionSelected_].setFillColor(sf::Color(150,150,150));
}

void Menu::ChoiceByMouse(sf::RenderWindow &Window, sf::Event &Event)
{
    if(Event.type == sf::Event::MouseMoved)
    {
        IsMouseActive_ = true;
        sf::Vector2i MousePosition = sf::Mouse::getPosition(Window);
        if(MainMenuActive_)
            this->SelectMenu(MainMenu_, MousePosition, Window);
        else if(SettingsActive_)
            this->SelectMenu(SettingsMenu_, MousePosition, Window);
        else if(PlaySettingsActive_)
            this->SelectMenu(PlaySettingsMenu_, MousePosition, Window);
    }
    IsMouseActive_ = false;
}

void Menu::FUp(vector<sf::Text> &Menu)
{
    Menu[OptionSelected_].setFillColor(sf::Color::White);
    OptionSelected_--;
    SelectSound.play();
    Menu[OptionSelected_].setFillColor(sf::Color(150,150,150));
}

void Menu::FDown(vector<sf::Text> &Menu)
{
    Menu[OptionSelected_].setFillColor(sf::Color::White);
    OptionSelected_++;
    SelectSound.play();
    Menu[OptionSelected_].setFillColor(sf::Color(150,150,150));
}

void Menu::MoveUp()
{
    if(MainMenuActive_ && OptionSelected_ != 0)
        this->FUp(MainMenu_);
    else if(SettingsActive_ && OptionSelected_ != 0)
        this->FUp(SettingsMenu_);
    else if(PlaySettingsActive_ && OptionSelected_ != 0)
        this->FUp(PlaySettingsMenu_);
}

void Menu::MoveDown()
{
    if(MainMenuActive_ && OptionSelected_ != MainMenu_.size() - 1)
        FDown(MainMenu_);
    else if(PlaySettingsActive_ && OptionSelected_ != PlaySettingsMenu_.size() - 1)
        FDown(PlaySettingsMenu_);
    else if(SettingsActive_ && OptionSelected_ != SettingsMenu_.size() - 1)
        FDown(SettingsMenu_);
}

void Menu::SetFPS()
{
    if(FPS)
    {
        Settings_[0].setString("Wylaczony");
        Settings_[0].setFillColor(sf::Color::Red);
        std::cout << "Licznik FPS wylaczony" << std::endl;
        FPS = false;
    }
    else
    {
        Settings_[0].setString("Wlaczony");
        Settings_[0].setFillColor(sf::Color::Green);
        std::cout << "Licznik FPS wlaczony" << std::endl;
        FPS = true;
    }
}

void Menu::ShowFPS(sf::Clock Clock, sf::RenderWindow &Window)
{
    int framerate = 1 / Clock.getElapsedTime().asSeconds();
    sf::Text show;
    show.setPosition(0,0);
    show.setFont(Font);
    show.setFillColor(sf::Color::White);
    show.setCharacterSize(WindowHeight*0.05);
    show.setString(to_string(framerate) + "FPS");
    if(FPS)
        Window.draw(show);
}

void Menu::GameMusic()
{
    if(!GMusic)
    {
        Settings_[1].setString("Wlaczona");
        Settings_[1].setFillColor(sf::Color::Green);
        std::cout << "Muzyka wlaczona" << std::endl;
        GMusic = true;
    }
    else
    {
        Settings_[1].setString("Wylaczona");
        Settings_[1].setFillColor(sf::Color::Red);
        std::cout << "Muzyka wylaczona" << std::endl;
        GMusic = false;
    }

    if(GMusic && BackgroundMusic.getStatus() != sf::SoundStream::Playing)
        BackgroundMusic.play();
    else if (!GMusic)
        BackgroundMusic.stop();
}

void Menu::GameSound()
{
    if(!GSound)
    {
        Settings_[2].setString("Wlaczony");
        Settings_[2].setFillColor(sf::Color::Green);
        std::cout << "Dzwiek wlaczony" << std::endl;
        SelectSound.setVolume(1);
        GSound = true;
    }
    else
    {
        Settings_[2].setString("Wylaczony");
        Settings_[2].setFillColor(sf::Color::Red);
        std::cout << "Dzwiek wylaczony" << std::endl;
        SelectSound.setVolume(0);
        GSound = false;
    }
}

void Menu::GameControl()
{
    if(!ArrowsControl)
    {
        Settings_[3].setString("STRZALKI");
        std::cout << "Sterowanie strzalkami wlaczone" << std::endl;
        ArrowsControl = true;
    }
    else
    {
        Settings_[3].setString("WSAD");
        std::cout << "Sterowanie WSAD wlaczone" << std::endl;
        ArrowsControl = false;
    }
}

void Menu::SelectMenu(vector<sf::Text> &Menu, sf::Vector2i MousePosition, sf::RenderWindow &Window)
{
    for(size_t i = 0; i < Menu.size(); i++)
    {
        Menu[i].setFillColor(sf::Color::White);
        if(Menu[i].getGlobalBounds().contains(Window.mapPixelToCoords(MousePosition)))
        {
            if(OptionSelected_ != i) SelectSound.play();
            OptionSelected_ = i;
        }
    }
    Menu[OptionSelected_].setFillColor(sf::Color(150, 150, 150));
}

void Menu::ShowSwitch(sf::Event &Event, sf::RenderWindow &Window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->MoveUp();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->MoveDown();
    }
    if(((Event.type == sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Return) || (Event.mouseButton.button == sf::Mouse::Left && Event.type == sf::Event::MouseButtonReleased)))
    {
        if(MainMenuActive_)
        {
            switch(OptionSelected_)
            {
            case 0:
                this->PlaySettingsActive();
                break;
            case 1:
                this->SettingsActive();
                break;
            case 2:
                Window.close();
                break;
            }
        }
        else if(PlaySettingsActive_)
        {
            switch(OptionSelected_)
            {
            case 0:
                this->HideMenu();
                BackgroundMusic.stop();
                std::cout << "Tryb offline" << endl;
                break;
            case 1:
                this->HideMenu();
                BackgroundMusic.stop();
                std::cout << "Tryb online" << endl;
                break;
            case 2:
                this->MainMenuActive();
                break;
            }
        }
        else if(SettingsActive_)
        {
            switch(OptionSelected_)
            {
            case 0:
                this->SetFPS();
                break;
            case 1:
                this->GameMusic();
                break;
            case 2:
                this->GameSound();
                break;
            case 3:
                this->GameControl();
                break;
            case 4:
                this->MainMenuActive();
                break;
            }
        }
    }
    this->ChoiceByMouse(Window, Event);
}

void Menu::ShowMenu(sf::RenderWindow &Window, sf::Clock Clock)
{
    Window.draw(Sprite);
    if(MainMenuActive_)
    {
        for(auto &el: MainMenu_)
            Window.draw(el);
    }
    else if(SettingsActive_)
    {
        Window.draw(OptionBackground[OptionSelected_]);
        for(auto &el: SettingsMenu_)
            Window.draw(el);
        for(auto &el: Settings_)
            Window.draw(el);
    }
    else if(PlaySettingsActive_)
    {
        for(auto &el: PlaySettingsMenu_)
            Window.draw(el);
    }
    this->ShowFPS(Clock, Window);
}
