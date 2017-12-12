#ifndef CHARACTER_H
#define CHARACTER_H

#include "../_SOURCE Common/Animations.h"
#include "../_SOURCE Common/D2DGraphics.h"

class Character 
{
protected:
	static D2DGraphics* gfx;
public:
	static void init(D2DGraphics* graphics);
	virtual void load(float X, float Y) = 0;
	virtual void unload() = 0;
	virtual void update() = 0;
	virtual void draw () = 0;
};

#endif //CHARACTER_H
