#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Walker
{
public:
	bool vulnerable;

	Enemy();
	
	void damage();
	int bullet_collision();
	int enemy_collision();
};

Enemy::Enemy()
{
	vulnerable = true;
	
	switch(rand()%4)
	{
		case 0:						//lado superior da tela
			{
				x = rand()%DISPLAY_WIDTH;
				y = 0 - 96;
			}
			break;
		case 1:
			{
				x = rand()%DISPLAY_WIDTH;
				y = DISLPLAY_HEIGHT + 96;
			}
			break;
		case 2:
			{
				x = 0 - 96;
				y = rand()%DISPLAY_HEIGHT;
			}
		case 3:
			{
				x = DISPLAY_WIDTH + 96;
				y = rand()%DISPLAY_HEIGHT;
			}
	}
}

int Enemy::bullet_collision()
{
	for(unsigned int i = 0;i < bullet_vector.size();i++)
	{
		if(x - bullet_vector[i].x < bound_x/2 + bullet_vector[i].bound_x/2 
		  && y - bullet_vector[i].y < bound_y/2 + bullet_vector[i].bound_y/2)
		{
			return 1;
		}
	}
	
	return 0;
}


int Enemy::enemy_collision()
{
	double x_linha = x + bound_x/2*speed*cos(direction)/2;
	double y_linha = y + bound_y/2*speed*sin(direction)/2;
	
	for(unsigned int i = 0;i < Enemies.size();i++)
	{
		if(x != Enemies[i]->x && y != Enemies[i]->y)
		{
			if(abs(x_linha - Enemies[i]->x) < bound_x/2 + Enemies[i]->bound_x/2 && abs(y_linha - Enemies[i]->y) < bound_y/2 + Enemies[i]->bound_y/2)
			{
				return 1;
			}
		}		
	}
	return 0;
}

void Enemy::damage()
{
	if(bullet_collision() && vulnerable = true)
	{
		health--;
	}
}

#endif
