#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Walker
{
public:
	int type;
	int state;
	int shotTime;
	int shotDelay;

	Enemy(int type, int shotDelay);

 	void move(Player &player);
	void round(Player &player);
	GENERIC_FUNCTION void draw(Generic &generic, bool colliding);	
};

Enemy::Enemy(int type, int shotDelay)
{
	this->type = type;

	this->shotTime = 0;
	this->shotDelay = shotDelay;
	
	isAlive = true;
	state = MOVE;

	if(rand()%2)
	{
		if(rand()%2)
		{
			x = rand() % WINDOW_WIDTH;
			y = - LIMIT;
		}
		else
		{
			x = rand() % WINDOW_WIDTH; 
			y = WINDOW_HEIGHT + LIMIT;
		}		
	}
	else
	{
		if(rand()%2)
		{
			x = - LIMIT ;
			y = rand() % WINDOW_HEIGHT;
		}
		else
		{
			x =	WINDOW_WIDTH + LIMIT; 
			y = rand() % WINDOW_HEIGHT;
		}	
	}	
	
	switch(type)
	{
		case ASSAULT:
		{
			image = al_load_bitmap("images/assault.png");
			shot_audio = al_load_sample("audio/Space Gun 04.wav");
			shot_image = al_load_bitmap("images/laser3.png");
			bound_x = 110;
			bound_y = 110;	
			life = 100;
			speed = DEFAULT/1.5;
			break;
		}
		case SCOUT:
		{
			image = al_load_bitmap("images/scout.png");
			shot_audio = al_load_sample("audio/Space Gun 03.wav");
			shot_image = al_load_bitmap("images/laser2.png");
			bound_x = 110;
			bound_y = 110;
			life = 100;
			speed = DEFAULT/1.5;
			break;
		}
		case SUPPORT:
		{
			image = al_load_bitmap("images/mutant.png");
			shot_audio = al_load_sample("audio/Space Gun 12.wav");
			shot_image = al_load_bitmap("images/laser1.png");
			bound_x = 110;
			bound_y = 110;
			life = 150;
			speed = DEFAULT/1.5;
			break;
		}
		case TECH:
		{
			image = al_load_bitmap("images/tech1.png");
			shot_audio = al_load_sample("audio/Space Gun 12.wav");
			shot_image = al_load_bitmap("images/laser1.png");
			bound_x = 124;
			bound_y = 124;
			life = 400;
			speed = DEFAULT/1.75;
			break;
		}
		case CANNONER:
		{
			image = al_load_bitmap("images/cannoner.png");
			shot_audio = al_load_sample("audio/Space Gun 15.wav");
			shot_image = al_load_bitmap("images/laser4.png");
			bound_x = 170;
			bound_y = 170;
			life = 600;	
			speed = DEFAULT/2.0;
			break;
		}
	}
}

GENERIC_FUNCTION
void Enemy::move(Generic &generic)
{
	angle = getAngle(generic.x, generic.y, this->x, this->y);

	director_x = cos(angle);
	director_y = sin(angle);

	if(!(abs(director_x) && abs(director_y)))
	{
		x += speed * director_x ;
		y += speed * director_y;
	}
	else
	{
		x += speed * director_x * RAIZ2SOBRE2;
		y += speed * director_y * RAIZ2SOBRE2;
	}

	if(abs(x - generic.x) < 250 && abs(y - generic.y) < 250)
	{
		state = ROUND;
	}
}


void Enemy::round(Player &player)
{
	angle = getAngle(generic.x, generic.y, this->x, this->y);

	x -= speed * cos(angle);
	y -= speed * cos(angle);

	if(abs(x - generic.x) < 200 || abs(y - generic.y) < 200)
		state = MOVE;	
}

void Enemy::update()
{
	if(!colliding)
	{
		switch(state)
		{
			case MOVE:
			move(generic);
			break;

			case ROUND:
			round(generic);
			break;
		}
	}
	else
	{
		angle = getAngle(generic.x, generic.y, this->x, this->y);
	}
}

void Enemy::draw(Generic &generic, bool colliding)
{
	al_draw_rotated_bitmap(image, bound_x/2, bound_y/2, this->x, this->y, angle, 0);
}	



#endif