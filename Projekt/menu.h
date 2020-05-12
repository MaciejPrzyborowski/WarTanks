#ifndef MENU_H
#define MENU_H
#define NUMBERS_OF_MENU_OPTIONS 3
#include "Globals.h"

class menu
{
public:
    menu();
    void ShowMenu(sf::RenderWindow &Window, int x);
    void ShowMenuSettings(sf::RenderWindow &Window, int x);
    void HideMenu();
    void MoveUp();
    void MoveDown();
    void PlayOption();
    int ReturnIndex();

private:
    sf::Font Font;
    sf::Text MenuOption[NUMBERS_OF_MENU_OPTIONS];
    int OptionSelected;
    bool isActive = true;
};

#endif // MENU_H
