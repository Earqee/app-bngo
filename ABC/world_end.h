#ifndef WORLD_END
#define WORLD_END

#define def_x (DISPLAY_WIDTH)/2
#define def_y (DISPLAY_HEIGHT)/2
#define MAX_GRIM_STATES 6
enum Grim_States{SENTENTIATE, RECONSTRUCTION, MERGE, ELIMINATE, NORMAL};

class The_Grim_Reaper : public Object
{
public:
	int life;
	The_Grim_Reaper();
	double speed;
	double direction;

	double dist_player_boss;

	bool isAlive;
	bool is_Backing;
	bool is_Right;
	bool decreasing;

	int STATE;

	int alpha[MAX_GRIM_STATES];
	double change_state_count[2];
	double change_state_delay[2];
	double frameCount[MAX_GRIM_STATES];
	double frameDelay[MAX_GRIM_STATES];

	bool play_ID;
	bool world_end_attack;

	ALLEGRO_BITMAP *area_atack[2];
	ALLEGRO_SAMPLE *audio_atack[2];

	void change_x(Player &player);
	void change_y();
	void act(Player &player, ENUM_TAG attack_mode);
	void draw();
	void merge();
	void move(Player &player);
	void eliminate();
	ENUM_TAG rand_stage();
};

The_Grim_Reaper::The_Grim_Reaper()
{

	for(int i = 0; i < MAX_GRIM_STATES; i++)
	{
		alpha[i] = 0;
		frameCount[i] = 0;
		frameDelay[i] = 120;
	}

	x = DISPLAY_WIDTH/2;
	y = DISPLAY_HEIGHT/3;
	bound_x = 180;
	bound_y = 180;
	speed = 1;
	life = 300;

	frameDelay[MERGE] = 500;
	frameDelay[ELIMINATE] = 300;

	change_state_count[0] = 0;
	change_state_delay[0] = 500;

	change_state_count[1] = 0;
	change_state_delay[1] = 100;

	STATE = NORMAL;

	isAlive = true;
	is_Backing = false;
	is_Right = true;
	decreasing = false;

	image = al_load_bitmap("images/grim/grim.png");
	area_atack[0] = al_load_bitmap("images/grim/index.png");
	area_atack[1] = al_load_bitmap("images/grim/index2.png");

	audio_atack[0] = al_load_sample("audio/grim/And_stay_down.ogg");
	audio_atack[1] = al_load_sample("audio/grim/Always_too_overconfident.ogg");
	audio_atack[2] = al_load_sample("audio/grim/Always_too_overconfident.ogg");
	//can (super) attack?
	play_ID = true;
	world_end_attack = true;
}

void The_Grim_Reaper::move(Player &player)
{
	switch(STATE)
	{
		case NORMAL:
		{
			change_x(player);
			break;
		}
		case SENTENTIATE:
		{
			act(player, SENTENTIATE);
			break;
		}
		case RECONSTRUCTION:
		{
			act(player, RECONSTRUCTION);
			break;
		}
		case MERGE:
		{
			merge();
			break;
		}
		case ELIMINATE:
		{
			eliminate();
			break;
		}
	}
}

void The_Grim_Reaper::change_x(Player &player)
{ //OK
	direction = getAngle(player.x, player.y, x+90, y+90);
	x += speed * cos(direction);
	y += speed * sin(direction);

	if(++change_state_count[0] > change_state_delay[0])
	{
		change_state_count[0] = 0;
		world_end_attack = true;
		STATE = rand_stage();
	}

	dist_player_boss = dist_point(player.x, player.y, x + 90, y + 90);
	if(dist_player_boss > 400)
		speed = 3;
	if(dist_player_boss < 300)
		speed = 1;

	if(change_state_count[1] > change_state_delay[1])
		decreasing = true;
	if(change_state_count[1] < 0)
		decreasing = false;
	if(decreasing)
		change_state_count[1]--;
	else
		change_state_count[1]++;
}

ENUM_TAG The_Grim_Reaper::rand_stage()
{
	switch(rand()%3)
	{
		case 0:
		return SENTENTIATE;
		break;
		case 1:
		return MERGE;
		break;
		case 2:
		return ELIMINATE;
		break;
		case 3:
		return RECONSTRUCTION;
		break;
	}
}

void The_Grim_Reaper::change_y()
{

}

void The_Grim_Reaper::draw()
{
	al_draw_scaled_rotated_bitmap(image, 186/2, 182/2, this->x, this->y, 1 + change_state_count[1]/1000, 1 + change_state_count[1]/1000, 0, 0);
}

