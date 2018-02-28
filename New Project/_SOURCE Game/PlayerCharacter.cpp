#include "../_SOURCE Game/PlayerCharacter.h"
#include <tchar.h>

ANIMATION PlayerCharacter::animationList[5]
{
	{11,18,0,1,10}, {13,18,18,5,10}, {11,18,72,2,10}, {0,0,0,0,0}, {0,0,0,0,0}
};

PlayerCharacter::PlayerCharacter()
{
	defaultAnimation = animationList[0];
	curentAnimationIndex = 0;
	curentAnimation = defaultAnimation;
	facingRight = true;
	state = 0;
	m_keystate = { false, false, false, false, false, false, false, false };
}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::load(float X, float Y)
{
	positionX = X;
	positionY = Y;
	defaultPosX = X;
	defaultPosY = Y;
	xVelocity = 0.0f;
	yVelocity = 0.0f;
	thought = 0;

	TCHAR * fileName = _TEXT("_SOURCE Sound//footstep.wav");
	footStep = new Sound(fileName);

	fileName = _TEXT("_SOURCE Sound//jump.wav");
	m_jump = new Sound(fileName);

	fileName = _TEXT("_SOURCE Sound//landing.wav");
	m_land = new Sound(fileName);

	characterSpriteSheet = new SpriteSheet(L"_SOURCE Assets/spriteSheet 0.2.png", gfx, true);
	characterSpriteSheetFliped = new SpriteSheet(L"_SOURCE Assets/spriteSheet 0.2 flipped.png", gfx, false);
	thoughtBubble = new SpriteSheet(L"_Source Assets/Arrow up.png", gfx, false);
}

void PlayerCharacter::unload()
{
	state = 0;
	delete footStep;
	delete m_jump;
	delete m_land;
	delete characterSpriteSheet;
	delete characterSpriteSheetFliped;
	delete thoughtBubble;
}

void PlayerCharacter::update()
{
	positionX += xVelocity;
	positionY += yVelocity;
	fall();
	if (curentAnimationIndex == 2)
	{
		frameCounter = 2;
	}
	else
	{
		frameCounter++;
	}
	if (positionX > 1290 || positionX < -60)
	{
		die();
	}
	if(positionY > 730 || positionY < -150)
	{
		die();
	}
}

void PlayerCharacter::draw()
{
	if (facingRight)
	{
		characterSpriteSheet->Draw(curentFrame, curentAnimation, positionX, positionY);
		if (frameCounter >= (60.0f / curentAnimation.FPS))
		{
			curentFrame++;
			frameCounter = 0;
		}
	}else
	{
		characterSpriteSheetFliped->Draw(curentFrame, curentAnimation, positionX, positionY);
		if (frameCounter >= (60.0f / curentAnimation.FPS))
		{
			curentFrame++;
			frameCounter = 0;
		}
	}
	if(thought > 0)
	{
		thoughtBubble->Draw(1, { 8, 8, (thought - 1) * 8, 1, 1 }, positionX + 4, positionY - 36);
	}
}

void PlayerCharacter::move(int direction)
{
	if (direction == 1)
	{
		xVelocity = 6.0f;
	}
	else
	if (direction == 2)
	{
		xVelocity = -6.0f;
	}
	else if (direction == 0)
	{
		xVelocity = 0;
	}
}

void PlayerCharacter::run(int direction)
{
	if(direction == 0)
	{
		xVelocity = 0;
	}else if(direction == 1)
	{
		xVelocity = 10;	
	}else if(direction == 2)
	{
		xVelocity = -10;
	}
}

void PlayerCharacter::push(bool onXAxis, float pushLevel)
{
	if(onXAxis)
	{
		positionX += pushLevel;
	}
	else
	{
		positionY += pushLevel;
	}
}

void PlayerCharacter::jump()
{
	if (state == 0)
	{
		state = 1;
		yVelocity = -15.5f;
		switchAnimation(2);
		m_jump->Play(1.0f, 0.5f);
	}
}

void PlayerCharacter::die()
{
	state = 0;
	xVelocity = 0;
	yVelocity = 0;
	m_land->Play(1.0f, 0.1f);
	positionX = defaultPosX;
	positionY = defaultPosY;
}

void PlayerCharacter::checkKeyPress(KeyState keyState)
{
	prevKeyState = m_keystate;
	m_keystate = keyState;
	if(keyState.right && !keyState.left)
	{
		if(keyState.run)
		{
			run(1);
			if(state == 0)
			{
				switchAnimation(1);
				facingRight = true;
			}
		}
		else 
		{
			move(1);
			if (state == 0)
			{
				switchAnimation(1);
				facingRight = true;
			}
		}
	}
	else if (keyState.left && !keyState.right)
	{
		if (keyState.run)
		{
			run(2);
			if (state == 0)
			{
				switchAnimation(1);
				facingRight = false;
			}
		}
		else
		{
			move(2);
			if (state == 0)
			{
				switchAnimation(1);
				facingRight = false;
			}
		}
	}
	else 
	{
		move(0);
		if (state == 0)
		{
			switchAnimation(0);
		}
	}

	if (keyState.jump && !prevKeyState.jump)
	{
		jump();
	}
}

void PlayerCharacter::switchAnimation(int animationIndex)
{
	if(curentAnimationIndex != animationIndex)
	{
		curentAnimation = animationList[animationIndex];
		curentAnimationIndex = animationIndex;
		curentFrame = 01;
	}
}

float* PlayerCharacter::getColitionData()
{
	colitionData[0] = (positionX + 22);
	colitionData[1] = (positionY + 36);
	colitionData[2] = 22;
	colitionData[3] = 72;


	return colitionData;
}

void PlayerCharacter::fall()
{
	if(state == 1 && yVelocity < 21)
	{
		yVelocity += 1;
	}
}

void PlayerCharacter::checkState()
{
	state = 1;
}

void PlayerCharacter::chackWallColition(bool isHittingWall)
{
	this->isHittingWall = isHittingWall;
}

bool PlayerCharacter::getWallColition()
{
	return isHittingWall;
}

void PlayerCharacter::hitScealing()
{
	yVelocity = 0;
	m_land->Play(1.0f, 0.25f);
}

void PlayerCharacter::drop()
{
	if (yVelocity >= 0)
	{
		state = 0;
		yVelocity = 0;
	}
}

void PlayerCharacter::reciveThought(int rThought)
{
	thought = rThought;
}

bool PlayerCharacter::endCurentStage()
{
	if (thought != 1)
	{
		return false;
	}else
	{
		return true;
	}
}

