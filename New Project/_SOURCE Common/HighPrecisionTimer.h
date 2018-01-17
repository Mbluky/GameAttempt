#ifndef HIGH_PRECISION_TIMER_H
#define HIGH_PRECITION_TIMER_H

#include <windows.h>

class HPTimer
{
	long long startTime;
	long long lastCallToUpdate;
	long long currentCallToUpdate;
	long long frequancy;
	long long ticksPerFrame;
	double frameCounter;
public:
	HPTimer(int FPSLimit)
	{
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequancy = t.QuadPart;
		ticksPerFrame = frequancy / FPSLimit;

		reset();
	}

	void reset()
	{
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		startTime = t.QuadPart;
		currentCallToUpdate = t.QuadPart;
		lastCallToUpdate = t.QuadPart;
	}

	void update()
	{
		LARGE_INTEGER t;
		lastCallToUpdate = currentCallToUpdate;
		QueryPerformanceCounter(&t);
		currentCallToUpdate = t.QuadPart;
	}

	double getTimeTotal()
	{
		double d = currentCallToUpdate - startTime;
		return d / frequancy;
	}
	double getTimeDelta()
	{
		double d = currentCallToUpdate - lastCallToUpdate;
		return d / frequancy;
	}

	double getFrameTotal()
	{
		double d = currentCallToUpdate - startTime;
		return d / ticksPerFrame;
	}

	double getFrameDelta()
	{
		double d = currentCallToUpdate - lastCallToUpdate;
		return d / ticksPerFrame;
	}
	
	void waitForFrame() 
	{
		frameCounter = 0;
		while (frameCounter < 1) 
		{
			update();
			frameCounter += getFrameDelta();
		}
	}
};

#endif