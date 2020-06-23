#pragma once

#include "Globals.h"
#include "Perlin.h"
#include "WorldObject.h"

/**
 * @brief Struktura StepLand
 */
struct StepLand
{
    int top_; /**< top_ */
    int bottom_; /**< bottom_ */
    float velocity_; /**< velocity_ */
    bool active_; /**< active_ */
};

/**
 * @brief Klasa Land
 */
class Land : public WorldObject, public Perlin
{
public:

    /**
     * @param octaves - liczba oktaw
     * @param persistence - mnożnik do amplitudy terenu
     */
    Land(const float &octaves, const float &persistence);

    /**
     * @brief Generuje teren mapy.
     */
    void reset();

    /**
     * @brief Usuwa teren w kształcie koła o środku w punkcie (x, y) i promieniu r.
     * @param x - współrzędna x dla środka koła
     * @param y - współrzędna y dla środka koła
     * @param r - promień koła
     */
    void destroyCircle(const int &x, const int &y, const int &radius);

    /**
     * @brief Usuwa kolumnę terenu w punkcie x dla y o początku - top, końcu - bottom.
     * @param x - współrzędna x
     * @param top - pierwsza wartość współrzędnej y
     * @param bottom - ostatnia wartość współrzędnej y
     */
    void destroyColumn(const int &x, int top, int bottom);

    /**
     * @brief Sprawdza kolizje z innymi obiektami.
     * @param object - obiekt z którym sprawdza kolizję
     */
    void getCollison(WorldObject &object);

    /**
     * @brief Aktualizuje i wyświetla teren.
     * @param window - okno gry
     */
    void draw(sf::RenderTarget &window);

    /**
     * @brief Obsługuje grawitacje terenu.
     * @param elapsed - czas jaki upłynął od ostatniego wywołania funkcji
     */
    void step(const float &elapsed);

    /**
     * @brief Sprawdza czy istnieje teren w punkcie (x, y).
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return
     *          true - istnieje teren w punkcie (x, y)
     *          false - nie istnieje teren w punkcie (x, y)
     */
    bool isSolidPixel(const int &x, const int &y);

    /**
     * @brief Oblicza kąt nachylenia powierzchni w punkcie (x, y).
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return Kąt nachylenia powierzchni w punkcie (x, y) w stopniach
     */
    float getAngleDegree(const int &x, const int &y);

    /**
     * @brief Oblicza kąt nachylenia powierzchni w punkcie (x, y). Tworzy kwadrat o boku 3 o środku w punkcie (x, y), następnie w całym kwadracie sumuje odległość od (x, y) dla istniejącego terenu.
     * @param x - współrzędna x
     * @param y - współrzędna y
     * @return Kąt nachylenia powierzchni w punkcie (x, y) w radianach
     */
    float getAngleRadian(const int &x, const int &y);

    /**
     * @brief Oblicza wysokość terenu w punkcie x.
     * @param x - współrzędna x
     * @return Wysokość terenu w punkcie x
     */
    int getLandHeight(const int &x);

private:
    bool modified_; /**< Czy teren został zmodyfikowany */
    float size_; /**< TODO: describe */

    sf::Image image_; /**< TODO: describe */
    sf::Sprite sprite_; /**< TODO: describe */
    sf::Texture texture_; /**< TODO: describe */
    std::vector<int> height_; /**< TODO: describe */
    std::map<int, StepLand> steps_; /**< TODO: describe */

    /**
     * @brief Oblicza gradient używając interpolacji liniowej
     * @param brightness - jasność koloru (im większa wartość tym kolor jest ciemniejszy)
     * @param darkColor - najciemniejszy kolor
     * @param lightColor - najjaśniejszy kolor
     * @return Kolor gradientu w zależności od jasności koloru
     */
    sf::Color gradient(const float &brightness, const sf::Color &darkColor, const sf::Color &lightColor);
};
