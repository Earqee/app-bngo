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

class Volatile : public Object
{
public:
	double direction;
	double speed;
};

class Animated : public Object
{
public:
	int currentFrame;
	int maxFrame;
	ALLEGRO_BITMAP *anim[MAX_STATES][MAX_ANIM];
};

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