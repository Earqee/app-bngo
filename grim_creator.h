#ifndef GRIM_CREATOR_H
#define GRIM_CREATOR_H

#define REF 50
#define STARDARD_AUDIO_VOLUME 3.0, 0, 1.0
#define STANDARD_TEXT_POSITION player_x_real - 35, player_y_real + 335, ALLEGRO_ALIGN_CENTRE

void Grim_creator(Player &player, ALLEGRO_BITMAP* ground)
{
    al_stop_samples();

    bool game_over = false;
    The_Grim_Reaper the_grim_reaper;

    bool hello_death = true;

    Frame Laught[LAUGHTS];
    for(int i = 0; i < LAUGHTS; i++)
      Laught[i].Set_count_delay(20);

    int text_x_position[LAUGHTS];
    int text_y_position[LAUGHTS];

    Frame Haha(1000);

    fonte_arial = al_load_font("fonts/arial.ttf", 48, 0);
    ALLEGRO_FONT *boss_name = al_load_font("fonts/screen_font.ttf", 16, 0);
    ALLEGRO_SAMPLE *boss_music = al_load_sample("audio/grim/Bloodborne_Soundtrack_OST_-_Cleric_Beast.ogg");
    al_play_sample(boss_music, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    std::vector<Grim_Reaper_Strike*> strikes_vector;
    Grim_Reaper_Strike* strike;

    int HEALTH_BAR_X = DISPLAY_WIDTH - cam_x + 300;
    int HEALTH_BAR_BOUND_X = DISPLAY_WIDTH - cam_x + 400;
    int HEALTH_BAR_Y =  DISPLAY_HEIGHT - cam_y - 100;
    int HEALTH_BAR_BOUND_Y = DISPLAY_HEIGHT - cam_x - 80;

    double player_x_real = player.x - player.bound_x/2 + 25 -cam_x;
    double player_bound_x_real = player_x_real + player.bound_x - 45;
    double player_y_real = player.y - player.bound_x/2 + 25 - cam_y;
    double player_bound_y_real = player_y_real + player.bound_y - 45 ;

    double grim_x_real =  the_grim_reaper.x - the_grim_reaper.bound_x/2 + 20 - cam_x;
    double grim_bound_x_real = the_grim_reaper.x +the_grim_reaper.bound_x/2 - 20 - cam_x;
    double grim_y_real = the_grim_reaper.y - the_grim_reaper.bound_y/2 + 20 - cam_y;
    double grim_bound_y_real = the_grim_reaper.y + the_grim_reaper.bound_y/2 - 20 - cam_y;

    while(the_grim_reaper.life > 0 && !game_over && player.isAlive)
    {
      if(hello_death)
      {
        the_grim_reaper.x = player.x - 500 - cam_x;
        the_grim_reaper.y = player.y - 500 - cam_y;
        hello_death = false;
      }

      if(++Haha.frameCount > Haha.frameDelay)
      {
        Haha.resetFrameCount();
        al_play_sample(the_grim_reaper.audio_atack_haha, 4.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      }

      // Gets Input
  		ks_prev = keyboard_state;
  		al_get_keyboard_state(&keyboard_state);
  		al_get_mouse_state(&mouse_state);

      camera_update(player.x, player.y);

      player_x_real = player.x - player.bound_x/2 + 25 -cam_x;
      player_bound_x_real = player_x_real + player.bound_x - 45;
      player_y_real = player.y - player.bound_x/2 + 25 - cam_y;
      player_bound_y_real = player_y_real + player.bound_y - 45 ;

      grim_x_real =  the_grim_reaper.x - the_grim_reaper.bound_x/2 + 20 - cam_x;
      grim_bound_x_real = the_grim_reaper.x +the_grim_reaper.bound_x/2 - 20 - cam_x;
      grim_y_real = the_grim_reaper.y - the_grim_reaper.bound_y/2 + 20 - cam_y;
      grim_bound_y_real = the_grim_reaper.y + the_grim_reaper.bound_y/2 - 20 - cam_y;

      //Draw background
      for(int i = ((int)(cam_x/GROUND_TILE_SIZE))*GROUND_TILE_SIZE-GROUND_TILE_SIZE;i < cam_x+DISPLAY_WIDTH+GROUND_TILE_SIZE;i += GROUND_TILE_SIZE)
      {
        for(int j = ((int)(cam_y/GROUND_TILE_SIZE))*GROUND_TILE_SIZE-GROUND_TILE_SIZE;j < cam_y +DISPLAY_HEIGHT;j += GROUND_TILE_SIZE)
        {
          al_draw_bitmap(ground,i-cam_x,j-cam_y,0);
        }
      }

      //AQUI
      al_draw_text(boss_name, al_map_rgb(255, 255, 255), 65 + player_x_real - (500)*(the_grim_reaper.life/300.00), player_y_real + 285, ALLEGRO_ALIGN_CENTRE, "The Grim Reaper");
      al_draw_filled_rectangle(player_x_real - (500)*(the_grim_reaper.life/300.00), player_y_real + 310, player_bound_x_real + 500*(the_grim_reaper.life/300.00), player_bound_y_real + 330, al_map_rgb(255, 0, 0));

      for(int i = 0;i < bullet_vector.size();i++)
      {
        if(bullet_vector[i]->x - cam_x> grim_x_real && bullet_vector[i]->x + bullet_vector[i]->bound_x - cam_x < grim_bound_x_real &&
           bullet_vector[i]->y - cam_y> grim_y_real && bullet_vector[i]->y + bullet_vector[i]->bound_y - cam_y< grim_bound_y_real)
        {
          delete bullet_vector[i];
          bullet_vector.erase(bullet_vector.begin() + i);
          if(the_grim_reaper.STATE == NORMAL)
          {
            the_grim_reaper.life--;
            al_draw_filled_rectangle(player_x_real - (500)*(the_grim_reaper.life/300.00), player_y_real + 310, player_bound_x_real + 500*(the_grim_reaper.life/300.00), player_bound_y_real + 330, al_map_rgb(255, 255, 255));
          }
         
        }
        else
        {
          bullet_vector[i]->update();
          bullet_vector[i]->draw();          
      
        }
      }

      for(int i = 0; i < strikes_vector.size(); i++)
      {
        strikes_vector[i]->draw();
        strikes_vector[i]->update();
      }

      ////////////////////////// Grim UPDATE  

      player.update();
  		the_grim_reaper.move(player);


      if(the_grim_reaper.destroyStrikes)
      {
        for(int i = 0; i < strikes_vector.size(); i++)
        {
          delete strikes_vector[i];
          strikes_vector.erase(strikes_vector.begin() + i);
        }
        the_grim_reaper.destroyStrikes = false;
      }

  		if(the_grim_reaper.STATE != MERGE && the_grim_reaper.STATE != ELIMINATE)
  		{
       the_grim_reaper.draw();

  			if(the_grim_reaper.STATE == SENTENTIATE)
  			{
          cam_shake = true;
  				for(int i = 0; i < LAUGHTS; i++)
  				{
  					if(++Laught[i].frameCount > Laught[i].frameDelay)
  					{
  						Laught[i].resetFrameCount();

  						text_x_position[i] = rand()%(DISPLAY_WIDTH - 200) - cam_x;
  						text_y_position[i] = rand()%(DISPLAY_HEIGHT - 80) - cam_y;
  					}

  					al_draw_text(fonte_arial, al_map_rgb(255, 255, 255), text_x_position[i], text_y_position[i],  ALLEGRO_ALIGN_CENTRE,
  			   			"HAHA");
          }
          al_draw_text(fonte_arial, al_map_rgb(255, 255, 255), STANDARD_TEXT_POSITION, "...And STAY DOWN!");
          
          if(the_grim_reaper.world_end_attack)
          {
            for(int i = 0; i < 32; i++)
            {
              strike = new Grim_Reaper_Strike(the_grim_reaper, i, 1, i%17/2.0);
              strikes_vector.push_back(strike);
            }
            the_grim_reaper.world_end_attack = false;
            al_play_sample(the_grim_reaper.audio_atack[3], STARDARD_AUDIO_VOLUME, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
  			}
        else if(the_grim_reaper.STATE == RECONSTRUCTION)
        {
          al_draw_text(fonte_arial, al_map_rgb(255, 255, 255), 400 + 65 + player_x_real - 500, - REF - 25 + player_y_real + 310, ALLEGRO_ALIGN_CENTRE, "Aren't you supposed to be dead?");
          if(the_grim_reaper.world_end_attack)
          {
            al_play_sample(the_grim_reaper.audio_atack[0], STARDARD_AUDIO_VOLUME, ALLEGRO_PLAYMODE_ONCE, NULL);
            the_grim_reaper.world_end_attack = false;
          }
        }
  		}
  		else if(the_grim_reaper.STATE == MERGE)
  		{
        cam_shake = true;
        al_draw_text(fonte_arial, al_map_rgb(255, 255, 255), STANDARD_TEXT_POSITION, "I didn't start this war but I'm damn well gonna finish it.");
          
  			if(the_grim_reaper.world_end_attack)
  			{
  				for(int i = 0; i < 90; i++ )
  				{
  				  strike = new Grim_Reaper_Strike(the_grim_reaper, 0, 0, i/30);
  					strikes_vector.push_back(strike);
  				}
          al_play_sample(the_grim_reaper.audio_atack[2], STARDARD_AUDIO_VOLUME, ALLEGRO_PLAYMODE_ONCE, NULL);
  				the_grim_reaper.world_end_attack = false;
  			}
  		}
  		else if(the_grim_reaper.STATE == ELIMINATE)
  		{
        
        cam_shake = true;
        al_draw_text(fonte_arial, al_map_rgb(255, 255, 255), STANDARD_TEXT_POSITION, "Always too overconfident..");
        
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

    	int E = 500;

      //al_draw_rectangle(player_x_real, player_y_real, player_bound_x_real, player_bound_y_real, al_map_rgb(255, 255, 0), 1);

      for(unsigned int i = 0; i < strikes_vector.size(); i++)
  		{
        
  			if(strikes_vector[i]->x > DISPLAY_WIDTH + cam_x + E || strikes_vector[i]->x < cam_x - E ||
          strikes_vector[i]->y > DISPLAY_HEIGHT + cam_y + E || strikes_vector[i]->y < cam_y - E)
        {
          delete strikes_vector[i];
          strikes_vector.erase(strikes_vector.begin() + i);
        }


        if(player_x_real > strikes_vector[i]->x - cam_x && player_bound_x_real < strikes_vector[i]->x + strikes_vector[i]->bound_x - cam_x &&
          player_y_real > strikes_vector[i]->y - cam_y && player_bound_y_real < strikes_vector[i]->y + strikes_vector[i]->bound_y - cam_y)
        {
          player.isAlive =  false;
          break;
        }
      }

      ////////////////////////

      // Bullet update

      reset_camera();

      if(al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE))
  		{
  			game_over = true;
        break;
  		}

      al_flip_display();
      al_rest(1.0/75);
    }

    player.life = 0;
    player.isAlive = false;
    game_over = true;
    playerDeath();
    return;
}

#endif
