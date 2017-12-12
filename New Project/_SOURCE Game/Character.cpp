#include "../_SOURCE Game/Character.h"
#include "../_SOURCE Common/D2DGraphics.h"

D2DGraphics *Character::gfx;

void Character::init(D2DGraphics * graphics)
{
	gfx = graphics;
}
