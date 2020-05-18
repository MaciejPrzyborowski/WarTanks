#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cmath>

#define WindowHeight 600
#define WindowWidth 800
#define TankTextureSrc "tank.png"
#define BarrelTextureSrc "turret.png"
#define NazwaGry "WarTanks"
#define LERP(t, a, b) (a + t * (b - a))
#define TO_DEG(x) (x * 180.0 / M_PI)

using namespace std;
