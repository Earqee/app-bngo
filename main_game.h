#ifndef MAIN_GAME_H
#define MAIN_GAME_H

void main_game()
{
	bool game_over = false;

	Player player;
	
	Bullet* bullet;
	Bullet bullet_base;
	std::vector<Bullet*> bullet_vector;

	ALLEGRO_BITMAP *background = al_load_bitmap("ruined_tower04big.jpg");

	while(!game_over)
	{
		al_get_keyboard_state(&keyboard_state);
		al_get_mouse_state(&mouse_state);

		al_draw_bitmap(background, 0, 0, 0);

		player.move();
		player.draw();

		if(mouse_state.buttons & 1)
		{
			bullet = new Bullet(bullet_base,player);
			bullet_vector.push_back(bullet);
		}

		for(int i = 0;i < bullet_vector.size();i++)
		{
			//bullet_vector[i]->move();
			bullet_vector[i]->draw();
		}

		if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE))
		{
			game_over = true;
		}

		al_flip_display();
	}
}

#endif