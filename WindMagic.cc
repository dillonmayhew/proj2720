#include "WindMagic.h"

WindMagic::WindMagic(ALLEGRO_BITMAP *windimage)
{
	ID = WINDMAGIC;
	maxFrame = 20;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;
	dmg = 1;
	setCurRow(0);
	setCurColumn(0);

	live = false;
	speed = 10;

	boundx = 10;
	boundy = 10;

	image = windimage;
}
void WindMagic::startAtk(Player *plyr)
{
	plyr->frameDelay = 4;
	if(!live && plyr->getCurRow() == 0)
	{
		pOffsetx = 18;
		pOffsety = -18;
		yDirect = -1;
		xDirect = 0;
		initAtk(plyr);
	}
	else if(!live && plyr->getCurRow() == 1)
	{
		pOffsetx = 60;
		pOffsety = 0;
		yDirect = 0;
		xDirect = 1;
		initAtk(plyr);
	}
	else if(!live && plyr->getCurRow() == 2)
	{
		pOffsetx = 18;
		pOffsety = 32;
		yDirect = 1;
		xDirect = 0;
		initAtk(plyr);
	}
	else if(!live && plyr->getCurRow() == 3)
	{
		pOffsetx = -12;
		pOffsety = 0;
		yDirect = 0;
		xDirect = -1;
		initAtk(plyr);
	}
	else if(!live && plyr->getCurRow() == 4)
	{
		pOffsetx = 48;
		pOffsety = -12;
		yDirect = -1;
		xDirect = 1;
		initAtk(plyr);
	}
	else if(!live && plyr->getCurRow() == 5)
	{
		pOffsetx = 0;
		pOffsety = -12;
		yDirect = -1;
		xDirect = -1;
		initAtk(plyr);
	}
	else if(!live && plyr->getCurRow() == 6)
	{
		pOffsetx = 48;
		pOffsety = 32;
		yDirect = 1;
		xDirect = 1;
		initAtk(plyr);
	}
	else if(!live && plyr->getCurRow() == 7)
	{
		pOffsetx = 0;
		pOffsety = 32;
		yDirect = 1;
		xDirect = -1;
		initAtk(plyr);
	}
}