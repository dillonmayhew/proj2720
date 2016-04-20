#include "WaterAtk.h"

WaterAtk::WaterAtk(){image = 0;}
WaterAtk::WaterAtk(ALLEGRO_BITMAP *waterimage)
{
	maxFrame = 15;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;
	dmg = 1;
	setCurRow(0);
	setCurColumn(0);

	live = false;
	speed = 7;

	boundx = 15;
	boundy = 25;

	image = waterimage;
}