#ifndef PLAYER_H
#define PLAYER_H

class Player : public Walker
{
public:
	Player();
	~Player();
	int current_weapon;
	long int score;
	bool vulnerable;
	Frame Player_Shoot;
	Frame Player_hurt;
	ALLEGRO_SAMPLE* weapon_audio[MAX_WEAPONS];
	ALLEGRO_BITMAP* weapon_image[MAX_WEAPONS];
	ALLEGRO_BITMAP* fire_anim_bitmap[10];
	ALLEGRO_BITMAP* id;

	// Creates Bullets and copy for bullets
	Bullet* bullet;
	Bullet bullet_base;

	Frame fire_anim;
	int fire_anim_current;

	int move();
	void shoot();
	void update();
	void draw();
};

Player::~Player()
{

}

Player::Player()
{
	x = 500;
	y = 50;
	director_x = 0;
	director_y = 0;
	bound_x = 20;
	bound_y = 20;
	speed = DEFAULT_SPEED;
	life = 100;
	isAlive = true;
	Player_Shoot.Set_count_delay(5);
	Player_hurt.Set_count_delay(0.5*60);
	fire_anim.Set_count_delay(5);
	vulnerable = true;
	score = 0;

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




    char nome_sprite_2[] = "images/onfireanimation/onfire_0001.png";
    fire_anim_current = 0;

    for(int i = 0; i < 9; i++)
    {
    	nome_sprite_2[33] = i + 48 + 1; 
    	fire_anim_bitmap[i] = al_load_bitmap(nome_sprite_2);
    	std::cout << "Carreguei: " << nome_sprite_2 << std::endl;
    }


    //

	current_weapon = 0;

    //botei dois FOR aqui mas ficou muito pomposo, como são poucos deixarei assim
   	audio[DAMAGE] = al_load_sample("audio/player0-0.wav");
	audio[DEAD] = al_load_sample("audio/player0-1.wav");

	weapon_audio[MACHINEGUN] = al_load_sample("audio/machinegun.wav");
	weapon_audio[SHOTGUN] = al_load_sample("audio/shotgun.ogg");
	weapon_image[MACHINEGUN] = al_load_bitmap("images/held_weapons/0-0.png");
	weapon_image[SHOTGUN] = al_load_bitmap("images/held_weapons/0-1.png");

	shot_image = al_load_bitmap("images/ShotAnims/flashA1.png");

	

	id = al_load_bitmap("images/player/id.png");
}

void Player::update()
{
		if(move())
		{
			animate();
		}
		else
		{
			current_frame = 0;
		}
		if(vulnerable == false)
		{
				if(++Player_hurt.frameCount == Player_hurt.frameDelay)
				{
					vulnerable = true;
					Player_hurt.resetFrameCount();
				}
		}
		angle = getAngle(mouse_state.x+cam_x, mouse_state.y+cam_y, this->x, this->y);
		shoot();
		draw();
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

		if(x > cam_x + DISPLAY_WIDTH - bound_x/2)
		{
			x = cam_x + DISPLAY_WIDTH - bound_x/2;
		}
		if(x < cam_x + bound_x/2)
		{
			x = cam_x + bound_x/2;
		}
		if(y > cam_y + DISPLAY_HEIGHT - bound_y/2)
		{
			y = cam_y + DISPLAY_HEIGHT - bound_y/2;
		}
		if(y < cam_y + bound_y/2)
		{
			y = cam_y + bound_y/2;
		}
		return 1;
	}

	return 0;
}

void Player::shoot()
{
	//PLAYER SHOT
	if(al_key_down(&keyboard_state, ALLEGRO_KEY_T))
	{
		current_weapon = SHOTGUN;
	}
	if(al_key_down(&keyboard_state, ALLEGRO_KEY_R))
	{
		current_weapon = MACHINEGUN;
	}

	if(Player_Shoot.frameCount > 0)
	{
		Player_Shoot.frameCount--;
	}

	if((mouse_state.buttons & 1) && (!Player_Shoot.frameCount))
	{
		//cam_shake = 1;
		switch(current_weapon)
		{
			case MACHINEGUN:
			{
				Player_Shoot.frameDelay = 5;
				Player_Shoot.frameCount = Player_Shoot.frameDelay;
				bullet = new Bullet(&bullet_base,x,y,angle, 0);
				bullet_vector.push_back(bullet);
				Player_Shoot.frameCount = Player_Shoot.frameDelay;
				break;
			}
			case SHOTGUN:
			{
				Player_Shoot.frameDelay = 60;
				Player_Shoot.frameCount = Player_Shoot.frameDelay;
				for(int i = 0; i < 10; i++)
				{
					bullet = new Bullet(&bullet_base,x,y,angle, i-4);
					bullet_vector.push_back(bullet);
				}
				break;
			}
			default:
			break;
		}
		al_play_sample(weapon_audio[current_weapon], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

void Player::draw()
{
	al_draw_rectangle(x-bound_x/2-cam_x,y-bound_y/2-cam_y,x+bound_x/2-cam_x,y+bound_y/2-cam_y,al_map_rgb(0,0,0),-5);
	al_draw_rotated_bitmap(sprites[current_animation][current_frame], 32, 32, this->x-cam_x, this->y-cam_y, angle, 0);
	al_draw_rotated_bitmap(weapon_image[current_weapon], 32, 32, this->x-cam_x, this->y-cam_y, angle, 0);
	
	if(++fire_anim.frameCount > fire_anim.frameDelay)
	{
		fire_anim.frameCount = 0;
		fire_anim_current = (fire_anim_current + 1)%9;
	}

	al_draw_bitmap(fire_anim_bitmap[fire_anim_current], -15, 10, 0);

	
	al_draw_bitmap(id,32,32,0);

	al_draw_line(96,60,496,60,RED,10);

	al_draw_line(96,56,96+life*4.0,56,WHITE,4);
	al_draw_line(96,60,96+life*4.0,60,GREEN,8);
	al_draw_line(96,64,96+life*4.0,64,al_map_rgb(0,100,0),2);

	al_draw_textf(screen_font[1], WHITE, DISPLAY_WIDTH - 32, 32, ALLEGRO_ALIGN_RIGHT, "SCORE: %ld", score);
}

#endif
