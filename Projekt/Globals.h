#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <list>

#define WindowFPS 120
#define WindowWidth 800
#define WindowHeight 600
#define NazwaGry "WarTanks"

#define MenuMusicSrc "menu_music.wav"
#define SelectMenuSoundSrc "select_sound.wav"

#define GameFont "game_font.ttf"
#define TankTextureSrc1 "tank1.png"
#define TankTextureSrc2 "tank2.png"
#define BarrelTextureSrc "barrel.png"
#define CrosshairTextureSrc "crosshair.png"
#define ExplosionTextureSrc "explosion.png"
#define FireworksEndGameAnimation "fireworks.png"
#define FireEndGameAnimation "fire_animation.png"
#define MenuBackgroundTextureSrc "menu_background.jpg"
#define GameBackgroundTextureSrc "game_background.png"

#define LERP(t, a, b) (a + t * (b - a))
#define RadianToDegree(radians) (radians * (180.0 / M_PI))
#define DegreeToRadian(degree) (degree * (M_PI / 180.0))

using namespace std;

const int Gravity = 180;
