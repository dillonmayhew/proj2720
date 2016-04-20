#include "Objects.h"

void Objects::updateObj(Player *plyr)
{
	if(live)
	{
		if(plyr->getCurColumn() > 9 && plyr->getCurColumn() < 17 && getCurColumn() <= 1)
		{
			setCurRow(plyr->getCurRow());
			setCurColumn(0);
		}
		else
		{
			y += yDirect*speed;
			x += xDirect*speed;
			frameDelay = 5;
		}
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrame)
			{
				reset();
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
}
void Objects::reset()
{
	live = false;
	setCurRow(0);
	setCurColumn(0);
	frameDelay = 2;
}
void Objects::initAtk(Player *plyr)
{
	x = plyr->x + pOffsetx;
	y = plyr->y + pOffsety;
	live = true;
}
void Objects::startAtk(Player *plyr)
{
	plyr->frameDelay = 5;
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
void Objects::collideEnemy(Enemy *enemy)
{
	if(live)
	{
		if(enemy->live)
		{
			if(x+boundx > (enemy->x - enemy->boundx) &&
				x-boundx < (enemy->x + enemy->boundx) &&
				y+boundx > (enemy->y - enemy->boundy) &&
				y-boundx < (enemy->y + enemy->boundy))
			{
				enemy->hit = true;
				enemy->beenHit();
				reset();
				if(ID == FIREMAGIC && enemy->ID == LAVATROLL)
					enemy->health += dmg;
				else if(ID == FIREMAGIC && enemy->ID == ICETROLL)
					enemy->health -= dmg*3;
				else if(ID == WATERMAGIC && enemy->ID == LAVATROLL)
					enemy->health -= dmg*2;
				else if(ID == WATERMAGIC && enemy->ID == ICETROLL)
					enemy->health += dmg;
				else if(ID == WINDMAGIC)
					enemy->health -= dmg;
				else if(ID == EARTHMAGIC && enemy->ID == GREYTROLL)
					enemy->health -= dmg*2;
				else
					enemy->health -= dmg;

			}
		}
	}
}