#ifndef DEATH_TRAPS_H
#define DEATH_TRAPS_H

#include "../_SOURCE Common/SpriteSheet.h"

class DeathTrap
{
protected:
	static D2DGraphics* gfx;
public:
	static void initGFX(D2DGraphics* graphics);
	virtual void draw() = 0;
	virtual float getPositionX() = 0;
	virtual float getPositionY() = 0;
	virtual float* getColitionData() = 0;
	virtual int getCurrentAnimation() = 0;
};

class Spikes: public DeathTrap
{
	float pos_x;
	float pos_y;
	float collisionData[4];
	int animationIndex;
	ANIMATION defaultAnimation = { 11, 11, 0, 1, 1 }, currentAnimation;
	static SpriteSheet* sprites;

public:
	Spikes(float X, float Y, int spikeDirection);
	~Spikes();
	static void initSpriteSheet();

	void draw() override;
	float getPositionX() override;
	float getPositionY() override;
	float* getColitionData() override;
	int getCurrentAnimation() override;
};
#endif // !DEATH_TRAPS_H