#ifndef PLAYER_H
#define PLAYER_H

class Player : public Walker
{
public:
	Player();

	void move();
	void draw();
};

Player::Player()
{
	x = 500;
	y = 50;
	director_x = 0;
	director_y = 0;
	bound_x = 64;
	bound_y = 64;
	speed = DEFAULT_SPEED;
	life = 100;
	isAlive = true;
	image = al_load_bitmap("SUBSTITUA AQUI");

	current_audio = SHOT;
	audio[SHOT] = al_load_sample("SUBSTITUA AQUI");
	shot_image = al_load_bitmap("SUBSTITUA AQUI ");
}

void Player::move()
{
	director_x = al_key_down(&keyboard_state, ALLEGRO_KEY_D) - al_key_down(&keyboard_state, ALLEGRO_KEY_A);
	director_y = al_key_down(&keyboard_state, ALLEGRO_KEY_S) - al_key_down(&keyboard_state, ALLEGRO_KEY_W); 

	direction = getAngle(director_x,director_y);

	if(director_x || director_y)
	{
		x += speed * cos(direction);
		y += speed * sin(direction);
	}
}

void Player::draw()
{
	angle = getAngle(mouse_state.x+cam_x, mouse_state.y+cam_y, this->x, this->y);
	al_draw_rotated_bitmap(image, bound_x/2, bound_y/2, this->x-cam_x, this->y-cam_y, angle, 0);
}	

#endif

