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

class WallCannon: public DeathTrap
{
	float pos_x;
	float pos_y;
	int animationIndex;
	ANIMATION defaultAnimation{ 11, 11, 0, 1, 1 }, currentAnimation;
	static SpriteSheet* sprites;
	bool arrowIsShot;
private:
	class WallArrow : private DeathTrap
	{
		float pos_x;
		float pos_y;
		float collisionData[4];
		float velocityX;
		float velocityY;
		int animationIndex;
		ANIMATION defaultAnimation = { 4, 4, 0, 1, 1 }, currentAnimation;
		static SpriteSheet* sprites;

	public:
		WallArrow(int x, int y, unsigned int direction);
		~WallArrow();
		static void initSpriteSheet();

		void draw() override;
		float getPositionX() override;
		float getPositionY() override;
		float* getColitionData() override;
		int getCurrentAnimation() override;
		void update();
	};
private:
	WallArrow* m_arrow = NULL;
public:
	WallCannon(int x, int y, int direction);
	~WallCannon();

	static void initSpriteSheet();

	void draw() override;
	float getPositionX() override;
	float getPositionY() override;
	float* getColitionData() override;
	int getCurrentAnimation() override;
	float getTrapPositionX();
	float getTrapPositionY();
	void update();
	void shoot();
};

#endif // !DEATH_TRAPS_H