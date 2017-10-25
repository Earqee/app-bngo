#ifndef MAIN_GAME_H
#define MAIN_GAME_H

void main_game()
{
	bool game_over = false;

	Player player;
	
	Bullet* bullet;
	Bullet bullet_base;
	std::vector<Bullet*> bullet_vector;
	
	/*Enemies*/
	Enemy* enemy_pointer; //Ponteiro para classe base pode apontar para "filhos"
	//Cópia de cada tipo de inimigo
	Enemy_follower follower_base;
	Enemy_scout scout_base;
	Enemy_support support_base;
	Enemy_tech tech_base;

	/*Play background music*/
	al_play_sample(background_music, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	

	Frame Player_Shot(5); //Can player shoot?

	while(!game_over)
	{
		//Input
		al_get_keyboard_state(&keyboard_state);
		al_get_mouse_state(&mouse_state);
		
		//Draw background
		al_clear_to_color(al_map_rgb(255,255,255));
		
		//Player update
		player.move();
		
		//Camera update
		cam_x = player.x - DISPLAY_WIDTH/2;
		cam_y = player.y - DISPLAY_HEIGHT/2;

		//PLAYER SHOT

		if(Player_Shot.frameCount > 0)
			Player_Shot.frameCount--;
		
		if((mouse_state.buttons & 1) && (!Player_Shot.frameCount))
		{
			bullet = new Bullet(bullet_base,player);
			bullet_vector.push_back(bullet);
			
			Player_Shot.frameCount = Player_Shot.frameDelay;
			al_play_sample(player.audio[SHOT], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		//Criar inimigos
		if(enemy_count < MAX_ENEMIES)
		{
			switch(rand()%4)
			{
				case 0 : enemy_pointer = new Enemy_follower();
					break;
				case 1 : enemy_pointer = new Enemy_scout();
					break;
				case 2 : enemy_pointer = new Enemy_support();
					break;
				case 4 : enemy_pointer = new Enemy_tech();
					break;
			}
			enemy_count++;
		}
		
		//Bullet update
		for(int i = 0;i < bullet_vector.size();i++)
		{
			bullet_vector[i]->update();
			bullet_vector[i]->draw();
		}
		
		//DRAW
		al_draw_circle(0-cam_x,0-cam_y,96,al_map_rgb(0,0,0),10);		//referencial
		player.draw();
	
		
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE))
		{
			game_over = true;
		}
		
		al_flip_display();
	}
}

#endif
