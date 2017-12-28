#ifndef CLASSES_H
#define CLASSES_H

// MOTHER CLASSES

class Object
{
public:
	double x, y;
	double bound_x;
	double bound_y;
	ALLEGRO_BITMAP *image;
};

class Animated : public Object
{
public:
	ALLEGRO_BITMAP* sprites[MAX_ANIM][MAX_FRAMES];

	int frames_quantity[MAX_ANIM];

	int current_frame;
	int frame_counter;

	int current_animation;
	int animation_quantity;

	int red,green,blue;

	void animate();
};

void Animated::animate()
{
	frame_counter++;
	if(frame_counter % (FPS/frames_quantity[current_animation] ) == 0)
	{
		current_frame = (current_frame+1)%(frames_quantity[current_animation]);
		frame_counter = 0;
	}
}

/*

se(++frameAtual > tempoDeEsperaParaMudarOFrame)
{
	frameAtual.resetarParaZero();
	frameAtual.adicionaUm % quantidadeDeFrames;
}

*/

class Walker : public Animated
{
public:

	enum sounds {DAMAGE,DEAD,SHOT};
	int director_x;
	int director_y;
	double direction;
	double speed;
	double life;
	double angle;
	bool isAlive;

	ALLEGRO_BITMAP* shot_image;
	ALLEGRO_SAMPLE* audio[MAX_SOUNDS];
	int current_audio;

	void audio_play();
};

void Walker::audio_play()
{
	 al_play_sample(audio[current_audio], 0.6, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

//classe para facilitar a construção do menu
class Back_menu
{
public:
	ALLEGRO_BITMAP *images[2];
	ALLEGRO_BITMAP *animation[4];
	unsigned short int frame_counter;
	int bit_counter ;
	int bit_increment ;
	int	current_image ;
	int tam_images ;
	int bit_limit;
	Back_menu();
	~Back_menu();
};
Back_menu :: Back_menu()
{
	images[0] = al_load_bitmap("images/image1.png");
	images[1] = al_load_bitmap("images/image2.png");
	animation[0] = al_load_bitmap("images/player/0-0.png");
	animation[1] = al_load_bitmap("images/player/0-1.png");
	animation[2] = al_load_bitmap("images/player/0-2.png");
	animation[3] = al_load_bitmap("images/player/0-3.png");
	frame_counter = 0;
	bit_counter = 1;
	bit_increment = 1;
	current_image = 0;
	tam_images = 2;
	bit_limit = 200;
}
Back_menu :: ~Back_menu()
{
	for(unsigned i = 0; i < tam_images; ++i)
	{
		al_destroy_bitmap(images[i]);
	}
	for(unsigned i = 0; i < 4; ++i)
	{
		al_destroy_bitmap(animation[i]);
	}
}

#endif
