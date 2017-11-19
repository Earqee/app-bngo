#include "libs.h"
#include "frame.h"
#include "init.h"
#include "music.h"
#include "basic_functions.h"
#include "classes.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "normal_enemy.h"
#include "enemy_fatso.h"
#include "enemy_zombie.h"
#include "enemy_dog.h"
#include "enemy_doctor.h"
#include "enemy_pyro.h"
#include "class_snake_node.h"
#include "boss_snake.h"
#include "Snake_creator.h"
#include "bullet_crab.h"
#include "boss_crab.h"
#include "Crab_creator.h"
#include "world_end.h"
#include "grim_creator.h"
#include "main_game.h"
#include "menu.h"
#include "title_screen.h"


int main( void )
{
	//initializing libs
	if(!initialize()) return INVALID;
	srand(time(NULL));

	//allegro variables
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if(!display) return INVALID;

	//music load
	background_music = al_load_sample("audio/Organ 67 - Fall of an Empire - Intense Powerful Organ Music.ogg");
	sefudeu_music = al_load_sample("audio/sefudeu.wav");
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);


	//
	menu_music = al_load_sample("audio/lavender.wav");
	
	//
	title_screen();

	al_destroy_display(display);
	return 0;
}
