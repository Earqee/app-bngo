#ifndef FRAME_H
#define FRAME_H

class Frame
{
public:
	Frame();
	int frameCount;
	int frameDelay;
}

Frame::Frame(int x)
{
	this->frameCount = 0;
	this->frameDelay = x;
}


#endif