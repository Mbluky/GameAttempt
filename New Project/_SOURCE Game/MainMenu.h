#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE Common/Letters.h"
#include "../_SOURCE Game/KeyboardInput.h"
#include "../_SOURCE Game/GameLevel.h"
#include "../_SOURCE Game/SoundSystem.h"

class MainMenu : public GameLevel
{
	Phrase* GameName;
	Phrase* mainMenu;
	Phrase* play;
	Phrase* option;
	Phrase* quit;
	Phrase* gameVersion;
	Phrase* WorldList[10];
	Phrase* LevelList[10];
	Sound* MenuMusic;
	unsigned int selection;
	unsigned int subMenu;
	unsigned int selectedWorld = 0;
	bool unlockedLevels[10][10];
	bool switchingTrigger = false;
	KeyState m_keyState;
	KeyState m_prevKeyState;
public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;
	void getInput(KeyState keystate) override;
	bool switchToOther();
};

#endif // !MAIN_MENU_H