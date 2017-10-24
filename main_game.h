#ifndef MAIN_GAME_H
#define MAIN_GAME_H

void main_game()
{
	bool game_over = false;

	Player player;
	
	Bullet* bullet;
	Bullet bullet_base;
	std::vector<Bullet*> bullet_vector;

	background_music = al_load_sample("audio/Organ 67 - Fall of an Empire - Intense Powerful Organ Music.ogg");
	al_play_sample(background_music, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	//Frame delayed
	Frame Player_Shot(5);

	while(!game_over)
	{

		al_get_keyboard_state(&keyboard_state);
		al_get_mouse_state(&mouse_state);

		al_clear_to_color(al_map_rgb(255,255,255));

		player.move();
		
		cam_x = player.x - DISPLAY_WIDTH/2;
		cam_y = player.y - DISPLAY_HEIGHT/2;

		if(Player_Shot.frameCount > 0)
			Player_Shot.frameCount--;

		if((mouse_state.buttons & 1) && (!Player_Shot.frameCount))
		{
			Player_Shot.frameCount = Player_Shot.frameDelay;

			al_play_sample(player.audio[SHOT], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			bullet = new Bullet(bullet_base,player);
			bullet_vector.push_back(bullet);
		}

		for(int i = 0;i < bullet_vector.size();i++)
		{
			bullet_vector[i]->update();
			bullet_vector[i]->draw();
		}

		if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE))
		{
			game_over = true;
		}

		al_draw_circle(0-cam_x,0-cam_y,96,al_map_rgb(0,0,0),10);
		player.draw();

		al_flip_display();
	}
}

#endif
