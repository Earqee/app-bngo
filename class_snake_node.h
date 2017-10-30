#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

class Snake_node : public Enemy
{
public:

	Snake_node(int i);
	Snake_node(Snake_node *node,int i);

	void update(Player &player);
	void draw();
};

Snake_node::Snake_node(int i)
{
	x = cam_x + DISPLAY_WIDTH/2;
	y = cam_y + DISPLAY_HEIGHT/2;

	bound_x = 96 - 10*i;
	bound_y = 96 - 10*i;

	speed = 2;

	life = 50;
	vulnerable = false;
	
	animation_quantity = 2;
	current_animation = 1;
	current_frame = 0;

	frames_quantity[0] = 1;
	frames_quantity[1] = 1;

	red = 255; green = 255; blue = 255;

	char nome_sprite[] = "images/snake/nodes/0-0.png";
       
    for(int i = 0;i < animation_quantity; i++)
    {
        for(int j = 0;j < frames_quantity[i]; j++)
		{
            nome_sprite[19] = i + 48;
            nome_sprite[21] = j + 48;
			
            sprites[i][j] = al_load_bitmap(nome_sprite);
        }
    }
}

Snake_node::Snake_node(Snake_node *node,int i)
{
	this->x = node->x;
	this->y = node->y;
	this->bound_x = node->bound_x - 7*i;
	this->bound_y = node->bound_y - 7*i;

	this->speed = node->speed;

	this->life = node->life;
	this->vulnerable = node->vulnerable;

	this->red = 255; this->green = 255; this->blue = 255;

	this->animation_quantity = node->animation_quantity;

	this->frames_quantity[0] = node->frames_quantity[0];
       
    for(int i = 0;i < animation_quantity; i++)
    {
        for(int j = 0;j < frames_quantity[i]; j++)
        {
            this->sprites[i][j] = node->sprites[i][j];
        }
    }
}

void Snake_node::update(Player &player)
{
	for(unsigned int i = 0;i < bullet_vector.size();i++)
	{
		if(abs(x - bullet_vector[i]->x) < bound_x/2 + bullet_vector[i]->bound_x/2 
		  && abs(y - bullet_vector[i]->y) < bound_y/2 + bullet_vector[i]->bound_y/2)
		{
			delete bullet_vector[i];
			bullet_vector.erase(bullet_vector.begin()+i);
			if(vulnerable)
			{
				life-=10;
				blue -= 5;
				green -= 5;
			}
		}
	}
	
	x += speed*cos(direction);
	y += speed*sin(direction);
}

void Snake_node::draw()
{
	//al_draw_rectangle(x-(bound_x/2)-cam_x,y-(bound_y/2)-cam_y,x+(bound_x/2)-cam_x,y+(bound_y/2)-cam_y,al_map_rgb(0,0,0),1);
	al_draw_tinted_scaled_rotated_bitmap(sprites[current_animation][current_frame],al_map_rgb(red,green,blue),bound_x/2,bound_y/2,x-cam_x,y-cam_y,bound_x/96,bound_y/96,direction,0);
}

#endif