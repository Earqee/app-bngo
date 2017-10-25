#ifndef my_boss_class_h
#define my_boss_class_h

enum STATE{CHASING, ATTACKING, RESTING, SPECIAL};

class Boss
{
public:
	float x, y;
	float speed;
	short int frame;
	short int state;
	bool living ;
	float angle;
	float life;
	ALLEGRO_BITMAP *bitmap[4];

	Boss( ALLEGRO_BITMAP* _b0 = NULL, ALLEGRO_BITMAP* _b1 = NULL, ALLEGRO_BITMAP* _b2 = NULL, ALLEGRO_BITMAP* _b3 = NULL,
		float _x = 40+rand()%(display_width-70), float _y = 40+rand()%(display_height-70), float _speed = 1.5,
		short int _frame = rand()%60, float _angle = 0.0, float _life = 500, short int _state = CHASING, bool _living = false );

	//calculating funcion
	void Update( float _y, float _x );

	//finite states of enemy
	void Chasing( float _y, float _x );
	void Resting( float _y, float _x );
	void Attacking( float _y, float _x );
	void Special( float _y, float _x );

	//draw function
	void Draw();
};

Boss::Boss (ALLEGRO_BITMAP* _b0, ALLEGRO_BITMAP* _b1, ALLEGRO_BITMAP* _b2, ALLEGRO_BITMAP* _b3,
	float _x, float _y, float _speed, short int _frame, float _angle, float _life, short int _state, bool _living)
{
	bitmap[0] = _b0;
	bitmap[1] = _b1;
	bitmap[2] = _b2;
	bitmap[3] = _b3;
	x = _x;
	y = _y;
	speed = _speed;
	frame = _frame;
	angle = _angle;
	life = _life;
	living = _living;
	state = _state;
}

void Boss::Update(float _y, float _x)
{
	switch(state)
	{
	case CHASING:
		Chasing( _y, _x );
		break;
	case RESTING:
		Resting( _y, _x );
		break;
	case ATTACKING:
		Attacking( _y, _x );
		break;
	case SPECIAL:
		Special( _y, _x);
		break;
	}
}

void Boss::Chasing( float _y, float _x)
{
	angle = atan2(y - _y, x - _x);
	frame++;
	x += -cos( angle ) * speed;
	y += -sin( angle ) * speed;

	if( rand()%120 == 7 || x > display_width || x < 0 || 
		y > display_height || y < 0) { speed = 10.0; state = ATTACKING; }
	if( rand()%240 == 13 ) { speed = 20.0; state = ATTACKING; }
	if( rand()%420 == 19 ) { state = RESTING; }
}

void Boss::Resting( float _y, float _x )
{
	if( rand()%360 == 33 ) { state = SPECIAL;}
	if( rand()%180 == 5 )
	{
		angle = atan2(y - _y, x - _x);
		speed = 40.0;
		state = ATTACKING;
	}
	angle = atan2(y - _y, x - _x);
}

void Boss::Attacking( float _y, float _x )
{
	x += -cos( angle ) * speed;
	y += -sin( angle ) * speed;
	frame += speed/2;
	if( rand()%60 == 3 || x > display_width || x < 0 || 
		y > display_height || y < 0) { speed = 1.5; state = CHASING; }
}

void Boss::Special( float _y, float _x )
{
	if( rand()%2 ) { angle = atan2( y - _y, x - _x ); x = rand()%display_width; y = rand()%display_height; }
	if( rand()%50 == 23 ) { state = RESTING; }
}

void Boss::Draw()
{
	al_draw_rotated_bitmap(bitmap[(frame%60)/15], 32, 32, x, y, angle - PI/2, 0); // pura gambiarra o angulo
	al_draw_line(50, 50, display_width - 50, 50, al_map_rgb(153, 51, 0), 10); 
	al_draw_line(50, 50, display_width - 50, 50, al_map_rgb(0, 153, 51), 10); 
}



#endif