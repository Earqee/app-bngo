#ifndef BULLET_H
#define BULLET_H

class Bullet : public Volatile
{
public:
	int type;

	Bullet(Bullet &bullet_base,Player &player);
	Bullet(){};
	~Bullet(){};
	
	void update();
	void draw();
};

Bullet::Bullet(Bullet &bullet_base,Player &player)
{
	this->x = player.x;
	this->y = player.y;
	this->direction = player.angle;

	bound_x = 8;
	bound_y = 8;

	speed = 10;

	image = player.shot_image;
}

void Bullet::update()
{
	x += speed * cos(direction);
	y += speed * sin(direction);
}

void Bullet::draw()
{
	al_draw_rotated_bitmap(image, 32, 32, x-cam_x, y-cam_y, direction, 0);
}

#endif
