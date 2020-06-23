#ifndef CONTROLL_H
#define CONTROLL_H

#include <World.h>
#include <Menu.h>


/**
 * @brief Klasa Controll
 */
class Controll
{
public:
    /**
     * @brief
     *
     */
    Controll();

    /**
     * @brief Obsługuje zdarzenia wykonane przez gracza w menu. Obsługiwana jest klawiatura oraz myszka gracza.
     * @param event - obiekt wszystkich zdarzeń
     * @param window - okno gry
     * @param menu - wskaźnik do obiektu klasy Menu
     */
    void menuPassEvent(const sf::Event &event, sf::RenderWindow &window, unique_ptr<Menu> &menu);

    /**
     * @brief Obsługuje zdarzenia wykonane przez gracza w grze. Obsługiwana jest klawiatura oraz myszka gracza.
     * @param event - obiekt wszystkich zdarzeń
     * @param window - okno gry
     * @param object - wskaźnik do obiektu klasy WorldObject
     */
    void tankPassEvent(const sf::Event &event, sf::RenderWindow &window, WorldObject *object);

private:

};

#endif
