#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Walker
{
public:
	bool vulnerable;
	int state;

	Enemy();
	
	virtual void update(Player &player) = 0;
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
	
	x = rand()%4000;
	y = rand()%4000;
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
			al_draw_tinted_rotated_bitmap(sprites[current_animation][current_frame], al_map_rgb(255,0,0), bound_x/2,bound_y/2,x-cam_x,y-cam_y,direction,0);
			return 1;
		}
	}
	al_draw_rotated_bitmap(sprites[current_animation][current_frame],bound_x/2,bound_y/2,x-cam_x,y-cam_y,direction,0);
	
	return 0;
}


int Enemy::enemy_collision()
{
	double x_linha = x + speed*cos(direction);
	double y_linha = y + speed*sin(direction);	

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
		life--;
	}
}

#endif
