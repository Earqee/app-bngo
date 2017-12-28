#ifndef BASIC_FUNCTIONS_H
#define BASIC_FUNCTIONS_H

inline double getAngle(double x1, double y1, double x2 = 0, double y2 = 0)
{
	return atan2(y1-y2, x1-x2);
}

inline double deg_to_rad(double angle)
{
	return (PI*angle)/180;
}

inline double rad_to_deg(double angle)
{
	return (180*angle)/PI;
}

inline double dist_point(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

inline void gets_input()
{
	ks_prev = keyboard_state;
	al_get_keyboard_state(&keyboard_state);
	al_get_mouse_state(&mouse_state);
}

void playerDeath()
{
	std::cout << "vida:";
	int s_f_delay = 0;
	al_stop_samples();
	al_play_sample(sefudeu_music, 1, 	0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	double a = PI/3;
	double posx = (rand()%DISPLAY_WIDTH)*1.0;
	double posy = (rand()%DISPLAY_HEIGHT)*1.0;
	int flag_x = 5;
	int flag_y = 5;
	while(1)
	{
		gets_input();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_textf(screen_font[0], RED, posx, posy, ALLEGRO_ALIGN_CENTRE, "FIM DE JOGO ;(");
		posx += flag_x*cos(a);
		posy += flag_y*sin(a);
		if(posx < 0+170 || posx > DISPLAY_WIDTH-170) flag_x *= -1;
		if(posy < 0 || posy > DISPLAY_HEIGHT-60) flag_y *= -1;
		if(al_key_down(&keyboard_state,ALLEGRO_KEY_ENTER) && !al_key_down(&ks_prev,ALLEGRO_KEY_ENTER))
		{
			break;
		}
		al_flip_display();
		al_rest(1.0/FPS);
	}

	player_dead = true;
}

void camera_update(double player_x, double player_y)
{
	if(cam_fixed == false)
	{
		cam_x = player_x - DISPLAY_WIDTH/2;
		cam_y = player_y - DISPLAY_HEIGHT/2;
	}
	if(!cam_shake)
	{
		prev_cam_x = cam_x;
		prev_cam_y = cam_y;
	}
	else
	{
		cam_x += rand()%10 - 5;
		cam_y += rand()%10 - 5;

		cam_shake_timer.frameCount++;

		if(cam_shake_timer.frameCount == cam_shake_timer.frameDelay)
		{
			cam_shake_timer.resetFrameCount();
			cam_shake = 0;
		}
	}
}

inline void reset_camera()
{
	cam_x = prev_cam_x;
	cam_y = prev_cam_y;
}

#endif
