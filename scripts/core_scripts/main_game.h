#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#define MARGEM_ERRO (killed_enemies > MAX_ENEMIES - 3 && killed_enemies < MAX_ENEMIES)

void main_game()
{
	bool game_over = false;

	// Creates player
	Player player;

	// Pointer for all classes derived from enemies
	Enemy* enemy_pointer;
	// Enemies counter
	int killed_enemies = 0;
	int created_enemies = 0;

	// Play background music


	//al_stop_samples();

	al_stop_samples();
	al_play_sample(background_music, 0.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	// Background image load
	ALLEGRO_BITMAP *ground;
	ground = al_load_bitmap("images/ground.png");

	//Enemies spawn delay
	Frame Spawn_Fatso(3*60);
	Frame Spawn_Zombie(1.2*60);
	Frame Spawn_Dog(2.2*60);
	Frame Spawn_Doctor(3.2*60);
	Frame Spawn_Pyro(5*60);

	

	while(!game_over)
	{
		gets_input();

		//Draw background
		for(int i = ((int)(cam_x/GROUND_TILE_SIZE))*GROUND_TILE_SIZE-GROUND_TILE_SIZE;i < cam_x+DISPLAY_WIDTH+GROUND_TILE_SIZE;i += GROUND_TILE_SIZE)
		{
			for(int j = ((int)(cam_y/GROUND_TILE_SIZE))*GROUND_TILE_SIZE-GROUND_TILE_SIZE;j < cam_y +DISPLAY_HEIGHT;j += GROUND_TILE_SIZE)
			{
				al_draw_bitmap(ground,i-cam_x,j-cam_y,0);
			}
		}

		camera_update(player.x, player.y);

		if(created_enemies < MAX_ENEMIES)
		{
			if(++Spawn_Zombie.frameCount > Spawn_Zombie.frameDelay)
			{
				Spawn_Zombie.resetFrameCount();
				enemy_pointer = new Enemy_Zombie();
				Enemies.push_back(enemy_pointer);
				created_enemies++;
			}
			if(++Spawn_Dog.frameCount > Spawn_Dog.frameDelay)
			{
				Spawn_Dog.resetFrameCount();
				enemy_pointer = new Enemy_Dog();
				Enemies.push_back(enemy_pointer);
				created_enemies++;
			}
			if(++Spawn_Fatso.frameCount > Spawn_Fatso.frameDelay)
			{
				Spawn_Fatso.resetFrameCount();
				enemy_pointer = new Enemy_Fatso();
				Enemies.push_back(enemy_pointer);
				created_enemies++;
			}
			if(++Spawn_Doctor.frameCount > Spawn_Doctor.frameDelay)
			{
				Spawn_Doctor.resetFrameCount();
				enemy_pointer = new Enemy_Doctor();
				Enemies.push_back(enemy_pointer);
				created_enemies++;
			}
			if(++Spawn_Pyro.frameCount > Spawn_Pyro.frameDelay)
			{
				Spawn_Pyro.resetFrameCount();
				enemy_pointer = new Enemy_Pyro();
				Enemies.push_back(enemy_pointer);
				created_enemies++;
			}
		}
		else
		{
			if(!crab_killed && MARGEM_ERRO )
			{						
				for (int i = 0;i < Enemies.size(); i++)
				{
					delete Enemies[i];
				}

				Enemies.clear();

				cam_fixed = true;
				Crab_creator(player, ground);
	
				cam_fixed = false;
				created_enemies = 0;
				MAX_ENEMIES = 18;
				if(player.isAlive)
					crab_killed = true;
				player.life = 100;
			}
			else if(!snake_killed && MARGEM_ERRO)
			{		
				for (int i = 0;i < Enemies.size(); i++)
				{
					delete Enemies[i];
				}

				Enemies.clear();

				cam_fixed = true;
				Snake_creator(player, ground);

				cam_fixed = false;
				created_enemies = 0;
				MAX_ENEMIES = 25;
				if(player.isAlive)
					snake_killed = true;
				player.life = 10;
			}
			else if(!grim_killed && MARGEM_ERRO)
			{				
				for (int i = 0;i < Enemies.size(); i++)
				{
					delete Enemies[i];
				}
				Enemies.clear();

				cam_fixed = false;
				Grim_creator(player, ground);

				cam_fixed = false;
				created_enemies = 0;
				if(player.isAlive)
					grim_killed = true;
			}			
		}

		// Bullet update
		for(int i = 0;i < bullet_vector.size();i++)
		{
			bullet_vector[i]->update();
			bullet_vector[i]->draw();
		}

		// Enemy life update
		for(int i = 0;i < Enemies.size();i++)
		{
			if(!(Enemies[i]->life > 0))
			{
				al_play_sample(Enemies[i]->audio[DEAD], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				player.score += Enemies[i]->score;
				delete Enemies[i];
				Enemies.erase(Enemies.begin()+i);
				killed_enemies++;
			}
			else
			{
				Enemies[i]->update(player);
			}
		}

		// Player update
		if(player.life > 0)
		{
			player.update();
		}
		else
		{
			if(player_dead == false)
			{
				playerDeath();
			}
			else
			{
				for (int i = 0;i < Enemies.size(); i++)
				{
					delete Enemies[i];
				}
				Enemies.clear();
				return;
			}
		}

		if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE) && !al_key_down(&ks_prev,ALLEGRO_KEY_ESCAPE))
		{
			al_draw_textf(screen_font[0], ORANGE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "JOGO PAUSADO");
			al_flip_display();
			while(1)
			{
				gets_input();
				if(al_key_down(&keyboard_state,ALLEGRO_KEY_ENTER) && !al_key_down(&ks_prev,ALLEGRO_KEY_ENTER))
				{
					game_over = true;
					break;
				}
				else
				{
					al_draw_textf(screen_font[0], ORANGE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "JOGO PAUSADO");
					if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE) && !al_key_down(&ks_prev,ALLEGRO_KEY_ESCAPE))
					{
						break;
					}
				}
				al_rest(1.0/FPS);
			}
		}

		al_flip_display();

		al_rest(1.0/FPS);
	}

	//RESET ENEMIES AND SOUND
	for (int i = 0;i < Enemies.size(); i++)
	{
		delete Enemies[i];
	}
	Enemies.clear();
	al_stop_samples();
}

#endif
