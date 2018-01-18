#ifndef LEVELEDDITOR

#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "../_SOURCE Game/Character.h"
#include "../_SOURCE Common/Animations.h"
#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE Game/KeyboardInput.h"

class PlayerCharacter : public Character 
{
	ANIMATION defaultAnimation;
	ANIMATION curentAnimation;
	SpriteSheet *characterSpriteSheet;
	SpriteSheet *characterSpriteSheetFliped;
	SpriteSheet *thoughtBubble;
	KeyState m_keystate, prevKeyState;
	static ANIMATION animationList[5];
	float positionX, positionY, xVelocity, yVelocity, defaultPosX, defaultPosY;
	int state;
	bool isHittingWall;
	int curentFrame = 1;
	int frameCounter = 0;
	int curentAnimationIndex;
	float colitionData[4] = {0 , 0 , 44, 72};
	bool facingRight;
	bool isRunning = false;
	int thought = 0;
	
public:
	PlayerCharacter();
	~PlayerCharacter();
	void load(float X, float Y) override;
	void unload() override;
	void update() override;
	void draw() override;
	void move(int direction = 0);
	void run(int direction = 0);
	void push(bool onXAxis, float pushLevel);
	void jump();
	void die();
	void checkKeyPress(KeyState keyState);
	void switchAnimation(int animationIndex);
	float* getColitionData();
	void fall();
	void checkState();
	void chackWallColition(bool isHittingWall);
	bool getWallColition();
	void hitScealing();
	void drop();
	void reciveThought(int rThought);
	bool endCurentStage();
};

#endif //PLAYER_CHARACTER_H
#endif //LEVELEDDITOR