#include "Menu.h"

Menu::Menu() :
    isMouseActive_(false),
    gameSettings_{false, true, true, true}
{
    font_.loadFromFile(GameFontSrc);
    menuSelectSoundBuffer_.loadFromFile(SelectMenuSoundSrc);
    menuSelectSound_.setBuffer(menuSelectSoundBuffer_);
    menuSelectSound_.setVolume(1);
}

/**
 * Resetuje układ menu do ustawień domyślnych
 *
 * @param settings - określa czy resetowi podlegają ustawienia gry
 *            true - resetuje ustawienia gry do domyślnych
 *           false - nie resetuje ustawień gry do domyślnych
 */
void Menu::reset(bool settings)
{
    if(settings)
    {
        gameSettings_[0] = false;
        gameSettings_[1] = true;
        gameSettings_[2] = true;
        gameSettings_[3] = true;
    }
    isMouseActive_ = false;
    setMenu(MenuMain);
}

/**
 * Zmienia aktualny wybór w menu
 * Funkcja przeznaczona tylko dla obsługi klawiatury
 *
 * @param direction - kierunek w którą stronę ma zostać dokonana zmiana
 *               -1 - w górę
 *                1 - w dół
 */
void Menu::move(int direction)
{
    if(!((menuSelected_ == 0 && direction < 0) || (menuSelected_ == menuOptions_.size() - 1 && direction > 0)))
    {
        menuOptions_[menuSelected_].setFillColor(sf::Color::White);
        menuSelected_ += direction;
        menuOptions_[menuSelected_].setFillColor(sf::Color(150, 150, 150));
        menuSelectSound_.play();
    }
}

/**
 * Obsługuje zdarzenia wykonane przez gracza
 * Obsługiwana jest klawiatura oraz myszka gracza
 *
 * @param event - obiekt wszystkich zdarzeń
 * @param window - okno gry
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
    if(event.type == sf::Event::MouseMoved)
    {
        isMouseActive_ = getMenuMouse(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }
    if((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) ||
            (isMouseActive_ && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased))
    {
        if(!getMenuChoice())
        {
            window.close();
        }
    }
}

/**
 * Wyświetla aktualne menu
 *
 * @param window - okno gry
 */
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

/**
 * Sprawdza status menu
 *
 * @return
 *        true - menu jest aktywne
 *        false - menu nie jest aktywne
 */
bool Menu::getMenuStatus()
{
    return !(menuType_ == MenuNone);
}

/**
 * Sprawdza ustawienia gry
 *
 * @param setting - ID ustawienia gry:
 *              0 - licznik FPS
 *              1 - muzyka w grze
 *              2 - muzyka w menu
 *              3 - dźwięki w menu
 *
 * @return
 *        true - ustawienie jest włączone
 *        false - ustawienie jest wyłączone
 */
bool Menu::getGameSettings(int setting)
{
    return gameSettings_[setting];
}

/**
 * Ustawia dane w menu
 *
 * @param type - typ menu:
 *        MenuNone - brak menu
 *        MenuMain - menu główne
 *        MenuPlay - menu gry
 *        MenuSettings - menu ustawień
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
            SettingNames = {"Tryb Offline", "Tryb MultiPlayer", "Wstecz"};
        }
        if(type == MenuSettings)
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

/**
 * Obsługuje wybór elementu z menu
 *
 * @return
 *        true - menu jest aktywne
 *        false - menu zostało zamknięte
 */
bool Menu::getMenuChoice()
{
    bool isMenuActive = true;
    if(menuType_ == MenuMain)
    {
        switch(menuSelected_)
        {
            case 0:
            {
                setMenu(MenuNone);
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
                isMenuActive = false;
                break;
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
                break;
            }
            case 1:
            {
                setMenu(MenuNone);
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
                setSettings(menuSelected_);
                break;
            }
        }
    }
    return isMenuActive;
}

/**
 * Sprawdza czy myszka znajduje się aktualnie na wybranym elemencie
 * Funkcja dodatkowo ustawia element menu, na którym znajduje się myszka, jako aktywny
 *
 * @return
 *        true - myszka znajduje się na wybranym elemencie
 *        false - myszka nie znajduje się na wybranym elemencie
 */
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

/**
 * Zmienia ustawienia gry
 *
 * @param setting - ID ustawienia gry:
 *              0 - licznik FPS
 *              1 - muzyka w grze
 *              2 - muzyka w menu
 *              3 - dźwięki w menu
 */
void Menu::setSettings(int setting)
{
    gameSettings_[setting] = !gameSettings_[setting];
    if(gameSettings_[setting])
    {
        if(setting == 3)
        {
            menuSelectSound_.setVolume(1);
        }
        menuSelectOptions_[setting].setString("TAK");
        menuSelectOptions_[setting].setFillColor(sf::Color::Green);
    }
    else
    {
        if(setting == 3)
        {
            menuSelectSound_.setVolume(0);
        }
        menuSelectOptions_[setting].setString("NIE");
        menuSelectOptions_[setting].setFillColor(sf::Color::Red);
    }
}
