#ifndef NORMAL_ENEMY
#define NORMAL_ENEMY

class Normal_Enemy : public Enemy
{
public:
    Normal_Enemy();
    Frame attack_timer;
    int atk_strength;

    void move();
    void attack_player(Player &player);
};

Normal_Enemy::Normal_Enemy()
{
    state = WALKING_E_SC;

    // Animation Settings
    animation_quantity = 2;
    frames_quantity[WALKING_E_SC] = 4;
    frames_quantity[IDLE_E_SC] = 1;
    frames_quantity[ATTACK_E_SC] = 2;
    current_animation = WALKING_E_SC;
    current_frame = 0;
}

void Normal_Enemy::move()
{
    x += speed*cos(direction);
    y += speed*sin(direction);
}

void Normal_Enemy::attack_player(Player &player)
{
  if(player_collision(player) && player.vulnerable == true)
  {
      player.vulnerable = false;
      player.life -= atk_strength;
  }
}

#endif
