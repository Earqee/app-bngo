#include "libs.h"
#include "frame.h"
#include "init.h"
#include "music.h"
#include "basic_functions.h"
#include "classes.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "normal_enemy.h"
#include "enemy_fatso.h"
#include "enemy_zombie.h"
#include "enemy_dog.h"
#include "enemy_doctor.h"
#include "enemy_pyro.h"
#include "main_game.h"
#include "menu.h"

int main( void )
{
	//initializing libs
	if(!initialize()) return INVALID;

	//allegro variables
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if(!display) return INVALID;

	//music load
	background_music = al_load_sample("audio/Organ 67 - Fall of an Empire - Intense Powerful Organ Music.ogg");

	menu();

	al_destroy_display(display);
	return 0;
}
