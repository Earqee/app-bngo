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
	
	/*Play background music*/
	al_play_sample(background_music, 0.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	

	// Background image load
	ALLEGRO_BITMAP *ground;
	ground = al_load_bitmap("images/ground.png");

	Frame Player_Shot(5); //Can player shoot? (1/12)s delay
	Frame Spawn_Fatso(180); //Can fatso spawn? (3,0)s delay
	Frame Spawn_Zombie(80); //Can zombie spawn? (1,2)s delay
	Frame Spawn_Dog(140); //Can dog spawn? (2,2)s delay
	Frame Spawn_Doctor(200); //Can Doctor spawn? (3,2)s delay
	Frame Spawn_Pyro(300); //Can DoctorPyro spawn? (5,0)s delay
	
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
		
		//Camera update
		cam_x = player.x - DISPLAY_WIDTH/2;
		cam_y = player.y - DISPLAY_HEIGHT/2;

		//PLAYER SHOT
		if(al_key_down(&keyboard_state, ALLEGRO_KEY_T))
		{
			player.current_weapon = SHOTGUN;
		}
		if(al_key_down(&keyboard_state, ALLEGRO_KEY_R))
		{
			player.current_weapon = MACHINEGUN;
		}

		std::cout << player.current_weapon << std::endl;

		if(Player_Shot.frameCount > 0)
			Player_Shot.frameCount--;
		
		if((mouse_state.buttons & 1) && (!Player_Shot.frameCount))
		{
			switch(player.current_weapon)
			{
				case MACHINEGUN:
				{
					Player_Shot.frameDelay = 5;
					Player_Shot.frameCount = Player_Shot.frameDelay;
					bullet = new Bullet(bullet_base,player, MACHINEGUN, 0);
					bullet_vector.push_back(bullet);
					Player_Shot.frameCount = Player_Shot.frameDelay;
					break;
				}
				case SHOTGUN:
				{
					Player_Shot.frameDelay = 80;
					Player_Shot.frameCount = Player_Shot.frameDelay;
					for(int i = 0; i < 5; i++)
					{
						//Essa foi ótima, explico-lhes na segunda
						bullet = new Bullet(bullet_base,player, SHOTGUN, i-2); 
						bullet_vector.push_back(bullet);
					}
					break;					
				}
				default:
				break;
			}
			
			al_play_sample(player.weapon_audio[player.current_weapon], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		
		if(++Spawn_Zombie.frameCount > Spawn_Zombie.frameDelay)
		{
			Spawn_Zombie.resetFrameCount();
			enemy_pointer = new Enemy_Zombie();
			Enemies.push_back(enemy_pointer);
		}

		if(++Spawn_Dog.frameCount > Spawn_Dog.frameDelay)
		{
			Spawn_Dog.resetFrameCount();
			enemy_pointer = new Enemy_Dog();
			Enemies.push_back(enemy_pointer);
		}
		if(++Spawn_Fatso.frameCount > Spawn_Fatso.frameDelay)
		{
			Spawn_Fatso.resetFrameCount();
			enemy_pointer = new Enemy_Fatso();
			Enemies.push_back(enemy_pointer);
		}
		
		if(++Spawn_Doctor.frameCount > Spawn_Doctor.frameDelay)
		{
			Spawn_Doctor.resetFrameCount();
			enemy_pointer = new Enemy_Doctor();
			Enemies.push_back(enemy_pointer);
		}
		if(++Spawn_Pyro.frameCount > Spawn_Pyro.frameDelay)
		{
			Spawn_Pyro.resetFrameCount();
			enemy_pointer = new Enemy_Pyro();
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
			// Enemy life update
			if(!(Enemies[i]->life > 0))
			{
				al_play_sample(Enemies[i]->audio[DEAD], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				delete Enemies[i];
				Enemies.erase(Enemies.begin()+i);	
			}
			else
			{
				Enemies[i]->update(player);
			}
		}
		
		//DRAW
		al_draw_circle(0-cam_x,0-cam_y,96,al_map_rgb(0,0,0),10);		//referencial
		player.draw();		
	
		
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE))
		{
			game_over = true;
		}
		
		al_rest(1/60);
		al_flip_display();
	}
}

#endif
