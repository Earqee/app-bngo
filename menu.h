#ifndef MENU_H
#define MENU_H

void menu()
{
	while(1)
	{
		al_get_keyboard_state(&keyboard_state);
		
		//al_flip_display();
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_ENTER))
		{
			main_game();
		}
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_I))
		{
			break;//instructions();
		}
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_E))
		{
			break;//exit();
		}
	}
}

#endif