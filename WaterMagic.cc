#include "WaterMagic.h"

WaterMagic::WaterMagic(ALLEGRO_BITMAP *waterimage)
{
	ID = WATERMAGIC;
	maxFrame = 20;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;
	dmg = 1;
	//curRow = 0;
	setCurRow(0);
	setCurColumn(0);

	live = false;
	speed = 6;

	boundx = 10;
	boundy = 10;

	image = waterimage;
}