#ifndef CRAB_CREATOR_H
#define CRAB_CREATOR_H

void Crab_creator(Player &player, ALLEGRO_BITMAP* ground)
{
    bool game_over = false;
    Crab Boss_Crabe;

    ALLEGRO_FONT *boss_name = al_load_font("fonts/screen_font.ttf", 16, 0);

    int HEALTH_BAR_X = DISPLAY_WIDTH/2;
    int HEALTH_BAR_BOUND_X = HEALTH_BAR_X;
    int HEALTH_BAR_Y =  DISPLAY_HEIGHT/2 + 300;
    int HEALTH_BAR_BOUND_Y = HEALTH_BAR_Y +7;

    while(Boss_Crabe.life > 0 && !game_over)
    {
      gets_input();
      camera_update(player.x, player.y);

      //Draw background
  		for(int i = ((int)(cam_x/GROUND_TILE_SIZE))*GROUND_TILE_SIZE-GROUND_TILE_SIZE;i < cam_x+DISPLAY_WIDTH+GROUND_TILE_SIZE;i += GROUND_TILE_SIZE)
  		{
  			for(int j = ((int)(cam_y/GROUND_TILE_SIZE))*GROUND_TILE_SIZE-GROUND_TILE_SIZE;j < cam_y +DISPLAY_HEIGHT;j += GROUND_TILE_SIZE)
  			{
  				al_draw_bitmap(ground,i-cam_x,j-cam_y,0);
  			}
  		}

      std::cout<< Boss_Crabe.life << std::endl;

      
      

      Boss_Crabe.update(player);

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



      // Bullet update
  		for(int i = 0;i < bullet_vector.size();i++)
  		{
  			bullet_vector[i]->update();
  			bullet_vector[i]->draw();
  		}

      reset_camera();

      if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE))
  		{
  			break;
  		}

      al_draw_text(boss_name, al_map_rgb(255, 255, 255), HEALTH_BAR_X - 500*(Boss_Crabe.life/250.00) + 140, HEALTH_BAR_Y - 20, ALLEGRO_ALIGN_CENTRE, "The Crab which killed Chuck Norris");
      if(Boss_Crabe.crab_bullet_collision2(player) && !Boss_Crabe.state)
      {
        al_draw_filled_rectangle(HEALTH_BAR_X - 500*(Boss_Crabe.life/250.00), HEALTH_BAR_Y, HEALTH_BAR_BOUND_X + 500*(Boss_Crabe.life/250.00), HEALTH_BAR_BOUND_Y, al_map_rgb(255, 255, 255));
      }
      else
      {
        al_draw_filled_rectangle(HEALTH_BAR_X - 500*(Boss_Crabe.life/250.00), HEALTH_BAR_Y, HEALTH_BAR_BOUND_X + 500*(Boss_Crabe.life/250.00), HEALTH_BAR_BOUND_Y, al_map_rgb(255, 0, 0));
      }

      al_flip_display();
	
		 al_rest(1.0/FPS);
    }

	if(game_over)
	{
		playerDeath();
	}

}

#endif
