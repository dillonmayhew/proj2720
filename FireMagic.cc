#include "FireMagic.h"

FireMagic::FireMagic(ALLEGRO_BITMAP *firimage)
{
	ID = FIREMAGIC;
	maxFrame = 20;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;
	dmg = 1;
	setCurRow(0);
	setCurColumn(0);

	live = false;
	speed = 6;

	boundx = 10;
	boundy = 10;

	image = firimage;
}