#ifndef BOSS_SNAKE_H
#define BOSS_SNAKE_H

class Snake
{
private:
	enum SOUNDS {SCREAM};

public:
	std::vector<Snake_node>nodes;
	int length;
	ALLEGRO_SAMPLE* audio[MAX_SOUNDS];

	Snake::Snake();

	void change_direction(int position);

	void update(Player &player);
};

Snake::Snake()
{
	length = 5;

	Snake_node head(0);
	Snake_node body(0);
	Snake_node tail(length);

	nodes.push_back(head);

	for(int i = 0;i < length;i++)
	{
		nodes.push_back(Snake_node(&body,i));
	}

	nodes.push_back(tail);
	
	audio[SCREAM] = al_load_sample("audio/snake/scream.wav");
}

void Snake::update(Player &player)
{
	
	if(nodes.size() > 0)
	{
		nodes[nodes.size()-1].vulnerable = true;
		change_direction(nodes.size() - 1);
	}

	if(nodes[0].direction > deg_to_rad(360))
	{
		nodes[0].direction -= deg_to_rad(360);
	}

	if(abs(nodes[0].direction + getAngle(player.x,player.y,nodes[0].x,nodes[0].y)) > deg_to_rad(10))
	{
		nodes[0].direction -= deg_to_rad(1);
	}

	std::cout << "node[0] direction:" << rad_to_deg(nodes[0].direction) << std::endl;
	std::cout << "target angle: " << rad_to_deg(getAngle(player.x,player.y,nodes[0].x,nodes[0].y)) << std::endl;

	nodes[0].current_animation = 0;

	
	for(int i = nodes.size()-1;i >= 0;i--)
	{
		std::cout << i;
		if(nodes[i].life <= 0)
		{
			al_play_sample(audio[SCREAM],10,0,0.75,ALLEGRO_PLAYMODE_ONCE,NULL);
			nodes[0].speed *= 1.25;
			nodes.erase(nodes.begin() + i);
		}
		else
		{
			nodes[i].update(player);
			nodes[i].draw();
		}
	}	
}

void Snake::change_direction(int pos)
{
	if(pos > 0)
	{
		nodes[pos].speed = nodes[pos-1].speed;

		if(sqrt(pow(abs(nodes[pos-1].y-nodes[pos].y),2) + pow(abs(nodes[pos-1].x-nodes[pos].x),2)) > nodes[pos].bound_x/2+nodes[pos-1].bound_x/2)
		{
			nodes[pos].direction = getAngle(nodes[pos-1].x,nodes[pos-1].y,nodes[pos].x,nodes[pos].y);
		}
		change_direction(pos-1);
	}
}

#endif