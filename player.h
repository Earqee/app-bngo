#ifndef PLAYER_H
#define PLAYER_H

class Player : public Walker
{
public:
	Player();
	int current_weapon;
	ALLEGRO_SAMPLE* weapon_audio[MAX_WEAPONS];
	ALLEGRO_BITMAP* weapon_image[MAX_WEAPONS];

	
	int move();
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
	
	// Animation Settings
	char nome_sprite[] = "images/player/0-0.png";
	animation_quantity = 2;
	frames_quantity[WALKING_P] = 4;
	frames_quantity[IDLE_P] = 1;

	current_animation = WALKING_P;
	current_frame = 0;
    
    for(int i = 0;i < animation_quantity;i++)
    {
        for(int j = 0;j < frames_quantity[i];j++)
        {
            nome_sprite[14] = i + 48;
            nome_sprite[16] = j + 48;

            sprites[i][j] = al_load_bitmap(nome_sprite);
        }
    }

    //botei dois FOR aqui mas ficou muito pomposo, como são poucos deixarei assim
   	audio[DAMAGE] = al_load_sample("audio/player0-0.wav");
	audio[DEAD] = al_load_sample("audio/player0-1.wav");

	weapon_audio[MACHINEGUN] = al_load_sample("audio/machinegun.wav");
	weapon_audio[SHOTGUN] = al_load_sample("audio/shotgun.ogg");
	weapon_image[MACHINEGUN] = al_load_bitmap("images/held_weapons/0-0.png"); 
	weapon_image[SHOTGUN] = al_load_bitmap("images/held_weapons/0-1.png");
	
	shot_image = al_load_bitmap("images/ShotAnims/flashA1.png");
}

int Player::move()
{
	director_x = al_key_down(&keyboard_state, ALLEGRO_KEY_D) - al_key_down(&keyboard_state, ALLEGRO_KEY_A);
	director_y = al_key_down(&keyboard_state, ALLEGRO_KEY_S) - al_key_down(&keyboard_state, ALLEGRO_KEY_W); 

	direction = getAngle(director_x,director_y);

	if(director_x || director_y)
	{
		x += speed * cos(direction);
		y += speed * sin(direction);
		return 1;
	}

	return 0;
}

void Player::draw()
{
	if(move())
		animate();
	else
		current_frame = 0;

	angle = getAngle(mouse_state.x+cam_x, mouse_state.y+cam_y, this->x, this->y);
	al_draw_rotated_bitmap(sprites[current_animation][current_frame], bound_x/2, bound_y/2, this->x-cam_x, this->y-cam_y, angle, 0);	
	al_draw_rotated_bitmap(weapon_image[current_weapon], bound_x/2, bound_y/2, this->x-cam_x, this->y-cam_y, angle, 0);
}	

#endif

