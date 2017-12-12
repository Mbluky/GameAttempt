#include "../_SOURCE Game/TileManager.h"
#include <fstream>

using namespace std;

defaultTile* TileManager::stageTiles[30][17];
Spikes* TileManager::stageSpikes[30][17];
D2DGraphics* TileManager::gfx;
SpriteSheet* TileManager::WorldSpriteSheets[10];
Door* TileManager::stageDoor = NULL;
int TileManager::m_currentWorld;
int TileManager::m_currentLevel;
string const TileManager::levelList[10][10] = 
{
	("Levels/World1/Level1.txt"),
	("Levels/World1/Level2.txt"),
	("Levels/World1/Level3.txt"),
	("Levels/World1/Level4.txt"),
	("Levels/World1/Level5.txt"),
	("Levels/World1/Level6.txt"),
	("Levels/World1/Level7.txt"),
	("Levels/World1/Level8.txt"),
	("Levels/World1/Level9.txt"),
	("Levels/World1/Level10.txt"),
	("Levels/World2/Level1.txt"),
	("Levels/World2/Level2.txt"),
	("Levels/World2/Level3.txt"),
	("Levels/World2/Level4.txt"),
	("Levels/World2/Level5.txt"),
	("Levels/World2/Level6.txt"),
	("Levels/World2/Level7.txt"),
	("Levels/World2/Level8.txt"),
	("Levels/World2/Level9.txt"),
	("Levels/World2/Level10.txt"),
	("Levels/World3/Level1.txt"),
	("Levels/World3/Level2.txt"),
	("Levels/World3/Level3.txt"),
	("Levels/World3/Level4.txt"),
	("Levels/World3/Level5.txt"),
	("Levels/World3/Level6.txt"),
	("Levels/World3/Level7.txt"),
	("Levels/World3/Level8.txt"),
	("Levels/World3/Level9.txt"),
	("Levels/World3/Level10.txt"),
	("Levels/World4/Level1.txt"),
	("Levels/World4/Level2.txt"),
	("Levels/World4/Level3.txt"),
	("Levels/World4/Level4.txt"),
	("Levels/World4/Level5.txt"),
	("Levels/World4/Level6.txt"),
	("Levels/World4/Level7.txt"),
	("Levels/World4/Level8.txt"),
	("Levels/World4/Level9.txt"),
	("Levels/World4/Level10.txt"),
	("Levels/World5/Level1.txt"),
	("Levels/World5/Level2.txt"),
	("Levels/World5/Level3.txt"),
	("Levels/World5/Level4.txt"),
	("Levels/World5/Level5.txt"),
	("Levels/World5/Level6.txt"),
	("Levels/World5/Level7.txt"),
	("Levels/World5/Level8.txt"),
	("Levels/World5/Level9.txt"),
	("Levels/World5/Level10.txt"),
	("Levels/World6/Level1.txt"),
	("Levels/World6/Level2.txt"),
	("Levels/World6/Level3.txt"),
	("Levels/World6/Level4.txt"),
	("Levels/World6/Level5.txt"),
	("Levels/World6/Level6.txt"),
	("Levels/World6/Level7.txt"),
	("Levels/World6/Level8.txt"),
	("Levels/World6/Level9.txt"),
	("Levels/World6/Level10.txt"),
	("Levels/World7/Level1.txt"),
	("Levels/World7/Level2.txt"),
	("Levels/World7/Level3.txt"),
	("Levels/World7/Level4.txt"),
	("Levels/World7/Level5.txt"),
	("Levels/World7/Level6.txt"),
	("Levels/World7/Level7.txt"),
	("Levels/World7/Level8.txt"),
	("Levels/World7/Level9.txt"),
	("Levels/World7/Level10.txt"),
	("Levels/World8/Level1.txt"),
	("Levels/World8/Level2.txt"),
	("Levels/World8/Level3.txt"),
	("Levels/World8/Level4.txt"),
	("Levels/World8/Level5.txt"),
	("Levels/World8/Level6.txt"),
	("Levels/World8/Level7.txt"),
	("Levels/World8/Level8.txt"),
	("Levels/World8/Level9.txt"),
	("Levels/World8/Level10.txt"),
	("Levels/World9/Level1.txt"),
	("Levels/World9/Level2.txt"),
	("Levels/World9/Level3.txt"),
	("Levels/World9/Level4.txt"),
	("Levels/World9/Level5.txt"),
	("Levels/World9/Level6.txt"),
	("Levels/World9/Level7.txt"),
	("Levels/World9/Level8.txt"),
	("Levels/World9/Level9.txt"),
	("Levels/World9/Level10.txt"),
	("Levels/World10/Level1.txt"),
	("Levels/World10/Level2.txt"),
	("Levels/World10/Level3.txt"),
	("Levels/World10/Level4.txt"),
	("Levels/World10/Level5.txt"),
	("Levels/World10/Level6.txt"),
	("Levels/World10/Level7.txt"),
	("Levels/World10/Level8.txt"),
	("Levels/World10/Level9.txt"),
	("Levels/World10/Level10.txt"),
};


