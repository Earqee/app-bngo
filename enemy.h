#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Walker
{
public:
	bool vulnerable;
	int state;
	ALLEGRO_SAMPLE* shot_audio;

	Enemy();
	
	virtual void update(Player &player) = 0;
	virtual void draw() = 0;
	void damage();
	int bullet_collision();
	int enemy_collision();
	int player_collision(Player &player);
};

//Enemies vector
std::vector <Enemy*> Enemies;

Enemy::Enemy()
{
	vulnerable = true;
	bound_x = 64;
	bound_y = 64;
	
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
		if(abs(x - bullet_vector[i]->x) < bound_x/2 + bullet_vector[i]->bound_x/2 
		  && abs(y - bullet_vector[i]->y) < bound_y/2 + bullet_vector[i]->bound_y/2)
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
	double x_linha = x + speed*cos(direction);
	double y_linha = y + speed*sin(direction);
	
	al_draw_rectangle(x_linha - cam_x - bound_x/2, y_linha - cam_y - bound_y/2, x_linha + bound_x/2 - cam_x, y_linha + bound_y/2 - cam_y, al_map_rgb(0, 0, 0), 5);

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

int Enemy::player_collision(Player &player)
{
	double x_linha = x;
	double y_linha = y;
	
	if(abs(x_linha - player.x) < bound_x/2 + player.bound_x/2 && abs(y_linha - player.y) < bound_y/2 + player.bound_y/2)
	{
		return 1;
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
