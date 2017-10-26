#ifndef BULLET_H
#define BULLET_H

class Bullet : public Walker
{
public:
	int type;

	Bullet(Bullet &bullet_base,Player &player);
	Bullet(){};
	~Bullet(){};
	
	void update();
	void draw();
};

std::vector<Bullet*>bullet_vector;

Bullet::Bullet(Bullet &bullet_base,Player &player)
{
	this->x = player.x;
	this->y = player.y;
	this->direction = player.angle;

	bound_x = 8;
	bound_y = 8;

	speed = 10;

	current_animation = 0;
	current_frame = 0;

	sprites[0][0] = al_load_bitmap("images/shot00/flashA1.png");
}

void Bullet::update()
{
	x += speed * cos(direction);
	y += speed * sin(direction);
}

void Bullet::draw()
{
	al_draw_rotated_bitmap(sprites[current_animation][current_frame], 32, 32, x-cam_x, y-cam_y, direction, 0);
}

#endif
