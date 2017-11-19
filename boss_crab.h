#ifndef BOSS_CRAB_H
#define BOSS_CRAB_H

class Crab : public Enemy
{
public:
  std::vector<Bullet_crab*> water_projectile;
  int state;
  int attack_state;
  int hitbox_side;
  Frame state_timer;
  Frame water_projectile_timer;
  Bullet_crab *water_projectile_copy;

  Crab();
  void born(Player &player);
  void move(Player &player);
  void attack(Player &player);
  void idle(Player &player);
  void update(Player &player);
  bool crab_bullet_collision(Player &player);
  bool crab_bullet_collision2(Player &player);
  void draw();

};

Crab::Crab()
{
  bound_x = 256;
  bound_y = 256;
  hitbox_side = 104;
  attack_state = ATK_CURVED;

  x = cam_x + DISPLAY_WIDTH/2;
  y = cam_y - bound_y;

  speed = 1.5;
  life = 250;
  vulnerable = false;

  //BASE bullet:
  water_projectile_copy = new Bullet_crab(0,0,0,0);

  state = BORN_CRAB;
  //SETS ALL FRAMES COUNTERS
  state_timer.frameDelay = 2*60;
  state_timer.frameCount = 0;

  water_projectile_timer.frameDelay = 8;
  water_projectile_timer.frameCount = 0;

  //ANIMATION SETTINGS
  animation_quantity = 3;
	current_animation = MOVE_CRAB;
	current_frame = 0;

	frames_quantity[IDLE_CRAB] = 4;
	frames_quantity[MOVE_CRAB] = 3;
  frames_quantity[ATTACK_CRAB] = 4;

	red = 255; green = 255; blue = 255;

	char nome_sprite[] = "images/CRAB/0-0.png";

  for(int i = 0;i < animation_quantity; i++)
  {
      for(int j = 0;j < frames_quantity[i]; j++)
	    {
          nome_sprite[12] = i + '0';
          nome_sprite[14] = j + '0';

          sprites[i][j] = al_load_bitmap(nome_sprite);
      }
  }

}

bool Crab::crab_bullet_collision(Player &player)
{
  for (int i = 0; i < bullet_vector.size(); i++)
  {
    if(abs(this->x - bullet_vector[i]->x) < (hitbox_side + bullet_vector[i]->bound_x)/2 &&
    abs(this->y - bullet_vector[i]->y) < (hitbox_side + bullet_vector[i]->bound_y)/2)
    {
      delete bullet_vector[i];
      bullet_vector.erase(bullet_vector.begin()+i);
      return true;
    }
  }
  return false;
}

bool Crab::crab_bullet_collision2(Player &player)
{
  for (int i = 0; i < bullet_vector.size(); i++)
  {
    if(abs(this->x - bullet_vector[i]->x) < (hitbox_side + bullet_vector[i]->bound_x)/2 &&
    abs(this->y - bullet_vector[i]->y) < (hitbox_side + bullet_vector[i]->bound_y)/2)
    {
      return true;
    }
  }
  return false;
}

void Crab::update(Player &player)
{
  switch(state)
  {
    case BORN_CRAB:
    {
      born(player);
    }
    break;
    case IDLE_CRAB:
    {
      idle(player);
    }
    break;
    case MOVE_CRAB:
    {
      move(player);
    }
    break;
    case ATTACK_CRAB:
    {
      attack(player);
    }
    break;
  }

  //Bullet crab update
  for(int i = 0;i < water_projectile.size();i++)
  {
    water_projectile[i]->update(player);
    water_projectile[i]->draw();
    std::cout << water_projectile.size() << "\n";

    if(water_projectile[i]->state == DESTROYED ||
    water_projectile[i]->x > DISPLAY_WIDTH + cam_x || water_projectile[i]->x < cam_x ||
    water_projectile[i]->y > DISPLAY_HEIGHT + cam_y || water_projectile[i]->y < cam_y)
    {
      delete water_projectile[i];
      water_projectile.erase(water_projectile.begin()+i);
    }
  }
}
void Crab::born(Player &player)
{
  cam_shake = true;
  y += speed;
  if(y > cam_y + bound_y/2)
  {
    state = MOVE_CRAB;
  }

  animate();
  draw();
}

