#ifndef LEVELEDDITOR

#ifndef TRANSITION_MENU_H
#define TRANSITION_MENU_H

#include "../_SOURCE Game/GameLevel.h"
#include "../_SOURCE Common/Letters.h"

class T_Menu: public GameLevel
{
	static int m_World, m_Level;
	Phrase* levelName;
	Phrase* clear;
	KeyState m_keyState, m_prevKeyState;
	bool loadNextStage;
	int countDown;
public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;
	void getInput(KeyState keystate) override;
	bool switchToOther() override;
	static void getCurrentLevel(int World, int Level);

};

#endif // !TRANSITION_MENU_H
#endif //LEVELEDDITOR