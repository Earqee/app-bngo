#ifndef FATSO_H
#define FATSO_H

class Enemy_Fatso : public Normal_Enemy
{
public:
    Enemy_Fatso();

    void update(Player &player);
    void walking(Player &player);
    void attacking(Player &player);
};

Enemy_Fatso::Enemy_Fatso()
{
    attack_timer.Set_count_delay(1*60);
    char nome_sprite[] = "images/enemy0/fatso0/0-0.png";

    for(int i = 0;i < animation_quantity; i++)
    {
        for(int j = 0;j < frames_quantity[i]; j++)
        {
            nome_sprite[21] = i + 48;
            nome_sprite[23] = j + 48;

            sprites[i][j] = al_load_bitmap(nome_sprite);
        }
    }

    audio[DEAD] = al_load_sample("audio/fatso00-1.wav");

    life = 15;
    atk_strength = 20;
    score = atk_strength;

    speed = DEFAULT_SPEED/1.64;
}

void Enemy_Fatso::update(Player &player)
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

void Enemy_Fatso::walking(Player &player)
{
	speed = DEFAULT_SPEED/1.64;

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

void Enemy_Fatso::attacking(Player &player)
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
