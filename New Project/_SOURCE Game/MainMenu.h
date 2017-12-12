#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../_SOURCE Common/SpriteSheet.h"
#include "../_SOURCE Common/Letters.h"
#include "../_SOURCE Game/KeyboardInput.h"
#include "../_SOURCE Game/GameLevel.h"

class MainMenu : public GameLevel
{
	Phrase* GameName;
	Phrase* mainMenu;
	Phrase* play;
	Phrase* option;
	Phrase* quit;
	//Phrase* gameVersion;
	int selection;
	KeyState m_keyState;
	KeyState m_prevKeyState;
	bool switchingTrigger = false;
public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;
	void getInput(KeyState keystate) override;
	bool switchToOther();
};

#endif // !MAIN_MENU_H