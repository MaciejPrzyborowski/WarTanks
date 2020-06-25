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
     * @param position - określa który element z pliku graficznego trzeba wyciąć
     * @param stepPosition - określa co ile pikseli ma się zmieniać dana klatka animacji
     * @param radius - długość promienia okręgu, w którym wyświetla się animacja
     * @param repeat - określa czy animacja ma się cały czas odtwarzać
     *          true - animacja się zapętla
     *          false - animacja odtwarza się raz
     * @param scale - skala animacji
     */
    Animation(const string &fileName, const sf::IntRect &position, const int &stepPosition, const int &radius, const bool &repeat, const float &scale);

    /**
     * @brief Zmienia pozycję obrazka o wartość stepPosition_ tworząc jego animację.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void changeAnimation(const float &elapsed);

    /**
     * @brief Wyświetla animację w punkcie position(x,y).
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     * @param position - współrzędne punktu (x,y), w którym ma zostać wyświetlona animacja
     * @param window - okno gry
     */
    void draw(const float &elapsed, const sf::Vector2f &position, sf::RenderTarget &window);

    /**
     * @brief Sprawdza status animacji.
     * @return
     *          true - animacja jest aktywna
     *          false - animacja nie jest aktywna
     */
    bool getStatus();

private:
    bool active_; /**< Czy animacja jest aktywna */
    bool repeat_; /**< Czy animacja ma się zapętlać */

    int stepPosition_; /**< Co ile pikseli ma się zmieniać dana klatka animacji */
    float stepTime_; /**< Co jaki czas ma się zmieniać klatka animacji */
    float timeElapsed_; /**< Łączny czas trwania klatki */

    sf::IntRect position_; /**< Element */
    sf::IntRect startPosition_; /**< Określa który element z pliku graficznego trzeba wyciąć */
    sf::Texture texture_; /**< Tekstura animacji */
    sf::CircleShape shape_; /**< Animacja ma kształt okręgu */
};
