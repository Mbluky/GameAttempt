#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Game/PlayerCharacter.h"
#include "../_SOURCE Common/SpriteSheet.h"

class GameLevel
{
protected:
	static D2DGraphics* gfx;
	static PlayerCharacter* PlayerOne;

public:
	static void init(D2DGraphics* graphics)
	{
		gfx = graphics;
	}
	static void loadPCharacter(PlayerCharacter* playerChar)
	{
		PlayerOne = playerChar;
	}
	void virtual Load() = 0;
	void virtual Unload() = 0;
	void virtual Update() = 0;
	void virtual Render() = 0;
	void virtual getInput(KeyState keystate) = 0;
	bool virtual switchToOther() = 0;
};

#endif