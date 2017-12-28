#ifndef PYRO_H
#define PYRO_H

class Enemy_Pyro: public Normal_Enemy
{
public:
    Enemy_Pyro();

    void update(Player &player);
    void walking(Player &player);
    void attacking(Player &player);
};

Enemy_Pyro::Enemy_Pyro()
{
    attack_timer.Set_count_delay(1*60);
    char nome_sprite[] = "images/enemy0/doctrp/0-0.png";

    for(int i = 0;i < animation_quantity; i++)
    {
        for(int j = 0;j < frames_quantity[i]; j++)
        {
            nome_sprite[21] = i + 48;
            nome_sprite[23] = j + 48;

            sprites[i][j] = al_load_bitmap(nome_sprite);
        }
    }

    audio[DEAD] = al_load_sample("audio/zombie0-0.wav");

    life = 20;
    atk_strength = 15;
    score = atk_strength;
    speed = DEFAULT_SPEED;
}

void Enemy_Pyro::update(Player &player)
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

void Enemy_Pyro::walking(Player &player)
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

void Enemy_Pyro::attacking(Player &player)
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
