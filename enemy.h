#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Walker
{
public:
	bool vulnerable;
	ALLEGRO_SAMPLE* shot_audio;

	Enemy();
	
	virtual void update(Player &player) = 0;
	virtual void draw() = 0;
	void damage();
	int bullet_collision();
	int enemy_collision();
};

//Enemies vector
std::vector <Enemy*> Enemies;

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
				y = DISPLAY_HEIGHT + 96;
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
		if(x - bullet_vector[i]->x < bound_x/2 + bullet_vector[i]->bound_x/2 
		  && y - bullet_vector[i]->y < bound_y/2 + bullet_vector[i]->bound_y/2)
		{
			delete bullet_vector[i];
			bullet_vector.erase(bullet_vector.begin()+i);
			return 1;
		}
	}
	
	return 0;
}


int Enemy::enemy_collision()
{
	double x_linha = x + (bound_x/2)*speed*cos(direction);
	double y_linha = y + (bound_y/2)*speed*sin(direction);
	
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
	if(bullet_collision() && vulnerable == true)
	{
		life -= 20;
	}
}

#endif
