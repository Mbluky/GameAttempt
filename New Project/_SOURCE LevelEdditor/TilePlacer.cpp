#include "../_SOURCE LevelEdditor/TilePlacer.h"
#include <fstream>

TilePlacer::TilePlacer()
{
	posX = 0;
	posY = 0;
	initStageTiles();
	onlyAnimation = { 11, 11, 0, 1, 1 };
	justMoved = false;
	moveCountDown = 5;
	curentMode = 0;
	curentTile = 0;
	curentSpriteSheet = 0;
	TileSpriteSheets[0] = (L"_SOURCE Assets/defaultTiles.png");
	TileSpriteSheets[1] = (L"_SOURCE Assets/RustyTile.png");
	keyState = { false, false, false, false, false, false, false, false};
	prevKeyState = { false, false, false, false, false, false, false, false};
	stageDoor = NULL;
}

TilePlacer::~TilePlacer()
{
	delete StageTiles;
}

void TilePlacer::initStageTiles()
{
	int x(0), y(0);
	while (x <= 29)
	{
		while (y <= 16)
		{
			StageTiles[x][y] = NULL;
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;

	while (x <= 29)
	{
		while (y <= 16)
		{
			stageSpikes[x][y] = NULL;
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;

	while (x <= 29)
	{
		while (y <= 16)
		{
			wallTraps[x][y] = NULL;
			y++;
		}
		y = 0;
		x++;
	}

}

void TilePlacer::getInput(E_KeyState keyState_)
{
	prevKeyState = keyState;
	keyState = keyState_;
}

void TilePlacer::getGFX(D2DGraphics* GFX)
{
	gfx = GFX;
	TilePlacerCursor = new SpriteSheet(L"_SOURCE Assets/Selecter.png", gfx, true);
	curentTileSet = new SpriteSheet(TileSpriteSheets[curentSpriteSheet], gfx, true);
	curentspikeSprites = new SpriteSheet(L"_SOURCE Assets/Spikes.png", gfx, true);
}

void TilePlacer::moveCursor()
{
	if (!justMoved)
	{
		if (keyState.left && !keyState.right && !keyState.up && !keyState.down)
		{
			if (posX > 0)
			{
				posX -= 44;
			}
		}
		if (!keyState.left && keyState.right && !keyState.up && !keyState.down)
		{
			if (posX < 1276)
			{
				posX += 44;
			}
		}
		if (!keyState.left && !keyState.right && keyState.up && !keyState.down)
		{
			if (posY > 0)
			{
				posY -= 44;
			}
		}
		if (!keyState.left && !keyState.right && !keyState.up && keyState.down)
		{
			if (posY < 704)
			{
				posY += 44;
			}
		}
		justMoved = true;
	}
	else
	{
		if (moveCountDown > 0)
		{
			moveCountDown--;
		}
		else
		{
			moveCountDown = 5;
			justMoved = false;
		}
	}
}

void TilePlacer::placeTile()
{
	if (curentMode == 0)
	{
		StageTiles[(int)posX / 44][(int)posY / 44] = new defaultTile(posX, posY, curentTile, curentTileSet);
	}else if (curentMode == 1)
	{	
		stageSpikes[(int)posX / 44][(int)posY / 44] = new Spikes(posX, posY, curentTile);
	}
	else if(curentMode == 2)
	{
		stageDoor = new Door(posX, posY);
	}
	else if(curentMode == 3)
	{
		wallTraps[(int)posX / 44][(int)posY / 44] = new WallCannon(posX, posY, curentTile);
	}
}
 void TilePlacer::removeTile()
 {
	 if (curentMode == 0) 
	 {
		 StageTiles[(int)posX / 44][(int)posY / 44] = NULL;
	 }else if(curentMode == 1)
	 {
		 stageSpikes[(int)posX / 44][(int)posY / 44] = NULL;
	 }else if(curentMode == 2)
	 {
		 stageDoor = NULL;
	 }
	 else if(curentMode == 3)
	 {
		 wallTraps[(int)posX / 44][(int)posY / 44] = NULL;
	 }
 }

void TilePlacer::changeTile()
{
	if (curentMode == 0 || curentMode == 1) 
	{
		if (keyState.nextTile && !prevKeyState.nextTile)
		{
			curentTile++;
			if (curentTile > 15)
			{
				curentTile = 0;
			}
		}
		else if (keyState.previousTile && !prevKeyState.previousTile)
		{
			curentTile--;
			if (curentTile < 0)
			{
				curentTile = 15;
			}
		}
	}else if(curentMode == 3)
	{
		if (keyState.nextTile && !prevKeyState.nextTile)
		{
			curentTile++;
			if (curentTile > 4)
			{
				curentTile = 0;
			}
		}
	}
}

void TilePlacer::drawStageTiles()
{
	int x(0), y(0);
	while (x <= 29)
	{
		while (y <= 16)
		{
			if(StageTiles[x][y] != NULL)
			{
				StageTiles[x][y]->draw();
			}
			y++;
		}
		y = 0;
		x++;
	}

	x = 0; y = 0;

	while (x <= 29)
	{
		while (y <= 16)
		{
			if (stageSpikes[x][y] != NULL)
			{
				stageSpikes[x][y]->draw();
			}
			y++;
		}
		y = 0;
		x++;
	}

	x = 0;
	y = 0;

	while (x <= 29)
	{
		while (y <= 16)
		{
			if (wallTraps[x][y] != NULL)
			{
				wallTraps[x][y]->draw();
			}
			y++;
		}
		y = 0;
		x++;
	}

	if (stageDoor != NULL)
	{
		stageDoor->draw();
	}
	
}

void TilePlacer::draw()
{
	TilePlacerCursor->Draw(1, onlyAnimation, posX, posY);
}

void TilePlacer::chackInput()
{
	if(keyState.Place)
	{
		placeTile();
	}

	if (keyState.Delete)
	{
		removeTile();
	}

	changeTile();

	if (keyState.Save)
	{
		Save();
	}
	
	if (keyState.SwitchSpriteSheet)
	{
		switchTileSet();
	}
	switchMode();
}

void TilePlacer::Save()
{
	ofstream levelFile("level.txt");
	int x(0), y(0);
	while(y < 17)
	{
		while(x < 30)
		{
			if(StageTiles[x][y] == NULL)
			{
				levelFile << 0 << endl;
			}
			else
			{
				levelFile << 1 <<" "<<
					StageTiles[x][y]->getPositionX() << " " <<
					StageTiles[x][y]->getPositionY() << " " <<
					StageTiles[x][y]->getCurrentAnimation() << endl;
					}
			x++;
		}
		y++;
		x = 0;
	}
	x = (0);
	y = (0);
	while (y < 17)
	{
		while (x < 30)
		{
			if (stageSpikes[x][y] == NULL)
			{
				levelFile << 0 << endl;
			}
			else
			{
				levelFile << 1 << " " <<
					stageSpikes[x][y]->getPositionX() << " " <<
					stageSpikes[x][y]->getPositionY() << " " <<
					stageSpikes[x][y]->getCurrentAnimation() << endl;
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (stageDoor == NULL)
	{
		levelFile << 0 << endl;
	}else
	{
		levelFile << 1 << " " <<
			stageDoor->getPositionX() << " " <<
			stageDoor->getPositionY() <<endl;
	}
	while (y < 17)
	{
		while (x < 30)
		{
			if (stageSpikes[x][y] == NULL)
			{
				levelFile << 0 << endl;
			}
			else
			{
				levelFile << 1 << " " <<
					wallTraps[x][y]->getTrapPositionX() << " " <<
					wallTraps[x][y]->getTrapPositionX() << " " <<
					wallTraps[x][y]->getCurrentAnimation() << endl;
			}
			x++;
		}
		y++;
	}
}

void TilePlacer::switchTileSet()
{
	if (curentSpriteSheet < (sizeof(TileSpriteSheets)/4 - 1))
	{
		curentSpriteSheet++;
	}else
	{
		curentSpriteSheet = 0;
	}

	int x(0), y(0);
	while (x <= 29)
	{
		while (y <= 16)
		{
			delete StageTiles[x][y];
			y++;
		}
		y = 0;
		x++;
	}

	initStageTiles();
	curentTileSet = new SpriteSheet(TileSpriteSheets[curentSpriteSheet], gfx, true);
}

void TilePlacer::switchMode()
{
	if(keyState.changeMode && !prevKeyState.changeMode)
	{
		if (curentMode < maxModes)
		{
			curentMode++;
		}
		else
		{
			curentMode = 0;
		}
		curentTile = 0;
	}
}
