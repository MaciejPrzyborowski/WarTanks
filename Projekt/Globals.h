#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cmath>

#define WindowWidth 800
#define WindowHeight 600
#define NazwaGry "WarTanks"

#define TankTextureSrc1 "tank1.png"
#define TankTextureSrc2 "tank2.png"
#define BarrelTextureSrc "barrel.png"

#define LERP(t, a, b) (a + t * (b - a))
#define RadianToDegree(radians) (radians * (180.0 / M_PI))

using namespace std;
