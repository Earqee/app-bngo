#ifndef ENEMY_SUPPORT
#define ENEMY_SUPPORT

class Enemy_support : public Enemy
{
public:
    Enemy_support();
    
    void move();
    void update(Player &player);
    void draw();
};

Enemy_support::Enemy_support()
{
    image = al_load_bitmap("images/support.png");
	shot_audio = al_load_sample("audio/Space Gun 12.wav");
	shot_image = al_load_bitmap("images/laser1.png");
	bound_x = 110;
	bound_y = 110;
	speed = DEFAULT_SPEED/1.5;
}

void Enemy_support::update(Player &player)
{
    direction = getAngle(x,y,player.x,player.y) + PI;
    
    damage();
    
    if(!enemy_collision() && rand()%100 < 35)   //Se não tiver coliosao com outro inimigo, há 35% de chance de movimento
    {
        move();
    }
    
    
    draw();
}

void Enemy_support::draw()
{
    al_draw_rectangle(this->x - cam_x, this->y - cam_y, x + bound_x - cam_x, y + bound_y - cam_y, al_map_rgb(0, 0, 0), 5);
    al_draw_rotated_bitmap(image,bound_x/2,bound_y/2,x-cam_x,y-cam_y,direction,0);
}

void Enemy_support::move()
{
    x += speed*cos(direction);
    y += speed*sin(direction);
}

#endif
