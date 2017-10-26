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
    // Animation Settings
    char nome_sprite[] = "images/enemy0/dog000/0-0.png";
    animation_quantity = 2;
    frames_quantity[WALKING_E_SC] = 4;
    frames_quantity[IDLE_E_SC] = 1;
    current_animation = WALKING_E_SC;
    current_frame = 0;
    
    for(int i = 0;i < animation_quantity;i++)
    {
        for(int j = 0;j < frames_quantity[i];j++)
        {
            nome_sprite[21] = i + 48;
            nome_sprite[23] = j + 48;

            sprites[i][j] = al_load_bitmap(nome_sprite);
        }
    }
    
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
    
    draw();
}

void Enemy_follower::draw()
{
    al_draw_rectangle(this->x - cam_x - bound_x/2, this->y - cam_y - bound_y/2, x + bound_x/2 - cam_x, y + bound_y/2 - cam_y, al_map_rgb(0, 0, 0), 5);
    al_draw_rotated_bitmap(sprites[current_animation][current_frame],bound_x/2,bound_y/2,x-cam_x,y-cam_y,direction,0);
}

void Enemy_follower::move()
{
    x += speed*cos(direction);
    y += speed*sin(direction);
}

#endif
