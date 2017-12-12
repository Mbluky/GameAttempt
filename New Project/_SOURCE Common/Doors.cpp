#include "../_SOURCE Common/Doors.h"

SpriteSheet* Door::sprite;
D2DGraphics* Door::m_gfx;

Door::Door(float X, float Y)
{
	posX = X;
	posY = Y;
}

Door::~Door()
{
}

void Door::draw()
{
	sprite->Draw(1, currentAnimation, posX, posY, 4);
}

float Door::getPositionX()
{
	return posX;
}

float Door::getPositionY()
{
	return posY;
}

float * Door::getColitionData()
{
	collisionData[0] = posX + 5.5f;
	collisionData[1] = posY + 11;
	collisionData[2] = 11;
	collisionData[3] = 22;
	
	return collisionData;
}

void Door::initGFX(D2DGraphics* gfx)
{
	m_gfx = gfx;
	sprite = new SpriteSheet(L"_SOURCE Assets/Default Door.png", m_gfx, true);
}