void TileManager::drawTiles()
{
	int x = 0;
	int y = 0;
	while (y<17)
	{
		while (x<30)
		{
			if(stageTiles[x][y] != NULL)
			{
				stageTiles[x][y]->draw();
			}
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;

	while (y<17)
	{
		while (x<30)
		{
			if (stageSpikes[x][y] != NULL)
			{
				stageSpikes[x][y]->draw();
			}
			x++;
		}
		x = 0;
		y++;
	}
	if(stageDoor != NULL)
	{
		stageDoor->draw();
	}
}

void TileManager::checkColition(PlayerCharacter * P1)
{
	int x = 0;
	int y = 0;
	bool isOnTheGround = false;
	bool isHittingWall = false;
	bool isDead = false;

	while (y < 17)
	{
		while (x < 30)
		{
			if (stageTiles[x][y] != NULL && stageTiles[x][y]->getInternal() == false)
			{
				float deltaX = (stageTiles[x][y]->getColitionData()[0] - P1->getColitionData()[0]);
				float deltaY = (stageTiles[x][y]->getColitionData()[1] - P1->getColitionData()[1]);

				float colitionX = (abs(deltaX) - (stageTiles[x][y]->getColitionData()[2] / 2 + P1->getColitionData()[2] / 2));
				float colitionY = (abs(deltaY) - (stageTiles[x][y]->getColitionData()[3] / 2 + P1->getColitionData()[3] / 2));

				if (colitionX < 0 && colitionY < 0)
				{
					if (colitionX > colitionY)
					{
						if (deltaX > 0)
						{
							P1->push(true, colitionX);
							P1->chackWallColition(true);
							isHittingWall = true;
						}
						else
						{
							P1->push(true, -colitionX);
							P1->chackWallColition(true);
							isHittingWall = true;
						}
					}else if (colitionY > colitionX)
					{
						if (deltaY < 0)
						{
							P1->push(false, -colitionY);
							if (!P1->getWallColition())
							{
								P1->hitScealing();
							}
						}
						else if (deltaY > 0 )
						{
							P1->push(false, +colitionY);
							P1->drop();
						}
					
					}
				}
				if (colitionY == 0 && colitionX < 0 && deltaY > 0)
				{
					P1->drop();
					isOnTheGround = true;
				}
			}
			x++;
		}
		x = 0;
		y++;
	}

	x = 0;
	y = 0;
	P1->reciveThought(0);
	if (stageDoor != NULL)
	{
		float deltaX = (stageDoor->getColitionData()[0] - P1->getColitionData()[0]);
		float deltaY = (stageDoor->getColitionData()[1] - P1->getColitionData()[1]);

		float colitionX = (abs(deltaX) - (stageDoor->getColitionData()[2] / 2 + P1->getColitionData()[2] / 2));
		float colitionY = (abs(deltaY) - (stageDoor->getColitionData()[3] / 2 + P1->getColitionData()[3] / 2));

		if (colitionX < 0 && colitionY < 0)
		{
			P1->reciveThought(1);
		}
	}
	while (y < 17)
	{
		while (x < 30)
		{
			if (stageSpikes[x][y] != NULL)
			{
				float deltaX = (stageSpikes[x][y]->getColitionData()[0] - P1->getColitionData()[0]);
				float deltaY = (stageSpikes[x][y]->getColitionData()[1] - P1->getColitionData()[1]);

				float colitionX = (abs(deltaX) - (stageSpikes[x][y]->getColitionData()[2] / 2 + P1->getColitionData()[2] / 2));
				float colitionY = (abs(deltaY) - (stageSpikes[x][y]->getColitionData()[3] / 2 + P1->getColitionData()[3] / 2));

				if (colitionX < 0 && colitionY < 0)
				{
					P1->die();
					isDead = true;
				}
			}
			x++;
			
		}
		x = 0;
		y++;

	}
	if(!isDead)
	{
		if (!isOnTheGround)
		{
			P1->checkState();
		}
		P1->chackWallColition(isHittingWall);
	}
}

void TileManager::loadStageTiles(int currentWorld, int currentLevel)
{
	m_currentWorld = currentWorld;
	m_currentLevel = currentLevel;

	fstream LevelFile(levelList[currentWorld][currentLevel].c_str());
	

	int x = 0; int y = 0;
	
	int isEmpty, posX, posY, sprite;

	while (y<17)
	{
		while (x < 30)
		{
			LevelFile >> isEmpty;
			if(isEmpty == 0)
			{
				stageTiles[x][y] = NULL;
			}
			else
			{
				LevelFile >> posX;
				LevelFile >> posY;
				LevelFile >> sprite;

				stageTiles[x][y] = new defaultTile(posX, posY, sprite, WorldSpriteSheets[currentWorld]);
			}
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;
	while (y<17)
	{
		while (x < 30)
		{
			LevelFile >> isEmpty;
			if (isEmpty == 0)
			{
				stageSpikes[x][y] = NULL;
			}
			else
			{
				LevelFile >> posX;
				LevelFile >> posY;
				LevelFile >> sprite;

				stageSpikes[x][y] = new Spikes((float)posX, (float)posY, sprite);
			}
			x++;
		}
		x = 0;
		y++;
	}
	LevelFile >> isEmpty;
	if(isEmpty == 0)
	{
		stageDoor == NULL;
	}else
	{
		LevelFile >> posX;
		LevelFile >> posY;
		stageDoor = new Door(posX, posY);
	}
}

void TileManager::initGFX(D2DGraphics * _gfx)
{
	gfx = _gfx;
	WorldSpriteSheets[0] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[1] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[2] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[3] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[4] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[5] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[6] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[7] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[8] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
	WorldSpriteSheets[9] = new SpriteSheet(L"_SOURCE Assets/defaultTiles.png", gfx, true);
}


