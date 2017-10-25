#ifndef INIT_H
#define INIT_H

ALLEGRO_DISPLAY* display;
ALLEGRO_MOUSE_STATE mouse_state;
ALLEGRO_KEYBOARD_STATE keyboard_state;
double cam_x = 0,cam_y = 0;

int initialize(void)
{
	if(!al_init()) return 0;
	if(!al_init_font_addon()) return 0;
	if(!al_init_image_addon()) return 0;
	if(!al_init_ttf_addon()) return 0;
	if(!al_install_audio()) return 0;
	if(!al_init_acodec_addon()) return  0;
	al_init_primitives_addon();
	al_install_mouse();
	al_install_keyboard();

	return 1;
}

#endif