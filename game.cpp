#include "libs.h"
#include "frame.h"
#include "init.h"
#include "music.h"
#include "basic_functions.h"
#include "classes.h"
#include "player.h"
#include "bullet.h"
#include "main_game.h"
#include "menu.h"


int main( void )
{
	//initializing libs
	if(!initialize()) return INVALID;

	//allegro variables
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if(!display) return INVALID;

	menu();

	al_destroy_display(display);
	return 0;
}
