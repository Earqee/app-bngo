#ifndef DOG_H
#define DOG_H

class Enemy_Dog: public Normal_Enemy
{
public:
    Enemy_Dog();
    
    void update(Player &player);
    void walking(Player &player);
    void attacking(Player &player);   
};

Enemy_Dog::Enemy_Dog()
{
    char nome_sprite[] = "images/enemy0/dog000/0-0.png";
       
    for(int i = 0;i < animation_quantity; i++)
    {
        for(int j = 0;j < frames_quantity[i]; j++)
        {
            nome_sprite[21] = i + 48;
            nome_sprite[23] = j + 48;

            sprites[i][j] = al_load_bitmap(nome_sprite);
        }
    }

    audio[DEAD] = al_load_sample("audio/dog0000-1.wav");

    life = 8;
    speed = DEFAULT_SPEED;
}

void Enemy_Dog::update(Player &player)
{
    switch (state)
    {
        case WALKING_E_SC:
        {
            walking(player);
            break;
        }
        case ATTACK_E_SC:
        {
            attacking(player);
            break;
        }        
    }
}

void Enemy_Dog::walking(Player &player)
{
	speed = DEFAULT_SPEED;

    direction = getAngle(x,y,player.x,player.y) + PI;
    
    damage();
    
    double _angle = getAngle(player.x,player.y,x,y);
    
    if(!enemy_collision())
        move();
    
    animate();

    if(player_collision(player))
    {
        state = ATTACK_E_SC;
        // Animation Settings
        current_animation = ATTACK_E_SC;
        current_frame = 0;
    }

}

void Enemy_Dog::attacking(Player &player)
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

#endif
