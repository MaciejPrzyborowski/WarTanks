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

private:
    sf::Font Font;
    sf::Sound MenuMusic;
    sf::Sound MenuSelectSound;
    sf::Sprite BackgroundSprite;
    sf::Texture BackgroundTexture;
    sf::SoundBuffer MenuMusicBuffer;
    sf::SoundBuffer MenuSelectSoundBuffer;

    MenuType menuType_;
    size_t menuSelected_;
    bool isMouseActive_;
    bool gameSettings_[4];

    void move(int direction);
    void setClientSetting(int setting);
    void setMenu(MenuType type);
    void getMenu(MenuType type);

    vector<sf::Text> menuOptions_;
    vector<sf::Text> menuSelectOptions_;
    vector<sf::RectangleShape> menuSelectBackground_;
};
