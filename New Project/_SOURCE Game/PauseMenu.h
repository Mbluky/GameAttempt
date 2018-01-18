#ifndef LEVELEDDITOR

#ifndef PAUSE_MANU_HEADER
#define PAUSE_MENU_HEADER

#include "../_SOURCE Common/Letters.h"
#include "../_SOURCE Game/KeyboardInput.h"

class PauseMenu
{
	static bool m_paused, returnToMainMenu;
	static Phrase* menuOptions[3];
	static Phrase* m_PauseMenuTitle;
	static KeyState m_keystate;
	static KeyState m_prevkeystate;
	static SpriteSheet* menuBorderSprite;
	static D2DGraphics* m_gfx;
	static int selection, subMenu;
public:
	static void initGfx(D2DGraphics* gfx);
	static void getInput(KeyState keystate);
	static void update();
	static void draw();
	static void load();
	static void unload();
	static void select();
	static bool quitToMainMenu();
	static bool resume();
};

#endif // !PAUSE_MANU_HEADER
#endif //LEVELEDDITOR