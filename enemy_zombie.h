#ifndef ZOMBIE_H
#define ZOMBIE_H

class Enemy_Zombie: public Normal_Enemy
{
public:
    Enemy_Zombie();

    void update(Player &player);
    void walking(Player &player);
    void attacking(Player &player);
};

Enemy_Zombie::Enemy_Zombie()
{
    attack_timer.Set_count_delay(1*60);
    //Animation
    char nome_sprite[] = "images/enemy0/zombie/0-0.png";

    for(int i = 0;i < animation_quantity; i++)
    {
        for(int j = 0;j < frames_quantity[i]; j++)
        {
            nome_sprite[21] = i + 48;
            nome_sprite[23] = j + 48;

            sprites[i][j] = al_load_bitmap(nome_sprite);
        }
    }

    //Audio
    audio[DEAD] = al_load_sample("audio/zombie0-1.wav");

    life = 10;
    atk_strength = 12;
    score = atk_strength;

    speed = DEFAULT_SPEED/3;
}

void Enemy_Zombie::update(Player &player)
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

void Enemy_Zombie::walking(Player &player)
{
	speed = DEFAULT_SPEED;

    direction = getAngle(x,y,player.x,player.y) + PI;

    double _angle = getAngle(player.x,player.y,x,y);

    if(!(_angle < player.angle + deg_to_rad(90)
    && _angle > player.angle - deg_to_rad(90))
	&& abs(y - player.y) < DISPLAY_HEIGHT/2
	&& abs(x - player.x) < DISPLAY_HEIGHT/2)
    {
        speed = DEFAULT_SPEED;
        direction += deg_to_rad(90);
    }
    if(!enemy_collision())
        move();

    damage();
    animate();

    if(player_collision(player))
    {
        state = ATTACK_E_SC;
        // Animation Settings
        current_animation = ATTACK_E_SC;
        current_frame = 0;
    }

}

void Enemy_Zombie::attacking(Player &player)
{
  attack_player(player);
  damage();
  animate();
  attack_timer.frameCount++;
  if(attack_timer.frameCount == attack_timer.frameDelay)
  {
      state = WALKING_E_SC;
      current_animation = WALKING_E_SC;
      current_frame = 0;
      attack_timer.resetFrameCount();
  }
}

#endif