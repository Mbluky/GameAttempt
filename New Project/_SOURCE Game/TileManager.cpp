#include "../_SOURCE Game/TileManager.h"
#include <fstream>

using namespace std;

defaultTile* TileManager::stageTiles[30][17];
Spikes* TileManager::stageSpikes[30][17];
WallCannon* TileManager::wallTraps[30][17];
D2DGraphics* TileManager::gfx;
SpriteSheet* TileManager::WorldSpriteSheets[10];
Door* TileManager::stageDoor = NULL;
unsigned int TileManager::m_currentWorld;
unsigned int TileManager::m_currentLevel;
float TileManager::characterPosX;
float TileManager::characterPosY;
string const TileManager::levelList[5][10] = 
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

	x = 0;
	y = 0;

	if (stageDoor != NULL)
	{
		stageDoor->draw();
	}

	while (y<17)
	{
		while (x<30)
		{
			if (wallTraps[x][y] != NULL)
			{
				wallTraps[x][y]->draw();
			}
			x++;
		}
		x = 0;
		y++;
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
			if (stageTiles[x][y] != NULL && !stageTiles[x][y]->getInternal())
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
							isOnTheGround = true;
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
	x = 0;
	y = 0;
	while (y < 17)
	{
		while (x < 30)
		{
			if (wallTraps[x][y] != NULL && wallTraps[x][y]->isShot())
			{
				float deltaX = (wallTraps[x][y]->getColitionData()[0] - P1->getColitionData()[0]);
				float deltaY = (wallTraps[x][y]->getColitionData()[1] - P1->getColitionData()[1]);

				float colitionX = (abs(deltaX) - (wallTraps[x][y]->getColitionData()[2] / 2 + P1->getColitionData()[2] / 2));
				float colitionY = (abs(deltaY) - (wallTraps[x][y]->getColitionData()[3] / 2 + P1->getColitionData()[3] / 2));

				if (colitionX < 0 && colitionY < 0)
				{
					P1->die();
					isDead = true;
					int a = 0, b = 0;
					while (b < 17)
					{
						while (a< 30)
						{
							if (wallTraps[a][b] != NULL)
							{
								wallTraps[a][b]->destroyArrow();
							}
							a++;
						}
						b++;
						a = 0;
					}
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

void TileManager::loadPlayerCharacter(PlayerCharacter * P1)
{
	P1->load(characterPosX, characterPosY);
}

void TileManager::update()
{
	for (unsigned int y = 0; y < 17; y++)
	{
		for (unsigned int x = 0; x < 30; x++)
		{
			if(wallTraps[x][y] != NULL)
			{
				wallTraps[x][y]->shoot();
				wallTraps[x][y]->update();
				for (unsigned int y1 = 0; y1 < 17; y1++)
				{
					for (unsigned int x1 = 0; x1 < 30; x1++)
					{
						if (stageTiles[x1][y1] != NULL && !stageTiles[x1][y1]->getInternal())
						{
							float deltaX = (stageTiles[x1][y1]->getColitionData()[0] - wallTraps[x][y]->getColitionData()[0]);
							float deltaY = (stageTiles[x1][y1]->getColitionData()[1] - wallTraps[x][y]->getColitionData()[1]);

							float colitionX = (abs(deltaX) - (stageTiles[x1][y1]->getColitionData()[2] / 2 + wallTraps[x][y]->getColitionData()[2] / 2));
							float colitionY = (abs(deltaY) - (stageTiles[x1][y1]->getColitionData()[3] / 2 + wallTraps[x][y]->getColitionData()[3] / 2));

							if (colitionX < 0 && colitionY < 0)
							{
								if (x != x1 || y != y1)
								{
									wallTraps[x][y]->destroyArrow();
								}									
							}
						}
					
					}
				}
			}
		}
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
	x = 0;
	y = 0;
	while (y<17)
	{
		while (x < 30)
		{
			LevelFile >> isEmpty;
			if (isEmpty == 0)
			{
				wallTraps[x][y] = NULL;
			}
			else
			{
				LevelFile >> posX;
				LevelFile >> posY;
				LevelFile >> sprite;

				wallTraps[x][y] = new WallCannon((float)posX, (float)posY, sprite);
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

	LevelFile >> isEmpty;
	if(isEmpty == 0)
	{
		characterPosX = 0.0f;
		characterPosY = 0.0f;
	}else
	{
		LevelFile >> characterPosX;
		LevelFile >> characterPosY;
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
}


