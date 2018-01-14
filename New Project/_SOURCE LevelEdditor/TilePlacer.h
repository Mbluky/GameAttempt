#ifndef TILE_PLACER_H
#define TILE_PLACER_H

#include "../_SOURCE Common/Tiles.h"
#include "../_SOURCE LevelEdditor/KeyboardInput.h"
#include "../_SOURCE Common/deathTraps.h"
#include "../_SOURCE Common/Doors.h"

class TilePlacer
{
	float posX, posY;
	int curentTile, curentMode;
	bool justMoved;
	int moveCountDown, curentSpriteSheet, maxModes = 3;
	wchar_t* TileSpriteSheets[2];
	defaultTile* StageTiles [30][17];
	E_KeyState prevKeyState;
	E_KeyState keyState;
	ANIMATION onlyAnimation;
	SpriteSheet* TilePlacerCursor, *curentTileSet, *curentspikeSprites;
	D2DGraphics* gfx;
	Spikes* stageSpikes[30][17];
	WallCannon* wallTraps[30][17];
	Door* stageDoor;
public:
	TilePlacer();
	~TilePlacer();
	void initStageTiles();
	void getInput(E_KeyState keyState_);
	void getGFX(D2DGraphics* GFX);
	void moveCursor();
	void placeTile();
	void removeTile();
	void changeTile();
	void drawStageTiles();
	void draw();
	void chackInput();
	void Save();
	void switchTileSet();
	void switchMode();
};

#endif // !TILE_PLACER_H
