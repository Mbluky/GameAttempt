#ifndef TILE_AND_COLITION_MANAGMENT
#define TILE_AND_COLITION_MANAGMENT

#include "../_SOURCE Common/Tiles.h"
#include <math.h>
class TileManager
{
	static float deltaX, deltaY, colitionX, colitionY;
	static defaultTile* stageTiles[30][17];

public:
	static void drawTiles() 
	{
		int x = 0;
		int y = 0;
		while(y<17)
		{
			while (x<30)
			{
				stageTiles[x][y]->draw();
				x++;
			}
			x = 0;
			y++;
		}
	}
	static void checkColition(PlayerCharacter* P1)
	{
		int x = 0;
		int y = 0;

		while (y < 17)
		{
			while (x < 30)
			{
				if (stageTiles[x][y] = NULL)
				{

				}
				else if (!stageTiles[x][y]->getInternal())
				{
					deltaX = (stageTiles[x][y]->getColitionData()[0] - P1->getColitionData()[0]);
					deltaY = (stageTiles[x][y]->getColitionData()[1] - P1->getColitionData()[1]);

					colitionX = (abs(deltaX) - (stageTiles[x][y]->getColitionData()[2] / 2 + P1->getColitionData()[2] / 2));
					colitionY = (abs(deltaY) - (stageTiles[x][y]->getColitionData()[3] / 2 + P1->getColitionData()[3] / 2));

					if (colitionX < 0 || colitionY < 0)
					{
						if (colitionX <= colitionY)
						{
							if (deltaX < 0)
							{
								P1->push(true, colitionX);
							}
							else
							{
								P1->push(true, -colitionX);
							}
						}if (colitionY > colitionX)
						{
							if (deltaY < 0)
							{
								P1->push(false, colitionY);
							}
							else
							{
								P1->push(false, -colitionY);
							}
						}
					}
				}
				x++;
			}
			x = 0;
			y++;

		}
	}

	void loadStageTiles(ofstream* tileFileSream)
	{
		
	}
};

#endif // !TILE_AND_COLITION_MANAGMENT