#ifndef BOSS_SNAKE_H
#define BOSS_SNAKE_H

class Snake
{
public:
	std::vector<Snake_node>nodes;		//vetor de nodes que formam a cobra

	ALLEGRO_SAMPLE* audio[MAX_SOUNDS];	//array de sons
	ALLEGRO_SAMPLE_ID sample;			//ponteiro para saber se o som atual n está tocando, para nao sobrepor

	int length;							//comprimento da cobra
	int state;							//estado da cobra
	double aux;							//variavel auxiliar para guardar a velocidade anterior, quando troca de estado

	Frame state_timer;					//frame que controla o tempo que estado vai durar
	Frame chase;						//frame que controla a atualizacao da direcao da cabeça

	Snake();							//Construtor
		
	void change_direction(int position);	//Funcao recursiva que muda a direcao de cada node em funcao do node que esta na frente
	void update(Player &player);			//Update da cobra

	void state_wand(Player &player);		//Estado que a cobra persegue o jogador com velocidade constante e gira em diracao ao jogador de acordo com o frame "chase"
	void state_chase(Player &player);		//Estado em que ela fica totalmente invulneravel e aumenta gradativamente a velocidade, perseguindo o jogador
	void state_hurt(Player &player);		//Quando perde um node, mantem a direcao e acelera ate chegar fora da tela, quando comeca a atacar
	void state_attack(Player &player);		//Vai em direcao ao jogador, de baixo para cima ou de cima para baixo
	void state_search(Player &player);		//Estado que fica parada mirando no jogador antes de ir para chase
};

Snake::Snake()
{
	length = 6 + (rand()%3);								//comprimento da cobra - 1
	state = WAND_SNAKE;						//estado inicial

	Snake_node head(0);						//cria a cabeca
	Snake_node body(0);						//cria um node do corpo

	nodes.push_back(head);					//coloca a cabeca no vetor

	for(int i = 0;i < length;i++)
	{
		nodes.push_back(Snake_node(&body,i));	//cria um node do corpo copiando o que já foi criado acima, e coloca no final do vetor
	}

	audio[SCREAM] = al_load_sample("audio/snake/scream.wav");	//carrega o audio do grito

	state_timer.Set_count_delay(150);	//inicia o timer com 150 frames
	chase.Set_count_delay(15);			//inicia o timer com 15 frames
}

void Snake::update(Player &player)
{
	if(nodes.size() > 0)
	{
		switch(state)		//Maquina de estados finitos
		{
		case WAND_SNAKE:
			{
				state_timer.frameDelay = 8*60; //a cobra permanece nesse estado por aproximadamente 8 segundos
				state_wand(player);
			}
			break;
		case SEARCH_SNAKE:
			{
				state_timer.frameDelay = 1.5*60;//a cobra permanece nesse estado por aproximadamente 1,5 segundos
				state_search(player);
			}
			break;
		case HURT_SNAKE:
			{
				state_hurt(player);
			}
			break;
		case CHASE_SNAKE:
			{
				state_timer.frameDelay = 5*60;//a cobra permanece nesse estado por aproximadamente 5 segundos
				state_chase(player);
			}
			break;
		case ATTACK_SNAKE:
			{
				state_timer.frameDelay = (16-nodes.size())*60;	//o tempo que a cobra permanece nesse estado é dado em funcao do comprimento atual
				state_attack(player);
			}
			break;
		}
	}
}

