#ifndef BULLET_CRAB_H
#define BULLET_CRAB_H

class Bullet_crab : public Walker
{
public:

	Bullet_crab(double crab_x, double crab_y, double crab_bound, double water_projectile_direction);
	Bullet_crab(Bullet_crab *water_projectile_copy, double crab_x, double crab_y, double crab_bound, double water_projectile_direction, double angle_increment);

	int state;
	double bullet_angle;
	Frame impact_timer;


	void update(Player &player);
	void launched(Player &player);
	void impact();
	bool player_water_collision(Player &player);
	void draw();
};

Bullet_crab::Bullet_crab(double crab_x, double crab_y, double crab_bound, double water_projectile_direction)
{
	bound_x = 48;
	bound_y = 48;

  x = crab_x;
  y = crab_y + crab_bound/2;

  direction = water_projectile_direction;

	speed = 10;
	state = LAUNCHED;

  //ANIMATION SETTINGS
  animation_quantity = 2;
	current_animation = LAUNCHED;
	current_frame = 0;

	frames_quantity[LAUNCHED] = 6;
	frames_quantity[IMPACT] = 2;

	impact_timer.frameDelay = 30;
	impact_timer.frameCount = 0;

	char nome_sprite[] = "images/CRAB/crab_attack/0-0.png";

  for(int i = 0;i < animation_quantity; i++)
  {
      for(int j = 0;j < frames_quantity[i]; j++)
	    {
          nome_sprite[24] = i + '0';
          nome_sprite[26] = j + '0';

          sprites[i][j] = al_load_bitmap(nome_sprite);
      }
  }
}

//copy or the bullets
Bullet_crab::Bullet_crab(Bullet_crab *water_projectile_copy, double crab_x, double crab_y, double crab_bound, double water_projectile_direction, double angle_increment)
{
	bound_x = water_projectile_copy -> bound_x;
	bound_y = water_projectile_copy -> bound_y;

  x = crab_x;
  y = crab_y + crab_bound/2;

  direction = water_projectile_direction;

	speed = water_projectile_copy -> speed;

	state = water_projectile_copy -> state;

	impact_timer.frameDelay = water_projectile_copy -> impact_timer.frameDelay;
	impact_timer.frameCount = water_projectile_copy -> impact_timer.frameCount;

	bullet_angle = angle_increment;

  //ANIMATION SETTINGS
  animation_quantity = water_projectile_copy -> animation_quantity;
	current_animation = water_projectile_copy -> current_animation;
	current_frame = water_projectile_copy -> current_frame;

	frames_quantity[LAUNCHED] = water_projectile_copy -> frames_quantity[LAUNCHED];
	frames_quantity[IMPACT] = water_projectile_copy   -> frames_quantity[IMPACT];

  for(int i = 0;i < animation_quantity; i++)
  {
      for(int j = 0;j < frames_quantity[i]; j++)
	    {
				sprites[i][j] = water_projectile_copy -> sprites[i][j];
      }
  }
}

void Bullet_crab::update(Player &player)
{
	switch (state)
	{
		case LAUNCHED:
		{
			launched(player);
		}
		break;
		case IMPACT:
		{
			impact();
		}
		break;
	}
}

void Bullet_crab::launched(Player &player)
{
	direction += deg_to_rad(bullet_angle);
	x += speed * cos(direction);
	y += speed * sin(direction);

	animate();

	if(player_water_collision(player))
	{
		state = IMPACT;
		current_frame = 0;
		frame_counter = 0;
		current_animation = IMPACT;

		//Player instant kill
		player.life -= 15;
		player.vulnerable = false;
	}
}

void Bullet_crab::impact()
{
	frame_counter+= 4;
	animate();
	impact_timer.frameCount++;
	if(impact_timer.frameCount > impact_timer.frameDelay)
	{
		state = DESTROYED;
	}
}

bool Bullet_crab::player_water_collision(Player &player)
{
  if(abs(x - player.x) < (bound_x+player.bound_x)/2 && abs(y - player.y) < (bound_y+player.bound_y)/2)
  {
    return true;
  }
  return false;
}

void Bullet_crab::draw()
{
	//al_draw_rectangle(x-bound_x/2-cam_x,y-bound_y/2-cam_y,x+bound_x/2-cam_x,y+bound_y/2-cam_y,al_map_rgb(255,0,0),1);
	al_draw_rotated_bitmap(sprites[current_animation][current_frame], 32, 32, x-cam_x, y-cam_y, direction, 0);
}

#endif
