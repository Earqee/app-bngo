#ifndef FRAME_H
#define FRAME_H

class Frame
{
public:
	Frame(int x);
	int frameCount;
	int frameDelay;

	void resetFrameCount();
};

Frame::Frame(int x)
{
	this->frameCount = 0;
	this->frameDelay = x;
}
void Frame::resetFrameCount()
{
	this->frameCount = 0;
}


#endif
