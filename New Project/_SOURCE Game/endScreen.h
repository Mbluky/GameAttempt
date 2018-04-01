#ifndef END_SCREEN_H
#define END_SCREEN_H

#include "../_SOURCE Game/GameLevel.h"
#include "../_SOURCE Common/Letters.h"

class EndScreen :public GameLevel
{
	Phrase* congratulations;
	Phrase* characterAnimation;
	Phrase* mrBlooper;
	Phrase* everythingElse;
	Phrase* pyroMab;
	int timer;
public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;
	bool switchToOther() override;
	void getInput(KeyState keystate) override;
};

#endif // !END_SCREEN_H
