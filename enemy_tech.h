#ifndef ENEMY_TECH
#define ENEMY_TECH

class Enemy_tech : public Enemy
{
public:
    Enemy_tech();
    
    void move();
    
    void update(Player &player);
    void draw();
};

Enemy_tech::Enemy_tech()
{
    image = al_load_bitmap("images/assault.png");
    shot_audio = al_load_sample("audio/Space Gun 04.wav");
    shot_image = al_load_bitmap("images/laser3.png");
    bound_x = 110;
    bound_y = 110;	
    life = 100;
    speed = DEFAULT/1.5;
}

void Enemy_tech::update(Player &player)
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

void Enemy_tech::draw()
{
    al_draw_rotated_bitmap(image,bound_x/2,bound_y/2,x,y,direction,0);
}

void Enemy_tech::move()
{
    x += speed*cos(direction);
    y += speed*sin(direction);
}

#endif
