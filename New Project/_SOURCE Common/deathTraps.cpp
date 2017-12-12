#include "../_SOURCE Common/deathTraps.h"

D2DGraphics* DeathTrap::gfx = NULL;

SpriteSheet* Spikes::sprites = NULL;

void DeathTrap::initGFX(D2DGraphics* graphics)
{
	gfx = graphics;
	Spikes::initSpriteSheet();
}

Spikes::Spikes(float X, float Y, int spikeDirection)
{
	pos_x = X;
	pos_y = Y;
	animationIndex = spikeDirection;
	currentAnimation = { 11, 11, spikeDirection * 11, 1, 1 };
	switch (spikeDirection)
	{
	case(0):
		collisionData[0] = pos_x + 22;
		collisionData[1] = pos_y + 40;
		collisionData[2] = 44;
		collisionData[3] = 8;
		break;
	case(1):
		collisionData[0] = pos_x + 4;
		collisionData[1] = pos_y + 22;
		collisionData[2] = 8;
		collisionData[3] = 44;
		break;
	case(2):
		collisionData[0] = pos_x + 22;
		collisionData[1] = pos_y + 4;
		collisionData[2] = 44;
		collisionData[3] = 8;
		break;
	case(3):
		collisionData[0] = pos_x + 40;
		collisionData[1] = pos_y + 22;
		collisionData[2] = 8;
		collisionData[3] = 44;
		break;
	case(4):
		collisionData[0] = pos_x + 14;
		collisionData[1] = pos_y + 40;
		collisionData[2] = 28;
		collisionData[3] = 8;
		break;
	case(5):
		collisionData[0] = pos_x + 30;
		collisionData[1] = pos_y + 40;
		collisionData[2] = 28;
		collisionData[3] = 8;
		break;
	case(6):
		collisionData[0] = pos_x + 4;
		collisionData[1] = pos_y + 14;
		collisionData[2] = 8;
		collisionData[3] = 28;
		break;
	case(7):
		collisionData[0] = pos_x + 4;
		collisionData[1] = pos_y + 30;
		collisionData[2] = 8;
		collisionData[3] = 28;
		break;
	case(8):
		collisionData[0] = pos_x + 14;
		collisionData[1] = pos_y + 4;
		collisionData[2] = 28;
		collisionData[3] = 8;
		break;
	case(9):
		collisionData[0] = pos_x + 30;
		collisionData[1] = pos_y + 4;
		collisionData[2] = 28;
		collisionData[3] = 8;
		break;
	case(10):
		collisionData[0] = pos_x + 40;
		collisionData[1] = pos_y + 30;
		collisionData[2] = 8;
		collisionData[3] = 28;
		break;
	case(11):
		collisionData[0] = pos_x + 40;
		collisionData[1] = pos_y + 14;
		collisionData[2] = 8;
		collisionData[3] = 28;
		break;
	case(12):
		collisionData[0] = pos_x + 22;
		collisionData[1] = pos_y + 40;
		collisionData[2] = 12;
		collisionData[3] = 8;
		break;
	case(13):
		collisionData[0] = pos_x + 4;
		collisionData[1] = pos_y + 22;
		collisionData[2] = 8;
		collisionData[3] = 12;
		break;
	case(14):
		collisionData[0] = pos_x + 22;
		collisionData[1] = pos_y + 4;
		collisionData[2] = 12;
		collisionData[3] = 8;
		break;
	case(15):
		collisionData[0] = pos_x + 40;
		collisionData[1] = pos_y + 22;
		collisionData[2] = 8;
		collisionData[3] = 12;
		break;
	}
}

Spikes::~Spikes()
{
	delete sprites;
}

void Spikes::initSpriteSheet()
{
	sprites = new SpriteSheet(L"_SOURCE Assets/Spikes.png", gfx, true);
}

void Spikes::draw()
{
	sprites->Draw(1, currentAnimation, pos_x, pos_y);
}

float Spikes::getPositionX()
{
	return pos_x;
}

float Spikes::getPositionY()
{
	return pos_y;
}

float * Spikes::getColitionData()
{
	return collisionData;
}

int Spikes::getCurrentAnimation()
{
	return animationIndex;
}