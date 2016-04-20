#include "Wizard.h"

Wizard::Wizard(ALLEGRO_BITMAP *wizimage)
{
	soulCount = 0;
	maxFrameWalk = 9;
	maxFrameRun = 38;
	maxFrameAtk = 22;
	maxHealth = 50;
	health = 50;
	setCurRow(0);
	setCurColumn(0);
	frameCount = 0;
	frameDelay = 5;
	frameWidth = 96;
	frameHeight = 96;

	speed = 2;
	runSpeed = speed*1.75;
	x = gameWidth / 2 - (frameWidth / 2);
	y = gameHeight / 2 - (frameHeight / 2);

	boundx = 15;
	boundy = 30;

	hit = false;
	live = true;

	image = wizimage;
}