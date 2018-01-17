#ifndef TILE_AND_COLITION_MANAGMENT
#define TILE_AND_COLITION_MANAGMENT

#include "../_SOURCE Common/Tiles.h"
#include "../_SOURCE Common/deathTraps.h"
#include "../_SOURCE Common/Doors.h"
#include <math.h>

class TileManager
{
	static defaultTile* stageTiles[30][17];
	static Spikes* stageSpikes[30][17];
	static WallCannon* wallTraps[30][17];
	static const string levelList[10][10];
	static SpriteSheet* WorldSpriteSheets[10];
	static D2DGraphics* gfx;
	static Door* stageDoor;
	
	static int m_currentWorld;
	static int m_currentLevel;

public:
	static void drawTiles();
	static void checkColition(PlayerCharacter* P1);
	static void update();

	static void loadStageTiles(int currentWorld, int currentLevel);
	static void initGFX(D2DGraphics* _gfx);
};

#endif // !TILE_AND_COLITION_MANAGMENT