#pragma once

#include "Globals.h"

class Menu
{
public:
    Menu();

    void MainMenu();
    void Settings();
    void PlaySettings();

    void ShowMenu(sf::RenderWindow &Window);
    void ShowSettings(sf::RenderWindow &Window);
    void ShowPlaySettings(sf::RenderWindow &Window);

    void MoveUp(sf::Sound &SelectSound);
    void MoveDown(sf::Sound &SelectSound);
    void ChoiceByMouse(sf::RenderWindow &Window, sf::Event &Event, sf::Sound &SelectSound);

    inline void MainMenuActive() {MainMenuActive_ = true; SettingsActive_ = false; PlaySettingsActive_ = false; OptionSelected_ = 0;};
    inline void SettingsActive() {SettingsActive_ = true; MainMenuActive_ = false; PlaySettingsActive_ = false; OptionSelected_ = 0;};
    inline void PlaySettingsActive() {PlaySettingsActive_ = true; MainMenuActive_ = false; SettingsActive_ = false; OptionSelected_ = 0;};
    inline void HideMenu() {MainMenuActive_ = false; SettingsActive_ = false; PlaySettingsActive_ = false;};

    inline bool GetMenuStatus() {return MainMenuActive_;};
    inline bool GetSettingsStatus() {return SettingsActive_;};
    inline bool GetPlaySettingsStatus() {return PlaySettingsActive_;};

    inline int GetIndex() {return OptionSelected_;};


private:
    sf::Font Font;

    size_t OptionSelected_ = 0;

    bool MainMenuActive_ = true;
    bool SettingsActive_ = false;
    bool PlaySettingsActive_ = false;

    bool IsMouseActive_ = false;

    vector<sf::RectangleShape> OptionBackground;
    vector<sf::Text> MainMenu_;
    vector<sf::Text> Settings_;
    vector<sf::Text> PlaySettings_;
};
