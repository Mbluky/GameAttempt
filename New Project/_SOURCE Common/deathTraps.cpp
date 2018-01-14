#include "../_SOURCE Common/deathTraps.h"

D2DGraphics* DeathTrap::gfx = NULL;

SpriteSheet* Spikes::sprites = NULL;

SpriteSheet* WallCannon::sprites = NULL;

SpriteSheet* WallCannon::WallArrow::sprites = NULL;

void DeathTrap::initGFX(D2DGraphics* graphics)
{
	gfx = graphics;
	Spikes::initSpriteSheet();
	WallCannon::initSpriteSheet();
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

WallCannon::WallCannon(int x, int y, int direction)
{
	pos_x = x;
	pos_y = y;
	animationIndex = direction;
	currentAnimation = { 11, 11, (animationIndex * 11), 1, 1 };
	arrowIsShot = 0;
}

WallCannon::~WallCannon()
{
	delete m_arrow;
}

void WallCannon::initSpriteSheet()
{
	sprites = new SpriteSheet(L"_SOURCE Assets/WallTraps.png", gfx, true);
	WallArrow::initSpriteSheet();
}

void WallCannon::draw()
{
	sprites->Draw(1, currentAnimation, pos_x, pos_y);
}

float WallCannon::getPositionX()
{
	return m_arrow->getPositionX();
}

float WallCannon::getPositionY()
{
	return m_arrow->getPositionY();
}

float * WallCannon::getColitionData()
{
	return m_arrow->getColitionData();
}

int WallCannon::getCurrentAnimation()
{
	return m_arrow->getCurrentAnimation();
}

float WallCannon::getTrapPositionX()
{
	return pos_x;
}

float WallCannon::getTrapPositionY()
{
	return pos_y;
}


void WallCannon::update()
{
	m_arrow->update();
}

void WallCannon::shoot()
{
	switch (animationIndex)
	{
	case 0:
		m_arrow = new WallArrow(pos_x, pos_y + 16, animationIndex);
		break;
	case 1:
		m_arrow = new WallArrow(pos_x + 16, pos_y, animationIndex);
		break;
	case 2:
		m_arrow = new WallArrow(pos_x + 16, pos_y + 16, animationIndex);
		break;
	case 3:
		m_arrow = new WallArrow(pos_x + 16, pos_y - 16, animationIndex);
		break;
	}
}

WallCannon::WallArrow::WallArrow(int x, int y, unsigned int direction)
{
	pos_x = x;
	pos_y = y;
	animationIndex = direction;
	currentAnimation = { 4, 4, (animationIndex * 4), 1, 1 };
	switch (animationIndex)
	{
	case 0:
		velocityX = -10;
		velocityY = 0;
		break;
	case 1:
		velocityX = 0;
		velocityY = -10;
		break;
	case 2:
		velocityX = 10;
		velocityY = 0;
		break;
	case 3:
		velocityX = 0;
		velocityY = 10;
	}
}

WallCannon::WallArrow::~WallArrow()
{
}

void WallCannon::WallArrow::initSpriteSheet()
{
	sprites = new SpriteSheet(L"_SOURCE Assets/WallArrows.png", gfx, true);
}

void WallCannon::WallArrow::draw()
{
	sprites->Draw(1, currentAnimation, pos_x, pos_y, 4);
}

float WallCannon::WallArrow::getPositionX()
{
	return pos_x;
}

float WallCannon::WallArrow::getPositionY()
{
	return pos_y;
}

float * WallCannon::WallArrow::getColitionData()
{
	if(animationIndex == 0 || animationIndex == 2)
	{
		collisionData[0] = pos_x + 8;
		collisionData[1] = pos_y + 4;
		collisionData[2] = 16;
		collisionData[3] = 8;
	}else
	{
		collisionData[0] = pos_x + 4;
		collisionData[1] = pos_y + 8;
		collisionData[2] = 8;
		collisionData[3] = 16;
	}
	return collisionData;
}

int WallCannon::WallArrow::getCurrentAnimation()
{
	return animationIndex;
}

void WallCannon::WallArrow::update()
{
	pos_x += velocityX;
	pos_y += velocityY;
}
