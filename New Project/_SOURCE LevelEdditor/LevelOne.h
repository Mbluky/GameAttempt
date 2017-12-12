#ifndef LEVEL_ONE_E_HEADER
#define LEVEL_ONE_E_HEADER

#include "../_SOURCE LevelEdditor/GameLevel.h"
#include "../_SOURCE Common/D2DGraphics.h"
#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE Common/Animations.h"
#include "../_SOURCE LevelEdditor/TilePlacer.h"

class LevelEdditor: public E_GameLevel 
{
	int frame;
	SpriteSheet* sprites;
	TilePlacer* tilePlacer;
public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override; 
	void getInput(E_KeyState keystate) override;

};

#endif //LEVEL_ONE_E_HEADER