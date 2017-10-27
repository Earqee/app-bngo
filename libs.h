#ifndef LIBS_H
#define LIBS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include <vector>
#include <math.h>
#include <iostream>

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720
#define GROUND_TILE_SIZE 64
#define FPS 60

#define PI 3.141592

#define DEFAULT_SPEED 3
#define INVALID -1
#define MAX_STATES 5
#define MAX_ANIM 9
#define MAX_FRAMES 9
#define MAX_SOUNDS 3
#define MAX_ENEMIES 10
#define MAX_WEAPONS 4

enum States{WALKING, IDLE};
enum WalkerSound{DAMAGE,DEAD,SHOT};

//PLAYER STATES
enum STATES_P {WALKING_P,IDLE_P};
enum WEAPON {MACHINEGUN, SHOTGUN, ROCKETLAUNCHER, FLAMETHROWER};
//ENEMY SCOUT STATES
enum STATES_E_SC {WALKING_E_SC, ATTACK_E_SC, IDLE_E_SC};

typedef int ENUM_TAG;


#endif
