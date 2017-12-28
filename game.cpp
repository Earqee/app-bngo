#include "scripts/libs.h"
#include "scripts/frame.h"
#include "scripts/init.h"
#include "scripts/music.h"
#include "scripts/basic_functions.h"
#include "scripts/classes.h"
#include "scripts/bullet.h"
#include "scripts/player.h"
#include "scripts/enemy.h"
#include "scripts/normal_enemy.h"
#include "scripts/enemy_fatso.h"
#include "scripts/enemy_zombie.h"
#include "scripts/enemy_dog.h"
#include "scripts/enemy_doctor.h"
#include "scripts/enemy_pyro.h"
#include "scripts/class_snake_node.h"
#include "scripts/boss_snake.h"
#include "scripts/Snake_creator.h"
#include "scripts/bullet_crab.h"
#include "scripts/boss_crab.h"
#include "scripts/Crab_creator.h"
#include "scripts/world_end.h"
#include "scripts/grim_creator.h"
#include "scripts/main_game.h"
#include "scripts/menu.h"
#include "scripts/title_screen.h"


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
