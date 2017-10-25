#ifndef ENEMY_FOLLOWER
#define ENEMY_FOLLOWER

class Enemy_follower : public Enemy
{
public:
    Enemy_follower();
    
    void move();
    
    void update(Player &player);
    void draw();
};




Enemy_follower::Enemy_follower()
{
    image = al_load_bitmap("images/assault.png");
    shot_audio = al_load_sample("audio/Space Gun 04.wav");
    shot_image = al_load_bitmap("images/laser3.png");
    bound_x = 110;
    bound_y = 110;	
    life = 100;
    speed = DEFAULT_SPEED/1.5;
}

void Enemy_follower::update(Player &player)
{
    direction = getAngle(x,y,player.x,player.y) + PI;
    
    damage();
    
    if(!enemy_collision())
    {
        move();
    }
    else
    {
        direction += deg_to_rad(90);
    }
    
    draw();
}

void Enemy_follower::draw()
{
al_draw_rectangle(this->x - cam_x, this->y - cam_y, x + bound_x - cam_x, y + bound_y - cam_y, al_map_rgb(0, 0, 0), 5);
    al_draw_rotated_bitmap(image,bound_x/2,bound_y/2,x-cam_x,y-cam_y,direction,0);
}

void Enemy_follower::move()
{
    x += speed*cos(direction);
    y += speed*sin(direction);
}

#endif
