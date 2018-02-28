#ifndef PLAYER_SPRITE_HEADER
#define PLAYER_SPRITE_HEADER

#include "../_SOURCE Common/SpriteSheet.h"

class P1
{
	float posX, posY;
	static SpriteSheet* p1;
	ANIMATION defaultAnimation{ 11, 18, 0, 1, 1 };
public:
	P1(float X, float Y)
	{
		posX = X;
		posY = Y;
	}
	~P1()
	{
		delete p1;
	}
	
	static void initGFX(D2DGraphics* gfx)
	{
		p1 = new SpriteSheet(L"_SOURCE Assets/SpriteSheet 0.2.png", gfx, true);
	}

	void draw()
	{
		if (p1 != NULL) 
		{
			p1->Draw(1, defaultAnimation, posX, posY);
		}
	}
	float getPosX()
	{
		return posX;
	}
	float getPosY()
	{
		return posY;
	}
};

#endif // !PLAYER_SPRITE_HEADER