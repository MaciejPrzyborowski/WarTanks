#pragma once

#include "Globals.h"

/**
 * @brief Klasa Animation
 */

class Animation
{
public:

    /**
     * @brief Konstruktor klasy Animation
     * @param fileName - nazwa pliku graficznego z kolejnymi klatkami animacji
     * @param position - określa początkową pozycję tekstury animacji
     * @param stepPosition - określa co ile pikseli ma się zmieniać dana klatka animacji
     * @param radius - długość promienia okręgu, w którym wyświetla się animacja
     * @param repeat - określa czy animacja ma być zapętlona
     * @param scale - skala animacji
     */
    Animation(const string &fileName, const sf::IntRect &position, const int &stepPosition,
              const int &radius, const bool &repeat, const float &scale);

    /**
     * @brief Zmienia pozycję tekstury animacji o wartość stepPosition_.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     * @return Zwraca informację czy animacja jest nadal aktywna
     */
    bool changeAnimation(const float &elapsed);

    /**
     * @brief Zmienia położenie animacji na ekranie
     * @param position - współrzędne punktu (x, y), w którym ma zostać wyświetlona animacja
     */
    void changePosition(const sf::Vector2f &position);

    /**
     * @brief Wyświetla animację na ekranie
     * @param window - okno gry
     */
    void draw(sf::RenderTarget &window);

    /**
     * @brief Sprawdza status animacji.
     * @return
     *        true - animacja jest aktywna;
     *        false - animacja nie jest aktywna
     */
    bool getStatus();

private:

    bool active_; /**< Określa czy animacja jest aktywna */
    bool repeat_; /**< Określa czy animacja ma być zapętlona */

    int stepPosition_; /**< Określa co ile pikseli ma się zmieniać dana klatka animacji */
    float stepTime_; /**< Określa czas po którym ma się zmieniać klatka animacji */
    float timeElapsed_; /**< Łączny czas trwania klatki animacji */

    sf::IntRect position_; /**< Aktualna pozycja tekstury animacji */
    sf::IntRect startPosition_; /**< Pozycja startowa tekstury animacji */
    sf::Texture texture_; /**< Tekstura animacji */
    sf::CircleShape shape_; /**< Animacja w kształcie okręgu */
};
