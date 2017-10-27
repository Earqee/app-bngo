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

	void animate();
};

void Animated::animate()
{
	frame_counter++;
	if(frame_counter % (FPS/frames_quantity[current_animation] - 5) == 0)
	{
		current_frame = (current_frame+1)%(frames_quantity[current_animation]);
		frame_counter = 0;
	}
}	

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

#endif