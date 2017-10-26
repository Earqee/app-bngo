#ifndef ENEMY_SCOUT
#define ENEMY_SCOUT

class Enemy_scout : public Enemy
{
public:
    Enemy_scout();
    
    void move();
    void walking(Player &player);
    void attacking(Player &player);
    
    void update(Player &player);
    void draw();
};

Enemy_scout::Enemy_scout()
{
    state = WALKING_E_SC;

    // Animation Settings
    char nome_sprite[] = "images/enemy0/fatso0/0-0.png";
    animation_quantity = 2;
    frames_quantity[WALKING_E_SC] = 4;
    frames_quantity[IDLE_E_SC] = 1;
    frames_quantity[ATTACK_E_SC] = 2;
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
    speed = DEFAULT_SPEED/3;
}

void Enemy_scout::update(Player &player)
{
    switch (state)
    {
        case WALKING_E_SC:
        {
            walking(player);
        }
        break;
        case ATTACK_E_SC:
        {
            attacking(player);
        }
        break;
    }
}

void Enemy_scout::walking(Player &player)
{
	speed = DEFAULT_SPEED/3;

    direction = getAngle(x,y,player.x,player.y) + PI;
    
    damage();
    
    double _angle = getAngle(player.x,player.y,x,y);
    
    if(!(_angle < player.angle + deg_to_rad(90)               //se estiver fora do campo de visao do jogador, a direcao continua normal
    && _angle > player.angle - deg_to_rad(90)))              //senao, faz uma trajetoria circular em relacao ao jogador
    {
        speed = DEFAULT_SPEED;
        direction += deg_to_rad(90);
    }
    
    if(!enemy_collision())
        move();
    
    animate();
    draw();

    if(player_collision(player))
    {
        state = ATTACK_E_SC;
        // Animation Settings
        current_animation = ATTACK_E_SC;
        current_frame = 0;
    }

}

void Enemy_scout::attacking(Player &player)
{
    damage();
    animate();
    if(!player_collision(player))
    {
        state = WALKING_E_SC;
        current_animation = WALKING_E_SC;
        current_frame = 0;
    }
}

void Enemy_scout::draw()
{
    al_draw_rectangle(this->x - cam_x - bound_x/2, this->y - cam_y - bound_y/2, x + bound_x/2 - cam_x, y + bound_y/2 - cam_y, al_map_rgb(0, 0, 0), 5);
    al_draw_rotated_bitmap(sprites[current_animation][current_frame],bound_x/2,bound_y/2,x-cam_x,y-cam_y,direction,0);
}

void Enemy_scout::move()
{
    x += speed*cos(direction);
    y += speed*sin(direction);
}

#endif
