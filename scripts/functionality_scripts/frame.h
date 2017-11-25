#ifndef FRAME_H
#define FRAME_H

class Frame
{
public:
	Frame();
	Frame(int x);
	int frameCount;
	int frameDelay;

	void resetFrameCount();
	void Set_count_delay(int frame_delay);
};


Frame::Frame()
{}

Frame::Frame(int x)
{
	this->frameCount = 0;
	this->frameDelay = x;
}
void Frame::resetFrameCount()
{
	this->frameCount = 0;
}

void Frame::Set_count_delay(int frame_delay)
{
	this->frameCount = 0;
	this->frameDelay = frame_delay;
}


#endif
