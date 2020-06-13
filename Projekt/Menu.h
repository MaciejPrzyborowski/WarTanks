#pragma once

#include "Globals.h"

enum MenuType
{
    MenuNone,
    MenuMain,
    MenuPlay,
    MenuSettings
};

class Menu
{
public:
    Menu();
    void passEvent(sf::Event &event, sf::RenderWindow &window);
    void draw(sf::RenderTarget &window);

    bool getStatus();
    void setMenu(MenuType type);

private:
    sf::Font font_;
    sf::Sound menuMusic_;
    sf::Sound menuSelectSound_;
    sf::SoundBuffer menuMusicBuffer_;
    sf::SoundBuffer menuSelectSoundBuffer_;

    MenuType menuType_;
    size_t menuSelected_;
    bool isMouseActive_;
    bool gameSettings_[4];

    void move(int direction);
    void setClientSetting(int setting);
    void getMenu(MenuType type);

    vector<sf::Text> menuOptions_;
    vector<sf::Text> menuSelectOptions_;
    vector<sf::RectangleShape> menuSelectBackground_;
};
