#include "LavaTroll.h"

LavaTroll::LavaTroll()
{
	ID = LAVATROLL;
	image = NULL;
}
LavaTroll::LavaTroll(ALLEGRO_BITMAP *trollImage)
{
	ID = LAVATROLL;
	maxFrameWalk = 9;
	maxFrameAtk = 22;
	speed = 1.5;

	dBound = 50;
	setCurRow(0);
	setCurColumn(0);
	frameCount = 0;
	frameDelay = 5;
	frameWidth = 96;
	frameHeight = 96;
	maxHealth = 2;
	health = 2;

	yDirect = 1;

	boundx = 15;
	boundy = 30;

	x = rand()%gameWidth - frameWidth;
	y = rand()%gameHeight - frameHeight;

	hit = false;
	live = true;

	image = trollImage;
}
void LavaTroll::disintegrate()
{
	if(getCurColumn() <= 27)
		setCurColumn(27);
	if(++frameCount >= frameDelay)
	{
		if((getCurColumn() + 1) >= 43)
		{
			setCurColumn(27);
			live = false;
			hit = false;
		}
		setCurColumn(getCurColumn() + 1);
		frameCount = 0;
	}
}
void LavaTroll::pace()
{
	if(getCurRow() != 1 && getCurRow() != 3)
		setCurRow(1);
	if(getCurRow() == 1)
		walk(E);
	else if(getCurRow() == 3)
		walk(W);
	if(getCurColumn()+1 >= maxFrameWalk)
	{
		if(getCurRow() == 1){
			setCurRow(3);
			setCurColumn(1);
		}
		else if(getCurRow() == 3){
			setCurRow(1);
			setCurColumn(1);
		}
	}
}