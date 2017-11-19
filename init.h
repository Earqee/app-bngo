#ifndef INIT_H
#define INIT_H

ALLEGRO_DISPLAY* display;

ALLEGRO_MOUSE_STATE mouse_state;
ALLEGRO_KEYBOARD_STATE keyboard_state,ks_prev;

//Player Death
bool player_dead = false;

// Camera settings
double cam_x = 0, cam_y = 0;
double prev_cam_x, prev_cam_y;
bool cam_shake = false;
bool cam_fixed = false;
Frame cam_shake_timer(70);

int initialize(void)
{
	if(!al_init()) return 0;
	al_init_font_addon();
	if(!al_init_image_addon()) return 0;
	if(!al_init_ttf_addon()) return 0;
	if(!al_install_audio()) return 0;
	if(!al_init_acodec_addon()) return  0;
	al_reserve_samples(40);
	al_init_primitives_addon();
	al_install_mouse();
	al_install_keyboard();

	return 1;
}

#endif
