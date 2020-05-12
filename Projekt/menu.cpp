#include "menu.h"

menu::menu()
{
    Font.loadFromFile("game_font.ttf");

    MenuOption[0].setFont(Font);
    MenuOption[0].setColor(sf::Color::White);
    MenuOption[0].setString("Graj");
    MenuOption[0].setPosition(sf::Vector2f(WindowWidth/10, WindowHeight * 0.2));

    MenuOption[1].setFont(Font);
    MenuOption[1].setColor(sf::Color::White);
    MenuOption[1].setString("Ustawienia");
    MenuOption[1].setPosition(sf::Vector2f(WindowWidth/10, WindowHeight * 0.3));

    MenuOption[2].setFont(Font);
    MenuOption[2].setColor(sf::Color::White);
    MenuOption[2].setString("Wyjdz");
    MenuOption[2].setPosition(sf::Vector2f(WindowWidth/10, WindowHeight * 0.4));

    OptionSelected = 0;
}

void menu::ShowMenu(sf::RenderWindow &Window, int x)
{

    if(isActive)
    {
        sf::Texture MenuBackground;
        MenuBackground.loadFromFile("menu_gackground.jpg");
        sf::Sprite Sprite;
        Sprite.setTexture(MenuBackground);
        sf::Vector2u TextureSize = MenuBackground.getSize();
        sf::Vector2u WindowSize = Window.getSize();
        float scaleX = (float)WindowSize.x/TextureSize.x;
        float scaleY = (float)WindowSize.y/TextureSize.y;
        Sprite.setScale(scaleX, scaleY);
        Window.draw(Sprite);

        for(size_t i = 0; i < NUMBERS_OF_MENU_OPTIONS; i++)
        {
            MenuOption[i].setOutlineThickness(5);
            MenuOption[i].setOutlineColor(sf::Color::Black);
            MenuOption[i].setCharacterSize(x*0.05);
            Window.draw(MenuOption[i]);
        }
    }
}

void menu::ShowMenuSettings(sf::RenderWindow &Window, int x)
{

}

void menu::HideMenu()
{
    isActive = false;
}

void menu::MoveUp()
{
    if(isActive && OptionSelected - 1 >= 0)
    {
        MenuOption[OptionSelected].setColor(sf::Color::White);
        OptionSelected--;
        MenuOption[OptionSelected].setColor(sf::Color(150,150,150));
    }
}

void menu::MoveDown()
{
    if(isActive && OptionSelected +1 < NUMBERS_OF_MENU_OPTIONS)
    {
        MenuOption[OptionSelected].setColor(sf::Color::White);
        OptionSelected++;
        MenuOption[OptionSelected].setColor(sf::Color(150,150,150));
    }
}

void menu::PlayOption()
{
    isActive = false;

}

int menu::ReturnIndex()
{
    return OptionSelected;
}
