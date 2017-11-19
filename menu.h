#ifndef MENU_H
#define MENU_H

void menu()
{
	//
	al_play_sample(menu_music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	//
	int m_c_state = 0;
	char option[4][20];
	strcpy(option[0], "INICIAR JOGO");
	strcpy(option[1], "TUTORIAL");
	strcpy(option[2], "AGRADECIMENTOS");
	strcpy(option[3], "SAIR");

	//
	Back_menu bit;
	ALLEGRO_BITMAP *mouse_icon = al_load_bitmap("images/mouseicon.png");
	ALLEGRO_BITMAP *wasd_icon = al_load_bitmap("images/wasdicon.png");

	//
	
	while(1)
	{
		gets_input();
		al_clear_to_color(BLACK);

		//
		al_draw_tinted_bitmap(bit.images[bit.current_image%bit.tam_images], al_map_rgb(bit.bit_counter, bit.bit_counter, bit.bit_counter), 0, 0, 0);
		//

		for (int i = 0; i < 4; i++) 
		{
			if(i == m_c_state)
			{
				al_draw_textf(screen_font[0], WHITE, DISPLAY_WIDTH/2, (1*DISPLAY_HEIGHT)/4 + i*100, ALLEGRO_ALIGN_CENTRE, "%s", option[i]);
			}
			else
			{
				al_draw_textf(screen_font[2], ORANGE, DISPLAY_WIDTH/2, (1*DISPLAY_HEIGHT)/4 + i*100, ALLEGRO_ALIGN_CENTRE, "%s", option[i]);
			}
		}

		//al_flip_display();
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_DOWN) && !al_key_down(&ks_prev, ALLEGRO_KEY_DOWN))
		{
			al_play_sample(change_sound, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			m_c_state++;
			m_c_state = (m_c_state%4 + 4)%4;
		}
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_UP) && !al_key_down(&ks_prev, ALLEGRO_KEY_UP))
		{
			al_play_sample(change_sound, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			m_c_state--;
			m_c_state = (m_c_state%4 + 4)%4;
		}
		if (al_key_down(&keyboard_state,ALLEGRO_KEY_ENTER) && !al_key_down(&ks_prev, ALLEGRO_KEY_ENTER))
		{
			if (m_c_state == 0)
			{
				al_stop_samples();
				al_play_sample(click_sound, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				main_game();				
				break;
			}
			if (m_c_state == 1)
			{
				//
				al_play_sample(click_sound, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				while(1)
				{
					gets_input();
					al_clear_to_color(BLACK);
					al_draw_bitmap(wasd_icon, 150, 300, 0);
					al_draw_textf(screen_font[2],WHITE, 20, 500, ALLEGRO_ALIGN_LEFT,"Utilize T para trocar de arma.");
					al_draw_textf(screen_font[2],WHITE, 20, 550, ALLEGRO_ALIGN_LEFT,"W, A, S e D movimentam o personagem.");
					al_draw_bitmap(mouse_icon, 550, 30, 0);
					al_draw_textf(screen_font[2],WHITE, 500, 300, ALLEGRO_ALIGN_LEFT,"Use o clique esquerdo");
					al_draw_textf(screen_font[2],WHITE, 500, 350, ALLEGRO_ALIGN_LEFT,"do mouse para atirar");
					al_draw_line(96,64,296,64,RED,15);
					al_draw_line(96,58,296,58,WHITE,4);
					al_draw_line(96,64,296,64,GREEN,15);
					al_draw_line(96,68,296,68,al_map_rgb(0,100,0),4);
					al_draw_textf(screen_font[2],WHITE, 20, 85, ALLEGRO_ALIGN_LEFT,"Sua vida fica no");
					al_draw_textf(screen_font[2],WHITE, 20, 135, ALLEGRO_ALIGN_LEFT,"lado superior esquerdo");
					al_draw_textf(screen_font[1], WHITE, DISPLAY_WIDTH - 32, 32, ALLEGRO_ALIGN_RIGHT, "SCORE: 123");
					al_draw_textf(screen_font[1], WHITE, DISPLAY_WIDTH - 32, 82, ALLEGRO_ALIGN_RIGHT, "Seus pontos ficam");
					al_draw_textf(screen_font[1], WHITE, DISPLAY_WIDTH - 32, 132, ALLEGRO_ALIGN_RIGHT, "no lado superior direito.");
					al_draw_scaled_rotated_bitmap(bit.animation[(++bit.frame_counter%60)/15], 32, 32, 1100, 450, 6.0, 6.0, -PI/2, 0);
					if (al_key_down(&keyboard_state,ALLEGRO_KEY_ENTER) && !al_key_down(&ks_prev, ALLEGRO_KEY_ENTER)) break;
					if (al_key_down(&keyboard_state,ALLEGRO_KEY_ESCAPE) && !al_key_down(&ks_prev, ALLEGRO_KEY_ESCAPE)) break;
					al_flip_display();
					al_rest(1.0/FPS);

				}
				//
			}
			if (m_c_state == 2)
			{
				al_play_sample(click_sound, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			}
			if (m_c_state == 3)
			{
				al_play_sample(click_sound, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				return;
			}
		}

		//
		if(bit.bit_counter == bit.bit_limit) bit.bit_increment = -1;
		if(bit.bit_counter == 0)
		{
			bit.bit_increment = 1;
			bit.current_image++;
		}
		bit.bit_counter += bit.bit_increment;
		//

		al_flip_display();
		al_rest(1.0/FPS);
	}
	//
	al_destroy_bitmap(mouse_icon);
	al_destroy_bitmap(wasd_icon);
	//
}

#endif