void Snake::state_wand(Player &player)
{
	nodes[nodes.size()-1].vulnerable = true;	//deixa o ultimo node vulneravel
	change_direction(nodes.size() - 1);			//recursao

	if(++chase.frameCount > chase.frameDelay)
	{
		nodes[0].direction =  getAngle(player.x,player.y,nodes[0].x,nodes[0].y) + deg_to_rad(rand()%30 - 15); //quando o frame chase termina a cabeca gira em diracao ao jogador

		chase.resetFrameCount();
	}

	nodes[0].current_animation = 0;	//deixa o sprite da cabeca com a boca fechada

	for(int i = nodes.size()-1;i >= 0;i--)
	{
		if(i != nodes.size()-1)
		{
			if(nodes[i].blue < nodes[i].life)
			{
				nodes[i].blue += 5;					//Faz a cor de cada node anterior à cauda voltar à cor normal gradativamente
			}
			if(nodes[i].green < nodes[i].life)
			{
				nodes[i].green += 5;
			}
		}
		else
		{
			nodes[i].blue = nodes[i].life;		//deixa a cauda mais vermelha de acordo com a vida
			nodes[i].green = nodes[i].life;
		}
		nodes[i].red = 255;

		nodes[i].update(player);
		nodes[i].draw();
	}

	if(++state_timer.frameCount > state_timer.frameDelay)		//Muda o estado caso o timer termine
	{
		aux = nodes[0].speed; // guarda a velociade atual
		nodes[0].speed = 0;		//zera a velocidade
		nodes[0].current_frame = 0;
		state = SEARCH_SNAKE;
		state_timer.resetFrameCount();
	}

	if(nodes[nodes.size()-1].life <= 0)		//caso ela perca um node
	{
		if(nodes.size() > 1)		//se nao foi a cabeca
		{
			nodes.pop_back();		//tira o ultimo node do vetor
			//Scream
			al_play_sample(audio[SCREAM],1,0,0.5,ALLEGRO_PLAYMODE_ONCE,NULL); //grita

			nodes[0].current_frame = 1;		//deixa a boca aberta
			nodes[nodes.size()-1].vulnerable = false; //deixa o ultimo node invulneravel
			nodes[0].speed *= 5; //quintuplica a velocidade
			state = HURT_SNAKE;
			state_timer.resetFrameCount();
			chase.frameDelay += 5;	//aumenta o atraso do chase
		}
		else
		{
			state = DEAD_SNAKE;
		}
	}
}

void Snake::state_search(Player &player)
{
	change_direction(nodes.size() - 1);//recursao

	nodes[0].direction = getAngle(player.x,player.y,nodes[0].x,nodes[0].y);//deixa a cabeca sempre virada para o jogador

	for(int i = nodes.size()-1;i >= 0;i--)
	{
		nodes[i].blue = nodes[i].life;
		nodes[i].green = nodes[i].life;
		nodes[i].red = 255;

		nodes[i].update(player);
		nodes[i].draw();
	}

	if(++state_timer.frameCount == state_timer.frameDelay)
	{
		nodes[nodes.size()-1].vulnerable = false;
		nodes[0].speed = aux;	//retorna a velocidade que ela estava antes de entrar no estado atual
		nodes[0].current_frame = 1;	//deixa a boca aberta
		state = CHASE_SNAKE;		
		state_timer.resetFrameCount();

		cam_shake = true;		//faz a camera tremer
	}

	if(nodes[nodes.size()-1].life <= 0)
	{
		if(nodes.size() > 1)
		{
			nodes.pop_back();

			//Animation
			nodes[0].current_frame = 1;												//Vai para o estado hurt, semelhante ao wand

			//Scream
			al_play_sample(audio[SCREAM],1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);

			nodes[nodes.size()-1].vulnerable = false;
			nodes[0].speed = aux*5;	//quintuplica a velocidade

			state = HURT_SNAKE;

			state_timer.resetFrameCount();
		}
		else
		{
			state = DEAD_SNAKE;
		}
	}
}

void Snake::state_chase(Player &player)
{
	change_direction(nodes.size() - 1);	//recursao

	if(++chase.frameCount > chase.frameDelay)
	{
		nodes[0].direction = getAngle(player.x,player.y,nodes[0].x,nodes[0].y);
		nodes[0].speed += 0.05;		//aumenta a velocidade gradativamente
		chase.resetFrameCount();
	}
			
	nodes[0].animate();		//anima ela abrindo e fechando a boca

	for(int i = nodes.size()-1;i >= 0;i--)
	{
		nodes[i].blue = 220;
		nodes[i].green = 220;
		nodes[i].red = 255;

		nodes[i].update(player);
		nodes[i].draw();
	}

	if(++state_timer.frameCount > state_timer.frameDelay)
	{
		nodes[0].current_frame = 0;
		nodes[0].speed = aux;
		state = WAND_SNAKE;
		state_timer.resetFrameCount();
	}
}

