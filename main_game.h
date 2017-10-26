#ifndef MAIN_GAME_H
#define MAIN_GAME_H

void main_game()
{
	bool game_over = false;

	Player player;
	
	Bullet* bullet;
	Bullet bullet_base;
	
	//Enemies
	Enemy* enemy_pointer; //Ponteiro para classe base pode apontar para "filhos"
	//Cópia de cada tipo de inimigo
	
	Enemy_follower follower_base;
	Enemy_scout scout_base;
	Enemy_support support_base;
	Enemy_tech tech_base;

	/*Play background music*/
	al_play_sample(background_music, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	

	// Background image load
	ALLEGRO_BITMAP *ground;
	ground = al_load_bitmap("images/ground.png");

	Frame Player_Shot(5); //Can player shoot?

	while(!game_over)
	{
		//Input
		al_get_keyboard_state(&keyboard_state);
		al_get_mouse_state(&mouse_state);
		
		//Draw background
		for(int i = ((int)(cam_x/GROUND_TILE_SIZE))*GROUND_TILE_SIZE-GROUND_TILE_SIZE;i < cam_x+DISPLAY_WIDTH+GROUND_TILE_SIZE;i += GROUND_TILE_SIZE)
		{
			for(int j = ((int)(cam_y/GROUND_TILE_SIZE))*GROUND_TILE_SIZE-GROUND_TILE_SIZE;j < cam_y +DISPLAY_HEIGHT;j += GROUND_TILE_SIZE)
			{
				al_draw_bitmap(ground,i-cam_x,j-cam_y,0);
			}
		}

		
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
		
		if(Enemies.size() < MAX_ENEMIES)
		{
			enemy_pointer = new Enemy_scout();
			Enemies.push_back(enemy_pointer);
		}
		
		//Bullet update
		for(int i = 0;i < bullet_vector.size();i++)
		{
			bullet_vector[i]->update();
			bullet_vector[i]->draw();
		}

		
		for(int i = 0;i < Enemies.size();i++)
		{
			Enemies[i]->update(player);
			
			// Enemy life update
			if(!(Enemies[i]->life > 0))
			{
				delete Enemies[i];
				Enemies.erase(Enemies.begin()+i);	
			}
			else
			{
				Enemies[i]->draw();
			}
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
