#ifndef PLAYER_SPRITE_HEADER
#define PLAYER_SPRITE_HEADER

#include "../_SOURCE Common/SpriteSheet.h"

class P1
{
	float posX, posY;
	SpriteSheet* p1;
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
	void draw()
	{
		p1->Draw(1, defaultAnimation, posX, posY);
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