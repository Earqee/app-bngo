#ifndef SNAKE_CREATOR_H
#define SNAKE_CREATOR_H

void Snake_creator(Player &player, ALLEGRO_BITMAP* ground)
{
    bool game_over = false;
    Snake Boss_Snake;

    double init_lenght = Boss_Snake.length;

    int HEALTH_BAR_X = DISPLAY_WIDTH/2 - 600 - cam_x;
    int HEALTH_BAR_BOUND_X = HEALTH_BAR_X + 900;
    int HEALTH_BAR_Y =  DISPLAY_HEIGHT/2  - cam_y;
    int HEALTH_BAR_BOUND_Y = HEALTH_BAR_Y +7;

    ALLEGRO_FONT *boss_name = al_load_font("fonts/screen_font.ttf", 16, 0);
	
	while(Boss_Snake.nodes[0].life > 0 && !game_over)
	{


      // Gets Input
  		ks_prev = keyboard_state;
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

  		
      Boss_Snake.update(player);

      // Player update
  		if(player.life > 0)
  		{
  			player.update();
  		}
  		else
  		{
  			player.isAlive = false;
  			game_over = true;
  		}

		camera_update(player.x, player.y);
      
		// Bullet update
  		for(int i = 0;i < bullet_vector.size();i++)
  		{
  			bullet_vector[i]->update();
  			bullet_vector[i]->draw();
  		}

		al_flip_display();
	
		al_rest(1.0/FPS);
	  
    }

	if(game_over)
	{
		playerDeath();
	}
	else if(Boss_Snake.state == DEAD_SNAKE)
	{
		cam_x = Boss_Snake.nodes[0].x - DISPLAY_WIDTH/2;		//Foca a camera na cabeca da cobra
		cam_y = Boss_Snake.nodes[0].y - DISPLAY_HEIGHT/2;

		player.score += 2000;

		for(int i = 0;i < 3*60;i++)
		{
			al_clear_to_color(BLACK);

			Boss_Snake.nodes[0].direction += deg_to_rad(10);	//O fundo fica preto e cabeca fica rodando por 3 segundos

			Boss_Snake.nodes[0].draw();

			player.draw();

			al_flip_display();
			al_rest(1.0/FPS);
		}

		for(int i = 0;i < 1000;i += 2)
		{
			cam_shake = true;

			al_clear_to_color(BLACK);

			Boss_Snake.nodes[0].draw();						//Desenha um circulo com o raio crescendo, como se fosse uma explosao 
			
			player.draw();

			al_draw_filled_circle(Boss_Snake.nodes[0].x - cam_x,Boss_Snake.nodes[0].y - cam_y,i,WHITE);

			al_flip_display();
			al_rest(1.0/FPS);
		}

		cam_x = player.x - DISPLAY_WIDTH/2;			//Foca a camera no jogador
		cam_y = player.y - DISPLAY_HEIGHT/2;

		   
	}
}

#endif
