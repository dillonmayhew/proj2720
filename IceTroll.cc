#include "IceTroll.h"

IceTroll::IceTroll()
{
	ID = ICETROLL;
	image = NULL;
}
IceTroll::IceTroll(ALLEGRO_BITMAP *trollImage)
{
	ID = ICETROLL;
	maxFrameWalk = 9;
	maxFrameAtk = 22;
	dBound = 50;
	speed = 1;

	setCurRow(0);
	setCurColumn(0);
	frameCount = 0;
	frameDelay = 5;
	frameWidth = 96;
	frameHeight = 96;
	maxHealth = 3;
	health = 3;

	yDirect = 1;

	boundx = 15;
	boundy = 30;

	x = rand()%gameWidth - frameWidth;
	y = rand()%gameHeight - frameHeight;

	hit = false;
	live = true;

	image = trollImage;
}
void IceTroll::disintegrate()
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
void IceTroll::pace()
{
	if(getCurRow() != 0 && getCurRow() != 2)
		setCurRow(0);
	if(getCurRow() == 0)
		walk(N);
	else if(getCurRow() == 2)
		walk(S);
	if(getCurColumn()+1 >= maxFrameWalk)
	{
		if(getCurRow() == 0){
			setCurRow(2);
			setCurColumn(1);
		}
		else if(getCurRow() == 2){
			setCurRow(0);
			setCurColumn(1);
		}
	}
}