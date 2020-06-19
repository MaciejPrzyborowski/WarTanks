#pragma once

#include "Globals.h"

enum class MenuType
{
    None,
    Main,
    Settings
};

class Menu
{
public:
    Menu();
    void reset(bool settings);
    void move(int direction);
    void passEvent(sf::Event &event, sf::RenderWindow &window);
    void draw(sf::RenderTarget &window);

    bool getGameSettings(int setting);
    bool getMenuStatus();
    void setMenu(MenuType type);

private:
    sf::Font font_;
    sf::Sound menuSelectSound_;
    sf::SoundBuffer menuSelectSoundBuffer_;

    MenuType menuType_;
    size_t menuSelected_;

    bool isMouseActive_;
    bool gameSettings_[4];

    bool getMenuChoice();
    bool getMenuMouse(const sf::Vector2f &mousePosition);
    void setSettings(int setting);

    vector<sf::Text> menuOptions_;
    vector<sf::Text> menuSelectOptions_;
    vector<sf::RectangleShape> menuSelectBackground_;
};