void The_Grim_Reaper::act(Player &player, ENUM_TAG attack_mode)
{
	if(play_ID)
	{
		al_play_sample(audio_atack[attack_mode], 1.2, 1.0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		play_ID = false;
	}
	if(++frameCount[attack_mode] > frameDelay[attack_mode])
	{
		frameCount[attack_mode] = 0;

		if(STATE == SENTENTIATE)
		{
			dist_player_boss = sqrt(pow(player.x-this->x, 2)+pow(player.y-this->y, 2));

			if(dist_player_boss > 225)
			{
				player.isAlive = false;
			}
			else
			{

			}
		}

		STATE = NORMAL;
		play_ID = true;
		//return;
	}

	switch(attack_mode)
	{
		case RECONSTRUCTION:
		al_draw_tinted_bitmap(area_atack[attack_mode], al_map_rgba_f(0.3 + alpha[attack_mode]*0.1, 0, 0, 0.3 + alpha[attack_mode]*0.1), x - def_x - 535, y - def_y - 700, 0);
		break;
		case SENTENTIATE:
		al_draw_tinted_bitmap(area_atack[attack_mode], al_map_rgba_f(0.3 + alpha[attack_mode]*0.1, 0, 0, 0.3 + alpha[attack_mode]*0.1), x - def_x - 480, y - def_y - 650, 0);
		break;
	}
}

void The_Grim_Reaper::merge()
{
	if(++frameCount[MERGE] > frameDelay[MERGE])
	{
		frameCount[MERGE] = 0;
		STATE = NORMAL;
		world_end_attack = true;
		return;
	}
	al_draw_scaled_rotated_bitmap(image, 186/2, 182/2, this->x, this->y, frameCount[MERGE]/100, frameCount[MERGE]/100, 0, 0);
}

void The_Grim_Reaper::eliminate()
{

	if(++frameCount[ELIMINATE] > frameDelay[ELIMINATE])
	{
		frameCount[ELIMINATE] = 0;
		STATE = NORMAL;
		world_end_attack = true;
		return;
	}

	if((int)++frameCount[ELIMINATE]%100 == 0)
		world_end_attack = true;

	al_draw_scaled_rotated_bitmap(image, 186/2, 182/2, this->x, this->y, frameCount[ELIMINATE]/100, frameCount[ELIMINATE]/100, frameCount[ELIMINATE]*180/PI, 0);
}

class Grim_Reaper_Strike : public Walker
{
public:
	int epilepsia[3];
	int get_rekt_player;
	bool have_dir;

	Grim_Reaper_Strike(The_Grim_Reaper grim, int mod, int dir, double modifier);

	void update();
	void draw();
};

std::vector<Grim_Reaper_Strike*> strikes_vector;

Grim_Reaper_Strike::Grim_Reaper_Strike(The_Grim_Reaper grim, int mod, int dir, double modifier)
{
	have_dir = false;
	speed = 1;
	get_rekt_player = 0;

	for(int i = 0; i < 3; i++)
		epilepsia[i] = rand() % 255;

	if(!dir)
	{
		speed += modifier;
		get_rekt_player = rand() % 2;

		if(get_rekt_player)
		{
			x = rand() % DISPLAY_WIDTH;
			y = 0 - 200;
			bound_x = 20;
			bound_y = 200;
		}
		else
		{
			x = DISPLAY_WIDTH + 200;
			y = rand() % DISPLAY_HEIGHT;
			bound_x = 200;
			bound_y = 20;
		}
	}
	else
	{
		x = grim.x;
		y = grim.y;
		bound_x = 32;
		bound_y = 32;
		direction = mod*PI/16;
		speed += modifier;
		have_dir = true;
	}
}

void Grim_Reaper_Strike::update()
{
	if(!have_dir)
	{
		if(get_rekt_player)
			y += speed;
		else
			x -= speed;
	}
	else
	{
		x += speed * cos(direction);
		y += speed * sin(direction);
	}
}

void Grim_Reaper_Strike::draw()
{
	if(!have_dir)
	{
		if(get_rekt_player)
			al_draw_filled_rectangle(x, y, x + bound_x, y + bound_y, al_map_rgb(255, rand()%255, 0));
		else
			al_draw_filled_rectangle(x, y, x + bound_x, y + bound_y, al_map_rgb(255, 0, rand()%255));
	}
	else
	{
		al_draw_filled_rectangle(x, y, x + bound_x, y + bound_y, al_map_rgb(255, rand()%255, rand()%255));
	}
}

Grim_Reaper_Strike* strike;

#endif
