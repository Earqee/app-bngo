#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

class Snake_node : public Enemy
{
public:
	ALLEGRO_SAMPLE* reflect_bullet;	//audio que toca quando um node é atingido mas não é vulnerável

	Snake_node(int i);				//Construtor base
	Snake_node(Snake_node *node,int i);	//Construtor por copia

	void update(Player &player);		//Update do node
	void draw();		//desenha o node
};

Snake_node::Snake_node(int i)
{
	x = cam_x + DISPLAY_WIDTH/2;	//inicia no meio da tela (x)
	y = cam_y - SNAKE_SAFE_ZONE;	//inicia fora da tela, na parte superior (y)

	bound_x = 96 - 10*i;			//os nodes intermediarios e a cauda recebem o parammetro i != 0, por isso o tamanho deles diminui progressivamente
	bound_y = 96 - 10*i;

	speed = 2;						//velocidade inicial do node

	life = 255;						//vida do node
	vulnerable = false;				//variavel que diz se o node está vulnerável

	reflect_bullet = al_load_sample("audio/snake/reflect_bullet.wav");	//audio que toca quando a bala colide com o node mas não tira vida

	animation_quantity = 2;			//quantidade de animacoes
	current_animation = 1;			//animacao atual (todos comecam com 1, que é o sprite da vertebra, e nos estados só o da cabeça é alterado)
	current_frame = 0;				//o frame atual é o 0

	frames_quantity[0] = 2;			//0 - cabeca com a boca fechada    1 - cabeca com a boca aberta
	frames_quantity[1] = 1;			//0 - vertebra

	red = 255; green = 255; blue = 255; //valor de cada pigmento pra pintar o node

	char nome_sprite[] = "images/snake/nodes/0-0.png";	//caminho base para carregar imagens

    for(int i = 0;i < animation_quantity; i++)
    {
        for(int j = 0;j < frames_quantity[i]; j++)
		{
            nome_sprite[19] = i + 48;	//altera o numero da animacao no caminho do arquivo de acordo com a animacao que está sendo carregada
            nome_sprite[21] = j + 48;	//altera o numero do frame no caminho do arquivo de acordo com o frame que está sendo carregado

            sprites[i][j] = al_load_bitmap(nome_sprite);	//carrega a imagem no caminho "nome_sprite"
        }
    }
}

Snake_node::Snake_node(Snake_node *node,int i)		//Construtor por copia, apenas copia os valores de *node, principalmente os prites e audios, 
{
	this->x = node->x;
	this->y = node->y;
	this->bound_x = node->bound_x - 7*i;
	this->bound_y = node->bound_y - 7*i;

	this->speed = node->speed;

	this->life = node->life;
	this->vulnerable = node->vulnerable;

	reflect_bullet = node->reflect_bullet;

	this->red = 255;
	this->green = 255;
	this->blue = 255;

	animation_quantity = 2;
	current_animation = 1;
	current_frame = 0;

	frames_quantity[0] = 2;
	frames_quantity[1] = 1;

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
	for(unsigned int i = 0;i < bullet_vector.size();i++)	//checa a colisao entre o node e as balas do jogador
	{
		if(abs(x - bullet_vector[i]->x) < bound_x/2 + bullet_vector[i]->bound_x/2
		  && abs(y - bullet_vector[i]->y) < bound_y/2 + bullet_vector[i]->bound_y/2)
		{
			delete bullet_vector[i];	//desaloca a bal, caso haja colisao
			bullet_vector.erase(bullet_vector.begin()+i);	//apaga a bala do vetor
			if(vulnerable)	//se o node estiver vulnerável, tira a vida e deixa ele mais vermelho(diminui a quantidade de azul e de verde)
			{
				life-=100;
				blue -= 10;
				green -= 10;
			}
			else
			{
				al_play_sample(reflect_bullet,1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);	//se o node não estiver vulneravel toca o som reflect_bullet
			}
		}
	}

	if(abs(x - player.x) < bound_x/2 + player.bound_x/2				//checa a colisao com o jogador
		&& abs(y - player.y) < bound_y/2 + player.bound_y/2)
	{
		if(player.vulnerable)
		{
			player.life -= 5;
			player.vulnerable = false;	//deixa o jogador invulneravel por alguns instantes
		}
	}
	

	x += speed*cos(direction);	//move o node no eixo x
	y += speed*sin(direction);  //move o node no eixo y
}

void Snake_node::draw()
{
	//al_draw_rectangle(x-(bound_x/2)-cam_x,y-(bound_y/2)-cam_y,x+(bound_x/2)-cam_x,y+(bound_y/2)-cam_y,al_map_rgb(0,0,0),1); //desenha a hitbox do node
	al_draw_tinted_scaled_rotated_bitmap(sprites[current_animation][current_frame],al_map_rgb(red,green,blue),bound_x/2,bound_y/2,x-cam_x,y-cam_y,bound_x/96,bound_y/96,direction,0);  //desenha o node
}

#endif
