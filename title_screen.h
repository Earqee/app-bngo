#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

void title_screen()
{
  Frame flash(35);
  bool printText = true;

  ALLEGRO_COLOR normal_font = ORANGE;
  ALLEGRO_COLOR highlight_font = YELLOW;

  ALLEGRO_BITMAP* logo = al_load_bitmap("images/logo.png");

  screen_font[0] = al_load_font("fonts/screen_font.ttf", 48, 0);
  screen_font[1] = al_load_font("fonts/screen_font.ttf", 30, 0);
  screen_font[2] = al_load_font("fonts/screen_font.ttf", 40, 0);

  click_sound = al_load_sample("audio/menu/negative_2.wav");
  change_sound = al_load_sample("audio/menu/misc_menu.wav");

  for(int i = 0;i < 255; i += 2)
  {
	  al_clear_to_color(BLACK);

	  al_draw_tinted_bitmap(logo,al_map_rgba(i,i,i,i),0,0,0);
	  
	  al_flip_display();
	  al_rest(1.0/FPS);
  }

  while(!false)
  {
    al_clear_to_color(BLACK);
	  al_draw_bitmap(logo,0,0,0);

    gets_input();
    if(++flash.frameCount > flash.frameDelay)
    {
      flash.resetFrameCount();
      printText = !printText;
    }
    if(printText)
    {
      al_draw_textf(screen_font[0], WHITE, DISPLAY_WIDTH/2, (3*DISPLAY_HEIGHT)/4, ALLEGRO_ALIGN_CENTRE, "PRESSIONE ENTER");
      al_draw_textf(screen_font[1], WHITE, DISPLAY_WIDTH/2, (3*DISPLAY_HEIGHT)/4+60, ALLEGRO_ALIGN_CENTRE, "(ESC PARA SAIR)");
    }
    if(al_key_down(&keyboard_state, ALLEGRO_KEY_ENTER) && !al_key_down(&ks_prev, ALLEGRO_KEY_ENTER))
    {
      al_play_sample(click_sound, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      menu();
      al_stop_samples();
    }
    else if(al_key_down(&keyboard_state, ALLEGRO_KEY_ESCAPE) && !al_key_down(&ks_prev, ALLEGRO_KEY_ESCAPE))
    {
      break;
    }

    al_flip_display();
    al_rest(1.0/FPS);
  }
}


#endif
