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
	image = al_load_bitmap("images/kid_move_0001.png");

	current_audio = SHOT;
	audio[SHOT] = al_load_sample("audio/Space Gun 01.wav");
	shot_image = al_load_bitmap("images/laser.png");
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
	angle = getAngle(mouse_state.x, mouse_state.y, this->x, this->y);
	al_draw_rotated_bitmap(image, bound_x/2, bound_y/2, this->x, this->y , angle, 0);
}	

#endif

