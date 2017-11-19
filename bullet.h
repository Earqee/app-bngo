#ifndef BULLET_H
#define BULLET_H

class Bullet : public Walker
{
public:
	int type;

	Bullet(Bullet *bullet_base,double player_x,double player_y,
		 		 double player_angle, int bullet);

	Bullet();
	~Bullet(){};

	void update();
	void draw();
};

std::vector<Bullet*>bullet_vector;

Bullet::Bullet()
{
	bound_x = 8;
	bound_y = 8;

	speed = 10;

	current_animation = 0;
	current_frame = 0;

	sprites[0][0] = al_load_bitmap("images/shot00/flashA1.png");
}

Bullet::Bullet(Bullet *bullet_base,double player_x,double player_y,double player_angle,int bullet)
{
		this->x = player_x;
		this->y = player_y;
		this->direction = player_angle + (bullet * PI/9);

		bound_x = bullet_base->bound_x;
		bound_y = bullet_base->bound_y;

		speed = bullet_base->speed;

		current_animation = bullet_base->current_animation;
		current_frame = bullet_base->current_frame;

		sprites[0][0] = bullet_base->sprites[0][0];
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
