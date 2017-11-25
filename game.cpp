#include "scripts/functionality_scripts/libs.h"
#include "scripts/functionality_scripts/frame.h"
#include "scripts/functionality_scripts/init.h"
#include "scripts/core_scripts/music.h"
#include "scripts/functionality_scripts/basic_functions.h"
#include "scripts/core_scripts/classes.h"
#include "scripts/player_scripts/bullet.h"
#include "scripts/player_scripts/player.h"
#include "scripts/enemies_scripts/enemy.h"
#include "scripts/enemies_scripts/normal_enemy.h"
#include "scripts/enemies_scripts/enemy_fatso.h"
#include "scripts/enemies_scripts/enemy_zombie.h"
#include "scripts/enemies_scripts/enemy_dog.h"
#include "scripts/enemies_scripts/enemy_doctor.h"
#include "scripts/enemies_scripts/enemy_pyro.h"
#include "scripts/bosses_scripts/class_snake_node.h"
#include "scripts/bosses_scripts/boss_snake.h"
#include "scripts/bosses_scripts/Snake_creator.h"
#include "scripts/bosses_scripts/bullet_crab.h"
#include "scripts/bosses_scripts/boss_crab.h"
#include "scripts/bosses_scripts/Crab_creator.h"
#include "scripts/bosses_scripts/world_end.h"
#include "scripts/bosses_scripts/grim_creator.h"
#include "scripts/core_scripts/main_game.h"
#include "scripts/core_scripts/menu.h"
#include "scripts/core_scripts/title_screen.h"

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
