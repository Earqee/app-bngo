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
    bound_x = 64;
    bound_y = 64;
    
    direction = 0;
    speed = 2;
    life = 3;
    
}

void Enemy_follower::update(Player &player)
{
    direction = angle(x,y,player.x,player.y) + PI;
    
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
    al_draw_rotated_bitmap(image,bound_x/2,bound_y/2,x,y,direction,0);
}

void Enemy_follower::move()
{
    x += speed*cos(direction);
    y += speed*sin(direction);
}

#endif
