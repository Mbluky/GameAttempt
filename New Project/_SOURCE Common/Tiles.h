#ifndef TILE_CLASS_H
#define TILE_CLASS_H

#include "../_SOURCE Game/Character.h"
#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE Game/PlayerCharacter.h"


class defaultTile
{
	float positionX, positionY;
	ANIMATION defaultAnimation, curentAnimation;
	SpriteSheet* spriteSheet;
	int animationIndex;
	float ColitionData[4] = { 0, 0, 44, 44 };
public:
	defaultTile(float x, float y, int currentAnimationNumber, SpriteSheet * spriteSheetPointer);
	~defaultTile();
	void draw();
	void getSpriteSheet(SpriteSheet* spriteSheet_);
	float getPositionX();
	float getPositionY();
	int getCurrentAnimation();
	float* getColitionData();
	bool getInternal();
};

#endif // !TILE_CLASS_H