#include "LavaAtk.h"

LavaAtk::LavaAtk(){image = 0;}
LavaAtk::LavaAtk(ALLEGRO_BITMAP *lavaimage)
{
	maxFrame = 15;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;
	dmg = 2;
	setCurRow(0);
	setCurColumn(0);

	live = false;
	speed = 7;

	boundx = 15;
	boundy = 25;

	image = lavaimage;
}