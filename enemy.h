#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Walker
{
public:
	bool vulnerable;

	Enemy();
	
	void damage();
	int bullet_collision();
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

void Enemy::damage()
{
	if(bullet_collision() && vulnerable = true)
	{
		health--;
	}
}

#endif
