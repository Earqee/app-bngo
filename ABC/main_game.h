#ifndef MAIN_GAME_H
#define MAIN_GAME_H

void main_game()
{
	srand(time(NULL));

	al_stop_samples();
	bool game_over = false;

	Player player;
	
	Bullet* bullet;
	Bullet bullet_base;
	 
	//Enemies
	Enemy* enemy_pointer; //Ponteiro para classe base pode apontar para "filhos"
	//Cópia de cada tipo de inimigo	
	
	/*Play background music*/
	al_play_sample(background_music, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	

	// Background image load
	ALLEGRO_BITMAP *ground;
	ground = al_load_bitmap("optical-illusions-wallpaper-5.jpg");

	
	Frame Player_Shot(5); //Can player shoot? (1/12)s delay
	/*
	Frame Spawn_Fatso(400); //Can fatso spawn? (3,0)s delay
	Frame Spawn_Zombie(200); //Can zombie spawn? (1,2)s delay
	Frame Spawn_Dog(600); //Can dog spawn? (2,2)s delay
	Frame Spawn_Doctor(800); //Can Doctor spawn? (3,2)s delay
	Frame Spawn_Pyro(1000); //Can DoctorPyro spawn? (5,0)s delay
	*/
	//Frame The_End_of_World();
	SpriteFrame Player_Shot_Anim(5);

	Frame Laught[LAUGHTS](20);
	int text_x_position[LAUGHTS];
	int text_y_position[LAUGHTS];

	The_Grim_Reaper the_grim_reaper;

	while(!game_over)
	{
		//Input
		al_get_keyboard_state(&keyboard_state);
		al_get_mouse_state(&mouse_state);
		
		al_draw_bitmap(ground, -800, -500, 0);
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		for(int i = 0; i < strikes_vector.size(); i++)
		{
			strikes_vector[i]->draw();
			strikes_vector[i]->update();
		}


		//PLAYER SHOT
		if(al_key_down(&keyboard_state, ALLEGRO_KEY_T))
		{
			player.current_weapon = SHOTGUN;
		}
		if(al_key_down(&keyboard_state, ALLEGRO_KEY_R))
		{
			player.current_weapon = MACHINEGUN;
		}

		if(Player_Shot.frameCount > 0)
			Player_Shot.frameCount--;

		if(Player_Shot_Anim.frameCount)
		{
			Player_Shot_Anim.frameCount--;
			Player_Shot_Anim.draw(player);			
		}
		
		if((mouse_state.buttons & 1) && (!Player_Shot.frameCount))
		{
			Player_Shot_Anim.frameCount = Player_Shot_Anim.frameDelay;
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
					for(int j = 0; j < 3; j++)
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
			
			al_play_sample(player.weapon_audio[player.current_weapon], 0.75, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		
		/*
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
		*/			
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

		/////////////////////


		double grim_x_real =  the_grim_reaper.x - the_grim_reaper.bound_x/2 + 20;
		double grim_bound_x_real = the_grim_reaper.x +the_grim_reaper.bound_x/2 - 20;
		double grim_y_real = the_grim_reaper.y - the_grim_reaper.bound_y/2 + 20;
		double grim_bound_y_real = the_grim_reaper.y + the_grim_reaper.bound_y/2 - 20;

		al_draw_rectangle(grim_x_real, grim_y_real, grim_bound_x_real, grim_bound_y_real, al_map_rgb(255, 255, 255), 1);

		the_grim_reaper.move(player);
		if(the_grim_reaper.STATE != MERGE && the_grim_reaper.STATE != ELIMINATE)
		{
			the_grim_reaper.draw();
			
			if(the_grim_reaper.STATE == SENTENTIATE || the_grim_reaper.STATE == RECONSTRUCTION)
			{			
				for(int i = 0; i < LAUGHTS; i++)
				{
					if(++Laught[i].frameCount > Laught[i].frameDelay)
					{
						Laught[i].resetFrameCount();

						text_x_position[i] = rand()%(DISPLAY_WIDTH - 200);
						text_y_position[i] = rand()%(DISPLAY_HEIGHT - 80);	
					}

					al_draw_text(fonte_arial, al_map_rgb(255, 255, 255), text_x_position[i], text_y_position[i],  ALLEGRO_ALIGN_CENTRE, 
			   			"HAHA");
				}
			}			
		}
		else if(the_grim_reaper.STATE == MERGE)
		{
			if(the_grim_reaper.world_end_attack)
			{
				for(int i = 0; i < 15; i++ )
				{
					strike = new Grim_Reaper_Strike(the_grim_reaper, 0, 0, i/7);
					strikes_vector.push_back(strike);
				}
				al_play_sample(the_grim_reaper.audio_atack[2], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	
				the_grim_reaper.world_end_attack = false;
			}	

		}
		else if(the_grim_reaper.STATE == ELIMINATE)
		{
			if(!the_grim_reaper.frameCount[ELIMINATE])
				al_play_sample(the_grim_reaper.audio_atack[2], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

			if(the_grim_reaper.world_end_attack)
			{
				for(int i = 0; i < 32; i++)
				{

					strike = new Grim_Reaper_Strike(the_grim_reaper, i, 1, i%17/2.0);
					strikes_vector.push_back(strike);
				}	
				the_grim_reaper.world_end_attack = false;
			}
		}

		double player_x_real =  player.x - player.bound_x/2 + 25;
		double player_bound_x_real = player_x_real + player.bound_x - 45;
		double player_y_real = player.y - player.bound_x/2 + 25;
		double player_bound_y_real = player_y_real + player.bound_y - 45;

		al_draw_rectangle(player_x_real, player_y_real, player_bound_x_real, player_bound_y_real, al_map_rgb(255, 255, 255), 1);
		
		for(unsigned int i = 0; i < strikes_vector.size(); i++)
		{			
			if(!((player_x_real > strikes_vector[i]->x + strikes_vector[i]->bound_x) ||
				(player_y_real > strikes_vector[i]->y + strikes_vector[i]->bound_y) ||
				(strikes_vector[i]->x > player_bound_x_real) ||
				(strikes_vector[i]->y > player_bound_y_real)))
			{
				player.isAlive = false;
			}
		}
	
				

		////////////////		
		
		//DRAW
		player.draw();		
		
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE) || player.isAlive == false)
		{
			game_over = true;
		}
		
		if(!(player.life > 0))
			game_over = true;

		al_flip_display();
		al_rest(1/60);
	}

	for(int i = 0; Enemies.size() != 0; NULL)
	{
		delete Enemies[i];
		Enemies.erase(Enemies.begin()+i);
	}
}

#endif
