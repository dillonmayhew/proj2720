#include "enemyAtk.h"

enemyAtk::enemyAtk(ALLEGRO_BITMAP *atkimage)
{
	maxFrame = 15;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;
	//curRow = 0;
	setCurRow(0);
	setCurColumn(0);

	live = false;
	speed = 7;

	boundx = 15;
	boundy = 25;

	image = atkimage;
}
void enemyAtk::startAtk(Enemy *enemy, Player *plyr)
{
	if(enemy->inAtkDist(plyr) && enemy->getCurColumn()<27)
	{
		if(!live && enemy->getCurRow() == 0)
		{
			pOffsetx = 24;
			pOffsety = -12;
			yDirect = -1;
			xDirect = 0;
			initAtk(enemy);
		}
		else if(!live && enemy->getCurRow() == 1)
		{
			pOffsetx = 60;
			pOffsety = 0;
			yDirect = 0;
			xDirect = 1;
			initAtk(enemy);
		}
		else if(!live && enemy->getCurRow() == 2)
		{
			pOffsetx = 24;
			pOffsety = 32;
			yDirect = 1;
			xDirect = 0;
			initAtk(enemy);
		}
		else if(!live && enemy->getCurRow() == 3)
		{
			pOffsetx = -12;
			pOffsety = 0;
			yDirect = 0;
			xDirect = -1;
			initAtk(enemy);
		}
		else if(!live && enemy->getCurRow() == 4)
		{
			pOffsetx = 48;
			pOffsety = -12;
			yDirect = -1;
			xDirect = 1;
			initAtk(enemy);
		}
		else if(!live && enemy->getCurRow() == 5)
		{
			pOffsetx = 0;
			pOffsety = -12;
			yDirect = -1;
			xDirect = -1;
			initAtk(enemy);
		}
		else if(!live && enemy->getCurRow() == 6)
		{
			pOffsetx = 48;
			pOffsety = 32;
			yDirect = 1;
			xDirect = 1;
			initAtk(enemy);
		}
		else if(!live && enemy->getCurRow() == 7)
		{
			pOffsetx = 0;
			pOffsety = 32;
			yDirect = 1;
			xDirect = -1;
			initAtk(enemy);
		}
	}
}
void enemyAtk::reset()
{
	live = false;
	frameDelay = 4;
	setCurRow(0);
	setCurColumn(0);
}
void enemyAtk::updateObj(Enemy *enemy, Player *plyr)
{
	if(live)
	{
		if(getCurRow() > 1)
		{
			reset();
		}
		if(getCurRow() > 0)
		{
			if(enemy->getCurColumn() < 27 && enemy->inAtkDist(plyr))
				enemy->stop();
			y += yDirect*speed;
			x += xDirect*speed;
			frameDelay = 5;
		}
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrame)
			{
				setCurColumn(0);
				setCurRow(getCurRow() + 1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
}
void enemyAtk::collidePlayer(Player *plyr)
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
				plyr->hit = true;
				reset();
				//if(getCurRow() > 0)
				plyr->health -= dmg;
			}
			plyr->beenHit();
		}
	}
}
void enemyAtk::initAtk(Enemy *enemy)
{
	x = enemy->x + pOffsetx;
	y = enemy->y + pOffsety;
	live = true;
}