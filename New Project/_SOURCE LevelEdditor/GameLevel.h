#ifndef GAME_E_LEVEL_H
#define GAME_E_LEVEL_H

#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE LevelEdditor/KeyboardInput.h"

class E_GameLevel
{
protected:
	static D2DGraphics* gfx;

public:
	static void init(D2DGraphics* graphics)
	{
		gfx = graphics;
	}
	void virtual Load() = 0;
	void virtual Unload() = 0;
	void virtual Update() = 0;
	void virtual Render() = 0;
	void virtual getInput(E_KeyState keystate) = 0;
};

#endif //GAME_E_LEVEL_H