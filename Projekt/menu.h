#pragma once

#include "Globals.h"

class Menu
{
public:
    Menu();

    void MainMenu();
    void Settings();
    void PlaySettings();

    void ShowSwitch(sf::Event &Event, sf::RenderWindow &Window);
    void ShowMenu(sf::RenderWindow &Window, sf::Clock Clock);

    void MoveUp();
    void MoveDown();
    void ChoiceByMouse(sf::RenderWindow &Window, sf::Event &Event);

    void FUp(vector<sf::Text> &Menu);
    void FDown(vector<sf::Text> &Menu);
    void SelectMenu(vector<sf::Text> &Menu, sf::Vector2i MousePosition, sf::RenderWindow &Window);

    void SetFPS();
    void ShowFPS(sf::Clock Clock, sf::RenderWindow &Window);
    void GameMusic();
    void GameSound();
    void GameControl();

    inline bool IsActiveMenu() {if(MainMenuActive_ || SettingsActive_ || PlaySettingsActive_) return true; return false;}

    inline void MainMenuActive() {MainMenuActive_ = true; SettingsActive_ = false; PlaySettingsActive_ = false; OptionSelected_ = 0;};
    inline void SettingsActive() {SettingsActive_ = true; MainMenuActive_ = false; PlaySettingsActive_ = false; OptionSelected_ = 0;};
    inline void PlaySettingsActive() {PlaySettingsActive_ = true; MainMenuActive_ = false; SettingsActive_ = false; OptionSelected_ = 0;};
    inline void HideMenu() {MainMenuActive_ = false; SettingsActive_ = false; PlaySettingsActive_ = false;};

private:
    sf::Font Font;

    size_t OptionSelected_;

    bool MainMenuActive_ = true;
    bool SettingsActive_ = false;
    bool PlaySettingsActive_ = false;

    bool IsMouseActive_ = false;

    bool FPS = false;
    bool GMusic = true;
    bool GSound = true;
    bool ArrowsControl = false;

    sf::Sound BackgroundMusic;
    sf::Sound SelectSound;

    sf::Sprite Sprite;

    sf::SoundBuffer Buffer;
    sf::SoundBuffer Buffer2;

    sf::Texture MenuBackground;

    vector<sf::RectangleShape> OptionBackground;
    vector<sf::Text> Settings_;
    vector<sf::Text> MainMenu_;
    vector<sf::Text> SettingsMenu_;
    vector<sf::Text> PlaySettingsMenu_;
};
