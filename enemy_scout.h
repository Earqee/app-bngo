#ifndef ENEMY_SCOUT
#define ENEMY_SCOUT

class Enemy_scout : public Enemy
{
public:
    Enemy_scout();
    
    void move();
    
    void update(Player &player);
    void draw();
};

Enemy_scout::Enemy_scout()
{
    image = al_load_bitmap("images/assault.png");
    shot_audio = al_load_sample("audio/Space Gun 04.wav");
    shot_image = al_load_bitmap("images/laser3.png");
    bound_x = 110;
    bound_y = 110;	
    life = 100;
    speed = DEFAULT/1.5;
}

void Enemy_scout::update(Player &player)
{
    direction = angle(x,y,player.x,player.y) + PI;
    
    damage();
    
    double _angle = angle(x,y,player.x,player.y);
    
    if(_angle < player.angle - deg_to_rad(90)               //se estiver fora do campo de visao do jogador, a direcao continua normal
    && _angle > player.angle + deg_to_rad(90))              //senao, faz uma trajetoria circular em relacao ao jogador
    {
        direction += deg_to_rad(90);                                          
    }
    
    move();
    
    draw();
}

void Enemy_scout::draw()
{
    al_draw_rotated_bitmap(image,bound_x/2,bound_y/2,x,y,direction,0);
}

void Enemy_scout::move()
{
    x += speed*cos(direction);
    y += speed*sin(direction);
}

#endif