void Crab::idle(Player &player)
{
  if(crab_bullet_collision(player))
  {
    life-=5;
    green-=5;
    blue-=5;
  }

  if(life <= 150)
  {
    attack_state = ATK_RADIAL;
  }

  if(life <= 50)
  {
    attack_state = ATK_FUZZY;
    water_projectile_timer.frameDelay = 5;
    water_projectile_timer.resetFrameCount();
  }

  state_timer.frameCount++;

  if(state_timer.frameCount == state_timer.frameDelay)
  {
    current_frame = 0;
    current_animation = MOVE_CRAB;

    state_timer.resetFrameCount();
    state_timer.frameDelay = 3*60;

    state = MOVE_CRAB;
  }

  animate();
  draw();

}

void Crab::move(Player &player)
{
    if(x + bound_x/2 > DISPLAY_WIDTH + cam_x || x - bound_x/2 < 0 + cam_x)
    {
      speed *= -1;
    }

    x += speed;

    if(crab_bullet_collision(player));

    state_timer.frameCount++;

    if(state_timer.frameCount == state_timer.frameDelay)
    {
      state = ATTACK_CRAB;
      current_animation = ATTACK_CRAB;

      current_frame = 0;
      state_timer.resetFrameCount();
      state_timer.frameDelay = 5*60;

      cam_shake = true;
    }

    animate();
    draw();
}

void Crab::attack(Player &player)
{
  state_timer.frameCount++;
  water_projectile_timer.frameCount++;

  if(x + bound_x/2 > DISPLAY_WIDTH + cam_x || x - bound_x/2 < 0 + cam_x)
  {
    speed *= -1;
  }

  x += speed;

  if(crab_bullet_collision(player));

  if(water_projectile_timer.frameCount == water_projectile_timer.frameDelay)
  {
    switch (attack_state)
    {
      case ATK_CURVED:
      {
        for(int i = -3 ; i <= 3 ; ++i)
        {
          water_projectile.push_back(new Bullet_crab(water_projectile_copy, x, y, bound_y/2, PI/2 + i*PI/6, pow(-1, i)));
        }
      }
      break;
      case ATK_RADIAL:
      {
        angle += deg_to_rad(1.5);

        for (int i = -6; i <= 6; i++)
        {
            water_projectile.push_back(new Bullet_crab(water_projectile_copy, x, y, bound_y/2,angle + PI/2 + i*PI/6, 0));
        }
      }
      break;
      case ATK_FUZZY:
      {
        life++;
        water_projectile.push_back(new Bullet_crab(water_projectile_copy, x, y, bound_y/2, deg_to_rad(rand()%180), rand()%3-4));
      }
      break;
    }
    water_projectile_timer.resetFrameCount();
  }

  if(state_timer.frameCount == state_timer.frameDelay)
  {
    state = IDLE_CRAB;
    current_animation = IDLE_CRAB;
    state_timer.frameDelay = 2*60;
    current_frame = 0;
    state_timer.resetFrameCount();

    if(attack_state == ATK_FUZZY)
    {
      for (int i = 0; i < water_projectile.size(); i++)
      {
        water_projectile[i]->current_animation = IMPACT;
        water_projectile[i]->state = IMPACT;
        water_projectile[i]->current_frame = 0;
      }

    }
  }

  animate();
  draw();
}

void Crab::draw()
{
  //al_draw_rectangle(x-hitbox_side/2-cam_x,y-hitbox_side/2-cam_y,x+hitbox_side/2-cam_x,y+hitbox_side/2-cam_y,al_map_rgb(255,0,0),1);
  al_draw_tinted_bitmap(sprites[current_animation][current_frame], al_map_rgb(red, green, blue), this->x - this->bound_x/2 - cam_x, this->y - this->bound_y/2 - cam_y, 0);
}


#endif
