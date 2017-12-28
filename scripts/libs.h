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
#define GROUND_TILE_SIZE 256
#define FPS 60

#define PI 3.141592

#define DEFAULT_SPEED 3
#define INVALID -1
#define MAX_STATES 5
#define MAX_ANIM 9
#define MAX_FRAMES 9
#define MAX_SOUNDS 6
#define MAX_WEAPONS 4

int MAX_ENEMIES = 10;

enum States{WALKING, IDLE};
enum WalkerSound{DAMAGE,DEAD,SHOT};

//SNAKE
enum snake_SOUNDS {SCREAM};
enum snake_states {WAND_SNAKE,SEARCH_SNAKE,HURT_SNAKE,CHASE_SNAKE,ATTACK_SNAKE,DEAD_SNAKE};
#define SNAKE_CHASE_SPEED 2.5
#define SNAKE_DEFAULT_SPEED 2
#define SNAKE_SAFE_ZONE 96*4

//PLAYER STATES
enum STATES_P {WALKING_P,IDLE_P};
enum WEAPON {MACHINEGUN, SHOTGUN, ROCKETLAUNCHER, FLAMETHROWER};
//ENEMY SCOUT STATES
enum STATES_E_SC {WALKING_E_SC, ATTACK_E_SC, IDLE_E_SC};

//CRAB STATES
enum crab_states {IDLE_CRAB, MOVE_CRAB, ATTACK_CRAB,BORN_CRAB};
//VARIABLES FOR DIFFERENT KINDS OF ATTACK
enum crab_projectile_attacks {ATK_DIRECT, ATK_RADIAL, ATK_FUZZY,ATK_CURVED};
enum crab_projectile_states {LAUNCHED, IMPACT, DESTROYED};
typedef int ENUM_TAG;

#define WHITE al_map_rgb(255,255,255)
#define RED al_map_rgb(255,0,0)
#define GREEN al_map_rgb(0,255,0)
#define BLUE al_map_rgb(0,0,255)
#define YELLOW al_map_rgb(255,255,0)
#define ORANGE al_map_rgb(255,165,0)
#define PURPLE al_map_rgb(128,0,128)
#define BLACK al_map_rgb(0,0,0)
#define GREY al_map_rgb(128,128,128)
#define PINK al_map_rgb(255,192,203)
#define BROWN al_map_rgb(165,42,42)

#endif
