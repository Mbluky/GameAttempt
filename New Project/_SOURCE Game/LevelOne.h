#ifndef LEVEL_ONE_HEADER
#define LEVEL_ONE_HEADER

#include "../_SOURCE Game/GameLevel.h"
#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE Common/Animations.h"
#include "../_SOURCE Game/PlayerCharacter.h"
#include <fstream>

class LevelOne: public GameLevel 
{
	int frame;
	SpriteSheet* sprites;
	bool isPaused, quitToMenu;
	static int level, world, nextMode;
public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;
	void getInput(KeyState keystate) override;
	bool switchToOther() override;
	void static getCurrentLevel(int currentWorld, int currentLevel);
	int static changeMode();

};
#endif //LEVEL_ONE_HEADER