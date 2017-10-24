#ifndef BULLET_H
#define BULLET_H

class Bullet : public Volatile
{
public:
	int type;

	Bullet(Bullet &bullet_base,Player &player);
	Bullet(){};
	~Bullet(){};
	
	void draw();
};

Bullet::Bullet(Bullet &bullet_base,Player &player)
{
	this->x = player.x;
	this->y = player.y;
	this->direction = player.direction;

	bound_x = 8;
	bound_y = 8;

	speed = 10;

	image = player.shot_image;
}


void Bullet::draw()
{
	x += speed * cos(direction);
	y += speed * sin(direction);

	al_draw_rotated_bitmap(image, 0, 0, x, y, direction, 0);
}

#endif