void Snake::state_hurt(Player &player)
{
	change_direction(nodes.size() - 1);	//recursao

	for(int i = nodes.size()-1;i >= 0;i--)
	{
		nodes[i].blue = 0;
		nodes[i].green = 0;
		nodes[i].red = 200+rand()%56;	//faz ela ficar piscando

		nodes[i].update(player);
		nodes[i].draw();
	}

	if(nodes[0].x < cam_x - SNAKE_SAFE_ZONE || nodes[0].x > cam_x + DISPLAY_WIDTH + SNAKE_SAFE_ZONE			//se estiver fora da tela comeca a atacar
	|| nodes[0].y < cam_y - SNAKE_SAFE_ZONE || nodes[0].y > cam_y + DISPLAY_HEIGHT + SNAKE_SAFE_ZONE)
	{
		state = ATTACK_SNAKE;
		state_timer.resetFrameCount();
	}
}

void Snake::state_attack(Player &player)
{
	change_direction(nodes.size() - 1);	//recursao

	for(int i = nodes.size()-1;i >= 0;i--)
	{
		nodes[i].red = 200+rand()%56;		//deixa ela piscando

		nodes[i].update(player);
		nodes[i].draw();
	}

	if(nodes[0].x < cam_x - SNAKE_SAFE_ZONE || nodes[0].x > cam_x + DISPLAY_WIDTH + SNAKE_SAFE_ZONE		//ao sair da tela ela vai pra o lado superior ou inferior com a mesma abcissa do jogador e segue em frente
	|| nodes[0].y < cam_y - SNAKE_SAFE_ZONE || nodes[0].y > cam_y + DISPLAY_HEIGHT + SNAKE_SAFE_ZONE)
	{
		nodes[0].x = player.x;
		nodes[0].y = cam_y - 96 + (rand()%2) * (DISPLAY_HEIGHT + 96);	//determina se ela vai para cima ou para baixo
		for(int i = nodes.size() - 1;i > 0;i--)
		{
			nodes[i].x = nodes[0].x;				//leva todos os nodes para a mesma posicao
			nodes[i].y = nodes[0].y;
		}

		al_play_sample(audio[SCREAM],2,0,0.4,ALLEGRO_PLAYMODE_ONCE,&sample); //grita
		nodes[0].direction = getAngle(player.x,player.y,nodes[0].x,nodes[0].y);
	}

	if(++state_timer.frameCount > state_timer.frameDelay)
	{
		nodes[0].current_frame = 0;
		nodes[0].speed /= 5;	//volta para a velocidade anterior
		nodes[0].speed *= 1.05;	//aumenta 5% 
		state = WAND_SNAKE;
		state_timer.resetFrameCount();
	}
}

void Snake::change_direction(int pos)
{
	if(pos > 0)	//se o node nao for a cabeca
	{
		nodes[pos].speed = nodes[pos-1].speed; //vai passando a velocidade, pra que os nodes nao "descolem"
		/*
		
		calcula a distancia entre o ponto de tras de quem tá na frente com o ponto central do node atual. Se for maior que metade da largura do node atual, gira em direcao ao proximo.
		(essa explicacao ta terrivel)

		pra pegar o ponto de tras multiplica o vetor diretor do node por -largura/2
		_____
		|	 |
		|	 |
		---p--
		 ____
		 | c |
		 ----
		
		*/
		if(sqrt (pow (abs ( (nodes[pos-1].y + sin(nodes[pos-1].direction + PI) * (nodes[pos-1].bound_y/2)) - nodes[pos].y),2) +
			pow(abs((nodes[pos-1].x + cos(nodes[pos-1].direction + PI)*(nodes[pos-1].bound_x/2)) - nodes[pos].x),2))
			> (nodes[pos].bound_x/2))
		{
			nodes[pos].direction = getAngle(nodes[pos-1].x + cos(nodes[pos-1].direction+ PI)*nodes[pos-1].bound_x/2,nodes[pos-1].y + sin(nodes[pos-1].direction + PI)*nodes[pos-1].bound_y/2,nodes[pos].x,nodes[pos].y);
		}
		change_direction(pos-1);	//chamada recursiva
	}
}

#endif
