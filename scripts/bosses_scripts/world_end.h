#ifndef WORLD_END
#define WORLD_END

#define LAUGHTS 2
#define def_x cam_x -  DISPLAY_WIDTH/2 + 165
#define def_y cam_y - DISPLAY_HEIGHT/2 + 50
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
	bool destroyStrikes;

	int STATE;

	int alpha[MAX_GRIM_STATES];
	double change_state_count[2];
	double change_state_delay[2];
	double frameCount[MAX_GRIM_STATES];
	double frameDelay[MAX_GRIM_STATES];

	bool play_ID;
	bool world_end_attack;

	ALLEGRO_BITMAP *area_atack[2];
	ALLEGRO_SAMPLE *audio_atack[5];
	ALLEGRO_SAMPLE *audio_atack_haha;

	void change_x(Player &player);
	void act(Player &player, ENUM_TAG attack_mode);
	void draw();
	void merge();
	void repost();
	void move(Player &player);
	void eliminate();
	ENUM_TAG rand_stage();
};

The_Grim_Reaper::The_Grim_Reaper()
{
	destroyStrikes = false;

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

	frameCount[RECONSTRUCTION] = 30;
	frameDelay[MERGE] = 500;
	frameDelay[ELIMINATE] = 300;

	change_state_count[0] = 0;
	change_state_delay[0] = 85;

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

	audio_atack[0] = al_load_sample("audio/grim/S76_-_Aren_t_you_supposed_to_be_dead.ogg");
	audio_atack[1] = al_load_sample("audio/grim/Always_too_overconfident.ogg");
	audio_atack[2] = al_load_sample("audio/grim/I_didnt_start_this_war_but_Im_damn_well_gonna_fini.ogg");
	audio_atack[3] = al_load_sample("audio/grim/And_stay_down.ogg");
	audio_atack_haha = al_load_sample("audio/grim/devils_laugh_1_.ogg");
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
			repost();
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
	std::cout << "Hi0" << std::endl;

	direction = getAngle(player.x, player.y, this->x+90, this->y+90);

	std::cout << "wtf" << std::endl;
	
	if(++change_state_count[0] > change_state_delay[0])
	{
		std::cout << "wtf" << std::endl;

		change_state_count[0] = 0;
		
		world_end_attack = true;
		destroyStrikes = true;
		
		std::cout << "wtf1" << std::endl;

		this->STATE = rand_stage();

		std::cout << "wtf2" << std::endl;
	}

	std::cout << "Hi1" << std::endl;
	
	dist_player_boss = dist_point(player.x, player.y, x + 90, y + 90);
	
	if(dist_player_boss > 600)
	{
		speed = 30;
	}
	else if(dist_player_boss > 500)
	{
		speed = 7.5;
	}
	else if(dist_player_boss > 400)
	{
		speed = 5;
	}
	else if(dist_player_boss < 300)
	{
		speed = 2;
	}

	x += speed * cos(direction);
	y += speed * sin(direction);

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
	std::cout << "Aqui dentro" << std::endl;
	switch(rand()%5)
	{
		case 0:        
		return SENTENTIATE;

		case 1:
		return MERGE;

		case 2:
		return ELIMINATE;

		case 3:
		return RECONSTRUCTION;

		case 4:
		return RECONSTRUCTION;
	}
	std::cout << "Aqui fora" << std::endl;
	return 0;
}

void The_Grim_Reaper::repost()
{	
	x += 8 * cos(direction);
	y += 8 * sin(direction);


	if(++frameCount[RECONSTRUCTION]> frameDelay[RECONSTRUCTION])
	{
		frameCount[RECONSTRUCTION] = 0;
		STATE = NORMAL;
		return;
	}
}

void The_Grim_Reaper::draw()
{
	al_draw_scaled_rotated_bitmap(image, 186/2, 182/2, this->x - cam_x, this->y - cam_y, 1 + change_state_count[1]/1000, 1 + change_state_count[1]/1000, 0, 0);
}

void The_Grim_Reaper::act(Player &player, ENUM_TAG attack_mode)
{
	
	if(++frameCount[attack_mode] > frameDelay[attack_mode])
	{
		frameCount[attack_mode] = 0;

		dist_player_boss = sqrt(pow(player.x-this->x, 2)+pow(player.y-this->y, 2));

		if(dist_player_boss > 225)
		{
			player.isAlive = false;
		}

		STATE = NORMAL;
		//return;
	}

	al_draw_tinted_bitmap(area_atack[attack_mode], al_map_rgba_f(0.3 + alpha[attack_mode]*0.1, 0, 0, 0.3 + alpha[attack_mode]*0.1), x - def_x - 480, y - def_y - 650, 0);
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
	al_draw_scaled_rotated_bitmap(image, 186/2, 182/2, this->x - cam_x, this->y - cam_y, frameCount[MERGE]/100*4, frameCount[MERGE]/100*4, 0, 0);
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

	if(world_end_attack)
	{
		al_play_sample(audio_atack[1], 3.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}

	al_draw_scaled_rotated_bitmap(image, 186/2, 182/2, this->x - cam_x, this->y - cam_y, frameCount[ELIMINATE]/100, frameCount[ELIMINATE]/100, frameCount[ELIMINATE]*180/PI, 0);
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
			x = rand() % (DISPLAY_WIDTH + 2000) + cam_x - 2000; //
			y = 0 - 200 + cam_y;
			bound_x = 20;
			bound_y = 200;
		}
		else
		{
			x = DISPLAY_WIDTH + 200 + cam_x;
			y = rand() % (DISPLAY_HEIGHT + 2000) + cam_y - 2000; //
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
		{
			al_draw_filled_rectangle(x - cam_x, y - cam_y, x + bound_x - cam_x, y + bound_y - cam_y, al_map_rgb(255, rand()%255, 0));
		}
		else
		{
			al_draw_filled_rectangle(x - cam_x, y - cam_y, x + bound_x - cam_x, y + bound_y - cam_y, al_map_rgb(255, 0, rand()%255));
		}
	}
	else
	{
		al_draw_filled_rectangle(x - cam_x, y - cam_y, x + bound_x - cam_x, y + bound_y - cam_y, al_map_rgb(255, rand()%255, rand()%255));
	}
}



#endif
