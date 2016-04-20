#include "EarthMagic.h"

EarthMagic::EarthMagic(ALLEGRO_BITMAP *earthimage)
{
	ID = EARTHMAGIC;
	maxFrame = 20;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;
	dmg = 2;
	setCurRow(0);
	setCurColumn(0);

	live = false;
	speed = 4;

	boundx = 10;
	boundy = 10;

	image = earthimage;
}