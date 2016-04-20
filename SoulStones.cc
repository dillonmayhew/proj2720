#include "SoulStones.h"

SoulStones::SoulStones()
{
	image = NULL;
}
SoulStones::SoulStones(ALLEGRO_BITMAP *soulimage)
{
	maxFrame = 49;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;

	setCurRow(rand()%19);
	setCurColumn(0);

	boundx = 15;
	boundy = 15;

	hit = false;
	live = true;
	x = rand()%gameWidth - frameWidth;
	y = rand()%gameHeight - frameHeight;

	image = soulimage;
}
void SoulStones::updateObj()
{
	if(live)
	{
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= 32)
			{
				setCurColumn(0);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
	else
	{
		dissapear();
	}	
}
void SoulStones::dissapear()
{
	if(getCurColumn() < 33){
		hit = true;
		setCurColumn(33);
	}
	if(++frameCount >= frameDelay)
	{
		if((getCurColumn() + 1) >= maxFrame)
		{
			hit = false;
			setCurColumn(maxFrame);
		}
		setCurColumn(getCurColumn() + 1);
		frameCount = 0;
	}
}
void SoulStones::collidePlayer(Player *plyr)
{
	if(live)
	{
		if(plyr->live)
		{
			if(x+boundx > (plyr->x - plyr->boundx) &&
				x-boundx < (plyr->x + plyr->boundx) &&
				y+boundy > (plyr->y - plyr->boundy) &&
				y-boundy < (plyr->y + plyr->boundy))
			{
				plyr->soulCount += 1;
				live = false;
			}
		}
	}
}
void SoulStones::reset()
{
	setCurColumn(0);
	frameDelay = 2;
}