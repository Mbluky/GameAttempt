#ifndef STAGE_END_DOOR_H
#define STAGE_END_DOOR_H

#include "../_SOURCE Common/SpriteSheet.h"

class Door
{
	static D2DGraphics* m_gfx;

	float posX, posY;
	static SpriteSheet* sprite;
	float collisionData[4];
	ANIMATION  currentAnimation { 11, 22, 0, 1, 1 };
public:
	Door(float X, float Y);
	~Door();

	void draw();
	float getPositionX();
	float getPositionY();
	float* getColitionData();
	static void initGFX(D2DGraphics* gfx);
};

#endif // !STAGE_END_DOOR_H
