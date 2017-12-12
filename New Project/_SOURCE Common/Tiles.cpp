#include "../_SOURCE Common/Tiles.h"

defaultTile::defaultTile(float x, float y, int currentAnimationNumber, SpriteSheet* spriteSheetPointer)
{
	positionX = x;
	positionY = y;
	curentAnimation = { 11, 11, currentAnimationNumber * 11, 1, 1 };
	ColitionData[0] = (positionX + ColitionData[2] / 2);
	ColitionData[1] = (positionY + ColitionData[3] / 2);
	spriteSheet = spriteSheetPointer;
}

defaultTile::~defaultTile()
{
}

void defaultTile::draw()
{
	spriteSheet->Draw(1, curentAnimation, positionX, positionY);
}

void defaultTile::getSpriteSheet(SpriteSheet * spriteSheet_)
{
	spriteSheet = spriteSheet_;
}

float defaultTile::getPositionX()
{
	return positionX;
}

float defaultTile::getPositionY()
{
	return positionY;
}

int defaultTile::getCurrentAnimation()
{
	return curentAnimation.startY/11;
}

float * defaultTile::getColitionData()
{
	return ColitionData;
}

bool defaultTile::getInternal()
{
	if (curentAnimation.startY == 77)
	{
		return true;
	}
	else 
		return false;
}

